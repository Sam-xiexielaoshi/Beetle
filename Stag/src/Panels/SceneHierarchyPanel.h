#pragma once
#include "Beetle/Scene/Scene.h"
#include "Beetle/Core/Core.h"
#include "Beetle/Scene/Entity.h"

namespace Beetle {
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene>m_Context;
		Entity m_SelectionContext;
	};
}