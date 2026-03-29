#pragma once

#ifdef BT_PLATFORM_WINDOWS
	#ifdef BT_BUILD_DLL
		#define BEETLE_API __declspec(dllexport)
	#else
		#define BEETLE_API __declspec(dllimport)
	#endif
#else
	#error Beetle only supports Windows!
#endif // BT_BUILD_DLL