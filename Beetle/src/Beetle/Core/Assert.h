#pragma once

#include "Beetle/Core/Core.h"
#include "Beetle/Core/Log.h"
#include <filesystem>

#ifdef BT_ENABLE_ASSERTS

#define BT_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { BT##type##ERROR(msg, __VA_ARGS__); BT_DEBUGBREAK(); } }
#define BT_INTERNAL_ASSERT_WITH_MSG(type, check, ...) BT_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define BT_INTERNAL_ASSERT_NO_MSG(type, check) BT_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", BT_STRINGIFY_MACRO(check), srd::filesystem::path(__FILE__).filename().string(), __LINE__)

#define BT_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define BT_INTERNAL_ASSERT_GET_MACRO(...) BT_EXPAND_MACRO( BT_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, BT_INTERNAL_ASSERT_WITH_MSG, BT_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
#define BT_ASSERT(...) BT_EXPAND_MACRO( BT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define BT_CORE_ASSERT(...) BT_EXPAND_MACRO( BT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define BT_ASSERT(...)
#define BT_CORE_ASSERT(...)

#endif