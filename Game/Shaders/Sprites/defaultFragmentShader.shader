#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
	FragColor = vec4(1, 0, 1, 1);
}