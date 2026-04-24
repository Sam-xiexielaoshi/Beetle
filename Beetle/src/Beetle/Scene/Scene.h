#pragma once
#include "entt.hpp"
#include "Beetle/Core/TimeStamp.h"

namespace Beetle {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& GetRegistry() { return m_Registry; }

		void OnUpdate(TimeStamp ts);
	private:
		entt::registry m_Registry;
	};
}