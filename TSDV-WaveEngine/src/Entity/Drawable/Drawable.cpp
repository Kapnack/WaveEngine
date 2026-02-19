#include "Drawable.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Entity/EntityManager.h"

Drawable::Drawable(const unsigned int& ID)
{
	this->ID = ID;
}

Drawable::~Drawable()
{
	delete[] vertex;
	delete[] indices;
}

MaterialManager* Drawable::GetMaterialManager()
{
	return ServiceProvider::Instance().Get<MaterialManager>();
}

Renderer* Drawable::GetRenderer() const
{
	return ServiceProvider::Instance().Get<Renderer>();
}

void Drawable::SetLayer(const int& layer)
{
	ServiceProvider::Instance().Get<EntityManager>()->OnEntityChangeLayer(ID, this->layer, layer);
	this->layer = layer;
}

int Drawable::GetLayer() const
{
	return layer;
}

void Drawable::SetMaterial(unsigned int materialID)
{
	this->materialID = materialID;
}

const unsigned int Drawable::GetMaterial() const
{
	return materialID;
}

void Drawable::SetColor(const Vector4& color)
{
	for (int i = 0; i < vertexSize; i++)
		vertex[i].SetColor(color);

	UpdateVertexBuffer();
}

void Drawable::SetVertexColor(const int& index, const Vector4& color)
{
	if (index < 0 || index >= vertexSize)
		return;

	vertex[index].SetColor(color);
	UpdateVertexBuffer();
}

void Drawable::UpdateVertexBuffer()
{
	GetRenderer()->UpdateBuffer(vertex, vertexSize, VBO);
}