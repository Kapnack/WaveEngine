#include "Renderer.h"

#include "FileReader/FileReader.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialFactory.h"
#include "VertexData.h"

using namespace std;

#include <map>

Renderer::Renderer()
{
	Init();
}

Renderer::~Renderer()
{
	Unload();
}

Window* Renderer::GetWindow()
{
	return ServiceProvider::Instance().Get<Window>();
}

MaterialManager* Renderer::GetMaterialManager()
{
	return ServiceProvider::Instance().Get<MaterialManager>();
}

TextureManager* Renderer::GetTextureManager()
{
	return ServiceProvider::Instance().Get<TextureManager>();
}

Texture* Renderer::ChooseTextureToUse(const unsigned int& ID)
{
	return GetTextureManager()->GetTexture(ID) ? GetTextureManager()->GetTexture(ID) : GetTextureManager()->GetTexture(defualtTextureID);
}

void Renderer::Init()
{
	defualtTextureID = ServiceProvider::Instance().Get<TextureImporter>()->LoadTextureAbsolutePath("Sprites/whiteImage.png");

	res.x = GetWindow()->GetWidth();
	res.y = GetWindow()->GetHeight();
	res.z = 1.0f;

	glViewport(0, 0, res.x, res.y);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	view = new glm::mat4(1.0f);
	proj = new glm::mat4(glm::ortho(0.0f, res.x, 0.0f, res.y, -1.0f, 1.0f));

	FileReader* fileReader = ServiceProvider::Instance().Get<FileReader>();

	string vertexShader = fileReader->ReadFileAbsolutePath("Shaders/Shapes/basicVertexShader.shader");

	string fragmentShader = fileReader->ReadFileAbsolutePath("Shaders/Shapes/defaultFragmentShader.shader");

	shapeShaders = ServiceProvider::Instance().Get<MaterialFactory>()->CreateMaterial("defaultShapeShader", vertexShader, fragmentShader);

	vertexShader = fileReader->ReadFileAbsolutePath("Shaders/Sprites/basicVertexShader.shader");

	fragmentShader = fileReader->ReadFileAbsolutePath("Shaders/Sprites/defaultFragmentShader.shader");

	spriteShaders = ServiceProvider::Instance().Get<MaterialFactory>()->CreateMaterial("defaultSpriteShader", vertexShader, fragmentShader);
}

const unsigned int Renderer::ReturnWorkingMaterial(const unsigned int& materialIDToTry, const unsigned int& materialIDfallBack)
{
	return materialIDToTry != Material::NULL_MATERIAL ? materialIDToTry : materialIDfallBack;
}

void Renderer::CreateBuffers(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(VertexData), vertex, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(int), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Renderer::CreateBuffersSprite(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(VertexData), vertex, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(int), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, textureCordinates));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Renderer::UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSize * sizeof(VertexData), vertex);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawCalls = 0;
}

Vector3 Renderer::GetRes()
{
	return res;
}

unsigned int Renderer::GetDrawCalls()
{
	return drawCalls;
}

void Renderer::DrawElement(glm::mat4& model, const unsigned int& materialID, const unsigned int& indicesSize, const unsigned int& VAO)
{
	Material* materialToUse =
		GetMaterialManager()->GetMaterial(
			ReturnWorkingMaterial(materialID, spriteShaders));

	if (!materialToUse)
		return;

	materialToUse->Bind();

	materialToUse->SetVec4("uColor", materialToUse->GetColor());
	materialToUse->SetMat4("uModel", model);
	materialToUse->SetMat4("uView", *view);
	materialToUse->SetMat4("uProj", *proj);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);

	++drawCalls;
}

void Renderer::DrawElementSprite(glm::mat4& model, const unsigned int& materialID, const unsigned int& indicesSize, const unsigned int& VAO, const unsigned int& textureID)
{
	Texture* texture = ChooseTextureToUse(textureID);

	if (texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
	}

	DrawElement(model, materialID, indicesSize, VAO);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::Unload()
{
	delete view;
	delete proj;
}