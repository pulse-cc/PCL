#ifndef __PCL_IDL_H__
#define __PCL_IDL_H__
///!
///! PCL stands for Portable Class Library and is designed for
///! development of applications portable between different
///! environments (first of all between MS Windows and GNU Linux)
///!
///! CopyFree Pulse Computer Consulting, 2001 - 2003
///!
#include "PCL_Define.h"

#ifdef PCL_IDL_EXPOSE_TYPES
#	include "PCL_Types.h"
#endif

#ifdef PCL_IDLPASS
	import "pclidl.idl";
	import "oaidl.idl";
	import "ocidl.idl";
#endif


#endif // __PCL_IDL_H__