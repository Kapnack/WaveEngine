#pragma once

#include "ServiceProvider/Service.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window/Window.h"
#include "TextureImporter/TextureImporter.h"
#include "VertexData.h"
#include "Material/Material.h"

class Renderer final : public Service
{
private:

	unsigned int shapeShaders;
	unsigned int spriteShaders;

	unsigned int drawCalls = 0;

	glm::mat4* view;
	glm::mat4* proj;

	void Init();
	void Unload();

	unsigned int defualtTextureID = 0;

	const unsigned int ReturnWorkingMaterial(const unsigned int& materialIDToTry, const unsigned int& materialIDfallBack);

	Window* GetWindow();

	MaterialManager* GetMaterialManager();

	TextureManager* GetTextureManager();

	Texture* ChooseTextureToUse(const unsigned int& ID);

public:

	Renderer();
	~Renderer();

	void CreateBuffers(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const;
	void CreateBuffersSprite(const VertexData* vertex, const int& vertexSize, const int* indices, const int& indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO) const;

	void DeleteBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

	void UpdateBuffer(VertexData* vertex, int vertexSize, unsigned& VBO);

	void Clear();

	unsigned int GetDrawCalls();

	void DrawElement(glm::mat4& model, const unsigned int& materialID, const unsigned int& indicesSize, const unsigned int& VAO);
	void DrawElementSprite(glm::mat4& model, const unsigned int& materialID, const unsigned int& indicesSize, const unsigned int& VAO, const unsigned int& texture);
};

