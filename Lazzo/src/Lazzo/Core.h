#pragma once

#ifdef LZ_PLATFORM_WINDOWS
	#ifndef LZ_BUILD_DLL
		#define LAZZO_API __declspec(dllimport)
	#else
		#define LAZZO_API __declspec(dllexport)
	#endif
#else
	#error Lazzo only supports Windows!
#endif

#define BIT(x) (1<<x)
