#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>
#include "Beetle/Scene/Components.h"

namespace Beetle{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context.get()}; 

			auto& tag = entity.GetComponent<TagComponent>();
			ImGui::Text("%s", tag.c_str());
		});

		ImGui::End();
	}
}