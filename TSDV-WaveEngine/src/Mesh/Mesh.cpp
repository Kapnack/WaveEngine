#include "Mesh.h"

const unsigned int Mesh::NULL_MESH = 0;

Mesh::Mesh(VertexData* vertexBuffer, const unsigned int& vertexSize, const string_view name, const unsigned int& ID)
{
	this->ID = ID;
	this->name = name;
	this->vertexBuffer = vertexBuffer;
	this->vertexSize = vertexSize;
}

Mesh::~Mesh()
{
}

const VertexData* Mesh::GetVertexBuffer()
{
	return vertexBuffer;
}

const unsigned int Mesh::GetVertexSize()
{
	return vertexSize;
}

string Mesh::GetName()
{
	return name;
}
