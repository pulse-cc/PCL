#ifndef __PCL_CONFIG_H__
#define __PCL_CONFIG_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

// Configuration
#define PCL_OS PCL_OS_MICROSOFT
#define PCL_WORDBITS 32 //(sizeof(int) << 3)
#define PCL_UI PCL_UI_WINDOWS
#define PCL_COMPILER PCL_COMPILER_MSVC
#define PCL_LIBRARY_TYPE PCL_LIBRARY_DYNAMIC

#endif // __PCL_CONFIG_H__