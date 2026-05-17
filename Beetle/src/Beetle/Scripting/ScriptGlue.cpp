#include "btpch.h"
#include "ScriptGlue.h"
#include "ScriptEngine.h"

#include "Beetle/Core/UUID.h"
#include "Beetle/Core/Input.h"
#include "Beetle/Core/KeyCodes.h"

#include "Beetle/Scene/Scene.h"
#include "Beetle/Scene/Entity.h"

#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"

#include "box2d/b2_body.h"


namespace Beetle {
	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

#define BT_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Beetle.InternalCalls::" #Name, Name)

	static void NativeLog(MonoString* string, int parameter)
	{
		char* cStr = mono_string_to_utf8(string);
		std::string str(cStr);
		std::cout << str << ", " << parameter;
	}

	static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
	{
		BT_CORE_WARN("Value: {0}, {1}, {2}",
			parameter->x,
			parameter->y,
			parameter->z);
		*outResult = *parameter + glm::normalize(*parameter);
	}

	static float NativeLog_VectorDot(glm::vec3* paramter)
	{
		BT_CORE_WARN("Value: {0}, {1}, {2}",
			paramter->x,
			paramter->y,
			paramter->z);
		return glm::dot(*paramter, *paramter);
	}

	static void Entity_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();

		Entity entity = scene->GetEntityByUUID(entityID);
		*outTranslation = entity.GetComponent<TransformComponent>().Translation ;

	}

	static void Entity_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);
		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static bool Input_IsKeyDown(int keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	void ScriptGlue::RegisterFunctions()
	{
		BT_ADD_INTERNAL_CALL(NativeLog);
		BT_ADD_INTERNAL_CALL(NativeLog_Vector);
		BT_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		BT_ADD_INTERNAL_CALL(Entity_GetTranslation);
		BT_ADD_INTERNAL_CALL(Entity_SetTranslation);

		BT_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}


