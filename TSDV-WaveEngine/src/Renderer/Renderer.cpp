#include "Renderer.h"

#include "FileReader/FileReader.h"
#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialManager.h"
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

void Renderer::Init()
{
	res.x = GetWindow()->GetWidth();
	res.y = GetWindow()->GetHeight();
	res.z = 1.0f;

	//This tells OpenGL from were in the window it is able to draw
	glViewport(0, 0, res.x, res.y); // 0,0 = inferior left corner of the window.
	//Some drivers might automatically create a viewport. But not all of them do that. That is why it is important to create one.

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	view = new glm::mat4(1.0f);
	proj = new glm::mat4(glm::ortho(0.0f, res.x, 0.0f, res.y, -1.0f, 1.0f));

	FileReader fileReader;

	string vertexShader = fileReader.ReadFile("Shaders/Shapes/basicVertexShader.shader");

	string fragmentShader = fileReader.ReadFile("Shaders/Shapes/defaultFragmentShader.shader");

	shapeShaders = ServiceProvider::Instance().Get<MaterialManager>()->CreateMaterial("defaultShapeShader", vertexShader, fragmentShader);

	vertexShader = fileReader.ReadFile("Shaders/Sprites/basicVertexShader.shader");

	fragmentShader = fileReader.ReadFile("Shaders/Sprites/defaultFragmentShader.shader");

	spriteShaders = ServiceProvider::Instance().Get<MaterialManager>()->CreateMaterial("defaultSpriteShader", vertexShader, fragmentShader);
}

const unsigned int Renderer::ReturnWorkingMaterial(const unsigned int& materialIDToTry, const unsigned int& materialIDfallBack)
{
	return materialIDToTry != Material::NULL_MATERIAL ? materialIDToTry : materialIDfallBack;
}

void Renderer::CreateBuffers(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const
{
	//VAO = Vertex Array Object: It's the object were VBO & EBO store.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//VBO = Vertex Buffer Object: It contains the data of the vertex.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(VertexData), vertex, GL_DYNAMIC_DRAW);

	// EBO = Element Buffer Object: It contains the order in which the VBO vertices will be used, by specifying their indices.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(int), indices, GL_DYNAMIC_DRAW);

	//Sets layout 0, Vertex.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
	glEnableVertexAttribArray(0);

	//Sets layout 1, RGBA.
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Renderer::CreateBuffersSprite(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO, const unsigned int& texture) const
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
}

Vector3 Renderer::GetRes()
{
	return res;
}

void Renderer::DrawElement(glm::mat4& model, unsigned int materialID, int indicesSize, unsigned int VAO)
{
	Material* materialToUse = &GetMaterialManager()->GetMaterial(ReturnWorkingMaterial(materialID, shapeShaders));

	materialToUse->Bind();

	glUniformMatrix4fv(materialToUse->GetUModel(), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(materialToUse->GetUView(), 1, GL_FALSE, glm::value_ptr(*view));

	glUniformMatrix4fv(materialToUse->GetUProj(), 1, GL_FALSE, glm::value_ptr(*proj));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);
}

void Renderer::DrawElementSprite(glm::mat4& model, unsigned int materialID, int indicesSize, unsigned int VAO, unsigned int texture)
{
	Material* materialToUse = &GetMaterialManager()->GetMaterial(ReturnWorkingMaterial(materialID, spriteShaders));

	materialToUse->Bind();

	glUniformMatrix4fv(materialToUse->GetUModel(), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(materialToUse->GetUView(), 1, GL_FALSE, glm::value_ptr(*view));

	glUniformMatrix4fv(materialToUse->GetUProj(), 1, GL_FALSE, glm::value_ptr(*proj));

	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::Unload()
{
	delete view;
	delete proj;
}