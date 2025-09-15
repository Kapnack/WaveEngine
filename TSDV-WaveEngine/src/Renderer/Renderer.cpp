#include "Renderer.h"

#include <iostream>

#include "VertexPosColor.h"

using namespace std;

Renderer::Renderer()
{
	Init();
}

Renderer::~Renderer()
{
	Unload();
}

void Renderer::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

void Renderer::CreateBuffers(VertexPosColor* vertex, int vertexSize, int* indices, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(VertexPosColor), vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), (void*)offsetof(VertexPosColor, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), (void*)offsetof(VertexPosColor, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Renderer::DrawElement(glm::mat4& model, int indicesSize, unsigned int VAO)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);

	shader->Bind();

	glUniformMatrix4fv(shader->GetUModel(), 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(shader->GetUView(), 1, GL_FALSE, glm::value_ptr(view));

	glUniformMatrix4fv(shader->GetUProj(), 1, GL_FALSE, glm::value_ptr(proj));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);
}

void Renderer::Unload()
{
	delete shader;
}
