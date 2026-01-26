#pragma once

#include "../ImGuiClassState.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"

class MeshImGui : public ImGuiClassState
{
private:

	EntityManager* GetEntityManager();

	VertexData* currentVertex;

public:

	MeshImGui();
	~MeshImGui();

	void Update() override;
};

