#pragma once

#pragma warning(push, 0) //disable warnings for external headers
#include "Beetle/Core/Core.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Beetle {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternio)
{
	return os << glm::to_string(quaternio);
}

//core log macros
#define BT_CORE_TRACE(...) ::Beetle::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define BT_CORE_INFO(...)  ::Beetle::Log::GetCoreLogger()->info(__VA_ARGS__);
#define BT_CORE_WARN(...)  ::Beetle::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define BT_CORE_ERROR(...) ::Beetle::Log::GetCoreLogger()->error(__VA_ARGS__);
#define BT_CORE_CRITICAL(...) ::Beetle::Log::GetCoreLogger()->critical(__VA_ARGS__);

//client log macros
#define BT_TRACE(...)      ::Beetle::Log::GetClientLogger()->trace(__VA_ARGS__);
#define BT_INFO(...)       ::Beetle::Log::GetClientLogger()->info(__VA_ARGS__);
#define BT_WARN(...)       ::Beetle::Log::GetClientLogger()->warn(__VA_ARGS__);
#define BT_ERROR(...)      ::Beetle::Log::GetClientLogger()->error(__VA_ARGS__);
#define BT_CRITICAL(...)   ::Beetle::Log::GetClientLogger()->critical(__VA_ARGS__);


