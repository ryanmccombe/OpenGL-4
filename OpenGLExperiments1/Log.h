#pragma once
#include "spdlog/spdlog.h"
#include <memory>

class Log
{
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; };

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};

#define MINIMUM_LOG_LEVEL 1

#if MINIMUM_LOG_LEVEL < 1
  #define LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#else
  #define LOG_TRACE
#endif

#if MINIMUM_LOG_LEVEL < 2
	#define LOG_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
#else
	#define LOG_INFO
#endif

#if MINIMUM_LOG_LEVEL < 3
	#define LOG_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
#else
	#define LOG_WARN
#endif

#if MINIMUM_LOG_LEVEL < 4
	#define LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#else
	#define LOG_ERROR
#endif

#if MINIMUM_LOG_LEVEL < 5
	#define LOG_FATAL(...) ::Log::GetLogger()->fatal(__VA_ARGS__)
#else
	#define LOG_FATAL
#endif