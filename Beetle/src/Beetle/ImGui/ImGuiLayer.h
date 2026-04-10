#pragma once

#include "Beetle/Layer.h"

#include "Beetle/Events/MouseEvent.h"
#include "Beetle/Events/KeyEvent.h"
#include "Beetle/Events/ApplicationEvent.h"

namespace Beetle {

	class BEETLE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time{0.0f};
	};
}