#include "MeshFactory.h"

#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	MeshFactory::MeshFactory() : Service()
	{
	}

	MeshFactory::~MeshFactory()
	{
	}

	unsigned int MeshFactory::CreateMesh(const string_view name, VertexData* vertexBuffer, unsigned int vertexSize)
	{
		++currentMeshID;

		Mesh* newMesh = new Mesh(vertexBuffer, vertexSize, name, currentMeshID);

		GetMeshManager()->SaveMesh(newMesh, currentMeshID);

		return currentMeshID;
	}

	MeshManager* MeshFactory::GetMeshManager()
	{
		return ServiceProvider::Instance().Get<MeshManager>();
	}
}