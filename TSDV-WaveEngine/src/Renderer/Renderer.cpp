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

	const std::string vertexShader =
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


	const std::string fragmentShader =
		"#version 330 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vertexColor;\n"
		"}\n";

	shader = new Material();
	shader->CreateShader(vertexShader, fragmentShader);
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
	shader->Bind();

	glUniformMatrix4fv(shader->GetUModel(), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(shader->GetUView(), 1, GL_FALSE, glm::value_ptr(*view));

	glUniformMatrix4fv(shader->GetUProj(), 1, GL_FALSE, glm::value_ptr(*proj));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);
}

void Renderer::Unload()
{
	delete shader;
	delete view;
	delete proj;
}
