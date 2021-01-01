#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Nocturnal
{
	class NOCTURNAL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	};
}


//Core Logging Macros
#define NOC_CORE_INFO(...)  ::Nocturnal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NOC_CORE_TRACE(...) ::Nocturnal::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NOC_CORE_WARN(...)  ::Nocturnal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NOC_CORE_ERROR(...) ::Nocturnal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NOC_CORE_FATAL(...) ::Nocturnal::Log::GetCoreLogger()->critical(__VA_ARGS__)


//Client Logging Macros
#define NOC_INFO(...)  ::Nocturnal::Log::GetClientLogger()->info(__VA_ARGS__)
#define NOC_TRACE(...) ::Nocturnal::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NOC_WARN(...)  ::Nocturnal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NOC_ERROR(...) ::Nocturnal::Log::GetClientLogger()->error(__VA_ARGS__)
#define NOC_FATAL(...) ::Nocturnal::Log::GetClientLogger()->critical(__VA_ARGS__)
