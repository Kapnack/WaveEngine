#include "MaterialsImGui.h"

#include <ImGui/imgui.h>

#include "ServiceProvider/ServiceProvider.h"
#include "Material/Material.h"

MaterialsImGui::MaterialsImGui() : ImGuiClassState()
{
}

MaterialsImGui::~MaterialsImGui()
{
}

MaterialManager* MaterialsImGui::GetMaterialManager()
{
	return ServiceProvider::Instance().Get<MaterialManager>();
}

MaterialFactory* MaterialsImGui::GetMaterialFactory()
{
	return ServiceProvider::Instance().Get<MaterialFactory>();
}

FileReader* MaterialsImGui::GetFileReader()
{
	return ServiceProvider::Instance().Get<FileReader>();
}

void MaterialsImGui::Update()
{

	ImGui::Combo("Material Creation Method", &current, items, IM_ARRAYSIZE(items));


	if (current == 1)
	{
		text = "Import Material";
		ImGui::Text(text.c_str());

		ImGui::InputText("Material Name", newMaterialName.data(), newMaterialName.capacity() + 1, ImGuiInputTextFlags_CallbackResize, ResizeCallback, &newMaterialName);

		ImGui::Checkbox("Vertex Add Absolute Path", &addAbsoluteToVertexPath);
		ImGui::SameLine();
		ImGui::InputText("Vertex Shader", vertexShaderPath.data(), vertexShaderPath.capacity() + 1, ImGuiInputTextFlags_CallbackResize, ResizeCallback, &vertexShaderPath);

		ImGui::Checkbox("Fragment Add Absolute Path", &addAbsoluteToFragmentPath);
		ImGui::SameLine();
		ImGui::InputText("Fragment Shader", fragmentShaderPath.data(), fragmentShaderPath.capacity() + 1, ImGuiInputTextFlags_CallbackResize, ResizeCallback, &fragmentShaderPath);

		if (ImGui::Button("Import Material"))
		{
			string fileVertexShader;
			string fileFragmentShader;

			fileVertexShader = addAbsoluteToVertexPath ? GetFileReader()->ReadFileAbsolutePath(vertexShaderPath) : GetFileReader()->ReadFile(vertexShaderPath);
			fileFragmentShader = addAbsoluteToFragmentPath ? GetFileReader()->ReadFileAbsolutePath(fragmentShaderPath) : GetFileReader()->ReadFile(fragmentShaderPath);

			GetMaterialFactory()->CreateMaterial(newMaterialName, fileVertexShader, fileFragmentShader);
		}

	}
	else if(current == 2)
	{
		text = "Create Material";
		ImGui::Text(text.c_str());

		ImGui::InputText("Material Name", newMaterialName.data(), newMaterialName.capacity() + 1, ImGuiInputTextFlags_CallbackResize, ResizeCallback, &newMaterialName);

		ImGui::InputTextMultiline("Vertex Shader",
			vertexShader.data(), vertexShader.capacity() + 1,
			textBoxSize, ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackResize, ResizeCallback, &vertexShader);

		ImGui::InputTextMultiline("Fragment Shader",
			fragmentShader.data(), fragmentShader.capacity() + 1,
			textBoxSize, ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackResize, ResizeCallback, &fragmentShader);

		if (ImGui::Button("Create Material"))
			GetMaterialFactory()->CreateMaterial(newMaterialName, vertexShader, fragmentShader);
	}

	ImGui::Separator();

	text = "Delete by Name";
	ImGui::Checkbox(text.c_str(), &deleteByName);

	if (!deleteByName)
	{
		text = "Input Material ID";

		ImGui::InputInt(text.c_str(), &materialID);
	}
	else
	{
		text = "Input Material Name";

		ImGui::InputText(text.c_str(), materialName, sizeof(materialName));
	}

	text = "Delete Material";
	if (ImGui::Button(text.c_str()))
		if (!deleteByName)
			GetMaterialManager()->DeleteMaterial(materialID);
		else
			GetMaterialManager()->DeleteMaterial(materialName);


	for (auto it : GetMaterialManager()->GetMaterials())
	{
		if (it.second == nullptr)
			continue;

		text = "Name: " + it.second->GetName() + ". ID: " + to_string(it.first) + ". Program ID: " + to_string(it.second->GetProgram()) + ".";

		ImGui::ColorEdit4(text.c_str(), &it.second->color.x);
		ImGui::Separator();
	}

}
