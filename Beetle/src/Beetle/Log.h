#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Beetle {

	class BEETLE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

//core log macros
#define BT_CORE_TRACE(...) ::Beetle::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define BT_CORE_INFO(...)  ::Beetle::Log::GetCoreLogger()->info(__VA_ARGS__);
#define BT_CORE_WARN(...)  ::Beetle::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define BT_CORE_ERROR(...) ::Beetle::Log::GetCoreLogger()->error(__VA_ARGS__);
#define BT_CORE_FATAL(...) ::Beetle::Log::GetCoreLogger()->fatal(__VA_ARGS__);

//client log macros
#define BT_TRACE(...)      ::Beetle::Log::GetClientLogger()->trace(__VA_ARGS__);
#define BT_INFO(...)       ::Beetle::Log::GetClientLogger()->info(__VA_ARGS__);
#define BT_WARN(...)       ::Beetle::Log::GetClientLogger()->warn(__VA_ARGS__);
#define BT_ERROR(...)      ::Beetle::Log::GetClientLogger()->error(__VA_ARGS__);
#define BT_FATAL(...)      ::Beetle::Log::GetClientLogger()->fatal(__VA_ARGS__);


