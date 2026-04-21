#pragma once

#include <memory>

#ifdef BT_PLATFORM_WINDOWS
#if BT_DYNAMIC_LINK
	#ifdef BT_BUILD_DLL
		#define BEETLE_API __declspec(dllexport)
	#else
		#define BEETLE_API __declspec(dllimport)
	#endif
#else
	#define BEETLE_API
#endif
#else
	#error Beetle only supports Windows!
#endif // BT_BUILD_DLL

#ifndef IMGUI_API
	#define IMGUI_API BEETLE_API
#endif

#ifdef BT_DEBUG
#define BT_ENABLE_ASSERTS
#endif // BT_DEBUG


#ifdef BT_ENABLE_ASSERTS
	#define BT_ASSERT(x, ...) { if(!(x)) { BT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BT_CORE_ASSERT(x, ...) { if(!(x)) { BT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BT_ASSERT(x, ...)
#define BT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define BEETLE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Beetle {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	
}