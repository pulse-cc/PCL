#ifndef __PCL_ENVIRONMENT_H__
#define __PCL_ENVIRONMENT_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

#if defined(PCL_GENDEFRUN)
#elif PCL_OS == PCL_OS_MICROSOFT \
	&& PCL_WORDBITS == 32 \
	&& PCL_UI == PCL_UI_WINDOWS \
	&& PCL_LIBRARY_TYPE == PCL_LIBRARY_DYNAMIC
#	include "PCL_Env_Win32DLL.h"
#elif PCL_OS == PCL_OS_MICROSOFT \
	&& PCL_WORDBITS == 32 \
	&& PCL_UI == PCL_UI_WINDOWS \
	&& PCL_LIBRARY_TYPE == PCL_LIBRARY_STATIC
#	include "PCL_Env_Win32Static.h"
#else
#	error Specify Environment
#endif

#endif // __PCL_ENVIRONMENT_H__