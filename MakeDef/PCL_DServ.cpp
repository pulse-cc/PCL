#define PCL_GENDEFRUN
#define __PCL_H__
#include "PCL_License.h"
#include "PCL_Internal.h"

#define PCL_PURE =0
///!
///! Virtual Exception
///!
///! Global Scope Definitions:
///!
PCL_ENUMERATOR(ExceptionMode)
	ZIgnore = 0,
///!
	ZLog	= 0x1,			// Write to LOG File
	ZOutput	= ZLog << 1,	// Write to Console
	ZDebug	= ZOutput << 1,	// Use OutputDebugString in Win32 and ??? in Linux
	ZShow	= ZDebug << 1,	// Display MessageBox
	ZQuery	= ZShow << 1,	// Display dialog allowing end user mode change
	ZThrow	= ZQuery << 1,	// Throw C++ exception
///!
	ZAbort = 0x80000000uL
} ZExceptionMode;
PCL_VIRTUAL_CLASS(Exception):
#include "PCL_VException.hxx"
};
#undef PCL_PURE
#define PCL_PURE /**/
///!===========================================================================!
///!
///! Definition of Exception
///!
#include "PCL_Exception.hxx"
///!===========================================================================!
///!
///! Definition of common library functions
///!
PCL_ENUMERATOR(OutputFile)
	ZStdOut,
	ZStdErr,
	ZCustomOut
} ZOutputFile;

#include "PCL_Service.hxx"
