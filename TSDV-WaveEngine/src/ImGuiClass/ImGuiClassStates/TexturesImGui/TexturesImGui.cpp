#include "TexturesImGui.h"

#include <ImGui/imgui.h>

#include "ServiceProvider/ServiceProvider.h"

TexturesImGui::TexturesImGui() : ImGuiClassState()
{
}

TexturesImGui::~TexturesImGui()
{
}

TextureManager* TexturesImGui::GetTextureManager()
{
	return ServiceProvider::Instance().Get<TextureManager>();
}

TextureImporter* TexturesImGui::GetTextureImporter()
{
	return ServiceProvider::Instance().Get<TextureImporter>();
}

void TexturesImGui::Update()
{
	ImGui::Checkbox("Use Absolute Path", &withAbsolutePath);

	ImGui::InputText("Texture Path", fileTexurePath.data(), fileTexurePath.capacity() + 1, ImGuiInputTextFlags_CallbackResize, ResizeCallback, &fileTexurePath);

	if (ImGui::Button("Import Texture"))
		if (withAbsolutePath)
			GetTextureImporter()->LoadTextureAbsolutePath(fileTexurePath);
		else
			GetTextureImporter()->LoadTexture(string(buf));

	for (auto it : GetTextureManager()->GetTextures())
	{
		if (it.second == nullptr)
			continue;
		
		const string text = "ID: " + to_string(it.second->GetID()) + ". Texture ID: " + to_string(it.second->GetTextureID()) + ".";

		ImGui::Text(text.c_str());
		ImGui::Image(it.second->GetTextureID(), ImVec2(it.second->GetWidth() / 5, it.second->GetHeight() / 5), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Separator();
	}
}
