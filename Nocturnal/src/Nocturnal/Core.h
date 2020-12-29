#pragma once

#ifdef NOC_PLATFORM_WINDOWS
	#ifdef NOC_BUILD_DLL
		#define NOCTURNAL_API __declspec(dllexport)
	#else
		#define NOCTURNAL_API __declspec(dllimport)
	#endif
#else
	#error Noctural currently only supports Windows
#endif


#define BIT(x) (1 << (x))