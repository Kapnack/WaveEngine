#include "MaterialManager.h"

#include <GL/glew.h>
#include <algorithm>

#include "FileReader/FileReader.h"

MaterialManager::MaterialManager()
{
}

MaterialManager::~MaterialManager()
{
	for (unordered_map<unsigned int, Material*>::iterator it = materials.begin(); it != materials.end(); ++it)
		delete it->second;

	materials.clear();
}

unsigned int MaterialManager::GetMaterial(const string name)
{
	unordered_map<unsigned int, Material*>::iterator it = find_if(materials.begin(), materials.end(),
		[&name](const pair<const unsigned int, Material*>& entry)
		{
			return entry.second &&
				entry.second->GetName() == name;
		});

	if (it == materials.end())
		return 0;

	return it->first;
}

void MaterialManager::SaveMaterial(const unsigned int id, Material* material)
{
	materials[id] = material;
}

Material* MaterialManager::GetMaterial(const unsigned int id)
{
	return id != Material::NULL_MATERIAL ? materials[id] : nullptr;
}

unordered_map<unsigned int, Material*>& MaterialManager::GetMaterials()
{
	return materials;
}

void MaterialManager::DeleteMaterial(const string name)
{
	unordered_map<unsigned int, Material*>::iterator it = find_if(materials.begin(), materials.end(),
		[&name](const pair<const unsigned int, Material*>& entry)
		{
			return entry.second &&
				entry.second->GetName() == name;
		});


	if (it == materials.end())
		return;

	OnDeleteMaterial(*it->second);

	delete it->second;
	materials.erase(it);
}

void MaterialManager::DeleteMaterial(const unsigned int id)
{
	if (id == Material::NULL_MATERIAL)
		return;

	Material* it = materials[id];

	if (it == nullptr)
		return;

	OnDeleteMaterial(*it);

	delete it;
	materials.erase(id);
}

void MaterialManager::AddListener(Drawable* entity)
{
	listeners.push_back(entity);
}

void MaterialManager::OnDeleteMaterial(Material& material)
{
	for (Drawable* entity : listeners)
		if (entity->GetMaterial() == material.GetID())
			entity->SetMaterial(Material::NULL_MATERIAL);
}

void MaterialManager::RemoveListener(Drawable* entity)
{
	if (listeners.size() == 0)
		return;

	for (vector<Drawable*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		if (*it == entity)
		{
			listeners.erase(it);
			break;
		}
}

void MaterialManager::ClearListeners()
{
	listeners.clear();
}
