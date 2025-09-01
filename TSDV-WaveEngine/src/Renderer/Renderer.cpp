#include "Renderer.h"

#include <iostream>

using namespace std;

Renderer::Renderer()
{
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
}

void Renderer::Init(float position[])
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	string vertexShader =
		"#version 330 core \n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = position;\n"
		"}\n";

	string fragmentShader =
		"#version 330 core \n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	Shader shaderClass;

	shader = shaderClass.CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);
}

void Renderer::Unload()
{
	glDeleteShader(shader);
}
