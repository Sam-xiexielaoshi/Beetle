#pragma once
#include <entt.hpp>
#include "Beetle/Core/TimeStamp.h"

namespace Beetle {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void OnUpdate(TimeStamp ts);
	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}