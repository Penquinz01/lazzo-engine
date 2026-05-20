#pragma once

#ifdef LZ_PLATFORM_WINDOWS
	#ifdef LZ_BUILD_DLL
		#define LZ_API __declspec(dllexport)
	#else
		#define LZ_API __declspec(dllimport)
	#endif 
#else 
	#error Lazzo only supports Windows!
#endif
