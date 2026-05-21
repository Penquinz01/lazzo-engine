#pragma once
#include <memory>
#include "Core.h"
#include <spdlog/spdlog.h>


namespace Lazzo
{

	class LAZZO_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	};
}


//Core Log macros
#define LZ_CORE_ERROR(...)		::Lazzo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LZ_CORE_WARN(...)		::Lazzo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LZ_CORE_INFO(...)		::Lazzo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LZ_CORE_TRACE(...)		::Lazzo::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client Log macros
#define LZ_ERROR(...)			::Lazzo::Log::GetClientLogger()->error(__VA_ARGS__)
#define LZ_WARN(...)			::Lazzo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LZ_INFO(...)			::Lazzo::Log::GetClientLogger()->info(__VA_ARGS__)
#define LZ_TRACE(...)			::Lazzo::Log::GetClientLogger()->trace(__VA_ARGS__)

