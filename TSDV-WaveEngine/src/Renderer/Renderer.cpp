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
	const std::string vertexShader =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 vertexColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"   vertexColor = aColor;\n"
		"}\n";


	const std::string fragmentShader =
		"#version 330 core\n"
		"in vec3 vertexColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(vertexColor, 1.0);\n"
		"}\n";

	shader.CreateShader(vertexShader, fragmentShader);
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

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), (void*)offsetof(VertexPosColor, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}



void Renderer::DrawElement(int indicesSize, unsigned int VAO)
{
	shader.Bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, (void*)0);
}

void Renderer::Unload()
{
}
