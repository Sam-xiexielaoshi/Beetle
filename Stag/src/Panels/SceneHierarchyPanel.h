#pragma once
#include "Beetle/Scene/Scene.h"
#include "Beelte/Core/Log.h"
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
		Ref<Scene>m_Context;
	};
}