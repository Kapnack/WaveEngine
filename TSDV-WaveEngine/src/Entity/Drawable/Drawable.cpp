#include "Drawable.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Entity/EntityManager.h"

namespace WaveEngine
{
	Drawable::Drawable(const unsigned int& ID)
	{
		this->ID = ID;
	}

	Drawable::~Drawable()
	{
		GetRenderer()->DeleteBuffers(VAO, VBO, EBO);

		delete[] vertex;
		delete[] indices;
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

	unsigned int Drawable::GetMaterial() const
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

	void Drawable::Serialize(std::ostream& stream) const
	{
		stream.write(reinterpret_cast<const char*>(&materialID), sizeof(materialID));
		stream.write(reinterpret_cast<const char*>(&vertexSize), sizeof(vertexSize));

		for (int i = 0; i < vertexSize; i++)
			stream.write(reinterpret_cast<const char*>(&vertex[i]), sizeof(vertex[i]));

		stream.write(reinterpret_cast<const char*>(&indexSize), sizeof(indexSize));

		for (int i = 0; i < indexSize; i++)
			stream.write(reinterpret_cast<const char*>(&indices[i]), sizeof(indices[i]));
	}

	void Drawable::Deserialize(std::istream& stream)
	{
		stream.read(reinterpret_cast<char*>(&materialID), sizeof(materialID));
		stream.read(reinterpret_cast<char*>(&vertexSize), sizeof(vertexSize));

		for (int i = 0; i < vertexSize; i++)
			stream.read(reinterpret_cast<char*>(&vertex[i]), sizeof(vertex[i]));

		stream.read(reinterpret_cast<char*>(&indexSize), sizeof(indexSize));

		for (int i = 0; i < indexSize; i++)
			stream.read(reinterpret_cast<char*>(&indices[i]), sizeof(indices[i]));

		UpdateVertexBuffer();
	}

	void Drawable::UpdateVertexBuffer()
	{
		GetRenderer()->UpdateBuffer(vertex, vertexSize, VBO);
	}

	MaterialManager* Drawable::GetMaterialManager()
	{
		return ServiceProvider::Instance().Get<MaterialManager>();
	}

	Renderer* Drawable::GetRenderer() const
	{
		return ServiceProvider::Instance().Get<Renderer>();
	}
}