#include "MaterialsImGui.h"

#include <ImGui/imgui.h>

#include "ServiceProvider/ServiceProvider.h"
#include "Material/Material.h"

namespace WaveEngine
{
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
			ImGui::Text("Import Material");

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

				fileVertexShader = addAbsoluteToVertexPath ? GetFileReader()->ReadFile(vertexShaderPath) : GetFileReader()->ReadFile(vertexShaderPath);
				fileFragmentShader = addAbsoluteToFragmentPath ? GetFileReader()->ReadFile(fragmentShaderPath) : GetFileReader()->ReadFile(fragmentShaderPath);

				GetMaterialFactory()->CreateMaterial(newMaterialName, fileVertexShader, fileFragmentShader);
			}

		}
		else if (current == 2)
		{
			ImGui::Text("Create Material");

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

		ImGui::Checkbox("Delete by Name", &deleteByName);

		if (!deleteByName)
		{
			ImGui::InputInt("Input Material ID", &materialID);
		}
		else
		{
			ImGui::InputText("Input Material Name", materialName, sizeof(materialName));
		}

		if (ImGui::Button("Delete Material"))
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
}