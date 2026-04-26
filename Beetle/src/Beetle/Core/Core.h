#pragma once

#include <memory>

#include "Beetle/Core/PlatformDetection.h"


#ifdef BT_DEBUG
#if defined(BT_PLATFORM_WINDOWS)
#define BT_DEBUGBREAK() __debugbreak()
#elif defined(BT_PLATFORM_LINUX)
#include <signal.h>
#define BT_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define BT_ENABLE_ASSERTS
#else
#define BT_DEBUGBREAK()
#endif
#define BT_EXPAND_MACRO(x) x
#define BT_STRINGIFY_MACRO(x) #x

#define BIT(x) (1<<x)

#define BEETLE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Beetle {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Beetle/Core/Log.h"
#include "Beetle/Core/Assert.h"