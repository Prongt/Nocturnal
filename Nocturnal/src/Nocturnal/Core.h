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


#ifdef NOC_DEBUG
#define NOC_ENABLE_ASSERTS 
#endif

#ifdef NOC_ENABLE_ASSERTS 
	#define NOC_ASSERT(x, ...) { if (!(x)) { NOC_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
	#define NOC_CORE_ASSERT(x, ...) { if (!(x)) { NOC_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define NOC_ASSERT(x, ...)
	#define NOC_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << (x))

#define NOC_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)

