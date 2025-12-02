#include "Renderer.h"

#include "VertexData.h"

using namespace std;

Renderer::Renderer(Window* window)
{
	this->window = window;
	Init();
}

Renderer::~Renderer()
{
	Unload();
}

void Renderer::Init()
{
	res.x = window->GetWidth();
	res.y = window->GetHeight();
	res.z = 1.0f;

	//This tells OpenGL from were in the window it is able to draw
	glViewport(0, 0, res.x, res.y); // 0,0 = inferior left corner of the window.
	//Some drivers might automatically create a viewport. But not all of them do that. That is why it is important to create one.

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	view = new glm::mat4(1.0f);
	proj = new glm::mat4(glm::ortho(0.0f, res.x, 0.0f, res.y, -1.0f, 1.0f));

	std::string vertexShader =
		"#version 330 core						\n"
		"layout(location = 0) in vec3 aPos;		\n"
		"layout(location = 1) in vec4 aColor; \n"
		"uniform mat4 uModel;  // TRS matrix\n"
		"uniform mat4 uView;   // camera transform\n"
		"uniform mat4 uProj;   // projection\n"
		"out vec4 vertexColor;\n"
		"	void main()\n"
		"	{\n"
		"		gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);\n"
		"		vertexColor = aColor;\n"
		"	}\n";


	std::string fragmentShader =
		"#version 330 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(vertexColor.x, vertexColor.y + 0.7, vertexColor.z, vertexColor.w);\n"
		"}\n";

	shapeShaders = new Material();
	shapeShaders->CreateShader(vertexShader, fragmentShader);


	vertexShader =
		"#version 330 core						\n"
		"layout(location = 0) in vec3 aPos;		\n"
		"layout(location = 1) in vec4 aColor; \n"
		"layout (location = 2) in vec2 aTexCoord; \n"
		"uniform mat4 uModel;  // TRS matrix\n"
		"uniform mat4 uView;   // camera transform\n"
		"uniform mat4 uProj;   // projection\n"
		"out vec4 vertexColor;\n"
		"out vec2 texCoord;\n"
		"	void main()\n"
		"	{\n"
		"		gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);\n"
		"		vertexColor = aColor;\n"
		"		texCoord = aTexCoord;\n"
		"	}\n";


	fragmentShader =
		"#version 330 core\n"
		"in vec4 vertexColor;\n"
		"in vec2 texCoord;\n"
		"uniform sampler2D ourTexture;"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(ourTexture, texCoord) * vertexColor;"
		"}\n";

	spriteShaders = new Material();
	spriteShaders->CreateShader(vertexShader, fragmentShader);
}

void Renderer::CreateBuffers(VertexData* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO)
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

void Renderer::CreateBuffersSprite(VertexData* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO, unsigned int& texture)
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

void Renderer::DrawElement(glm::mat4& model, int indicesSize, unsigned int VAO)
{
	shapeShaders->Bind();

	glUniformMatrix4fv(shapeShaders->GetUModel(), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(shapeShaders->GetUView(), 1, GL_FALSE, glm::value_ptr(*view));

	glUniformMatrix4fv(shapeShaders->GetUProj(), 1, GL_FALSE, glm::value_ptr(*proj));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);
}

void Renderer::DrawElementSprite(glm::mat4& model, int indicesSize, unsigned int VAO, unsigned int texture)
{
	spriteShaders->Bind();

	glUniformMatrix4fv(spriteShaders->GetUModel(), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(spriteShaders->GetUView(), 1, GL_FALSE, glm::value_ptr(*view));

	glUniformMatrix4fv(spriteShaders->GetUProj(), 1, GL_FALSE, glm::value_ptr(*proj));

	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::Unload()
{
	delete shapeShaders;
	delete view;
	delete proj;
}
