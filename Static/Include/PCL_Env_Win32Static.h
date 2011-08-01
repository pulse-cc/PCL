#ifndef __PCL_ENV_WIN32STATIC_H__
#define __PCL_ENV_WIN32STATIC_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

#include <stdlib.h>
#include <stdio.h>
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#ifndef _WIN32_WINNT
#	define _WIN32_WINNT 0x0400
#endif
#include <windows.h>
#include <objbase.h>
#include <winerror.h>
#define PCL_API_IMP
#define PCL_API_USE

#define PCL_DESCRIPTION "Win32 LIB"

#endif // __PCL_ENV_WIN32STATIC_H__