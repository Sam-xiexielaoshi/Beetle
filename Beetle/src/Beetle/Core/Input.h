#pragma once

#include <glm/glm.hpp>

#include "Beetle/Core/KeyCodes.h"
#include "Beetle/Core/MouseButtonCodes.h"

namespace Beetle {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}