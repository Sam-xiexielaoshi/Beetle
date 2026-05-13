#include "btpch.h"
#include "ScriptGlue.h"

#include "mono/metadata/object.h"


namespace Beetle {

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

	void ScriptGlue::RegisterFunctions()
	{
		BT_ADD_INTERNAL_CALL(NativeLog);
		BT_ADD_INTERNAL_CALL(NativeLog_Vector);
		BT_ADD_INTERNAL_CALL(NativeLog_VectorDot);
	}

}


