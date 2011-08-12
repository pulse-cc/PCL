#ifndef __PCL_DEFINE_H__
#define __PCL_DEFINE_H__

#if !defined(__PCL_H__) && !defined(__PCL_IDL_H__)
#	error Do not include this file directly. Include "PCL.h"/"PCL_IDL.h" instead
#endif

// Configuration constants
#define PCL_OS_MICROSOFT 1
#define PCL_OS_LINUX 2

#define PCL_UI_WINDOWS 1
#define PCL_UI_CONSOLE 2

#define PCL_COMPILER_MSVC 1
#define PCL_COMPILER_MIDL 2
#define PCL_COMPILER_GCC 3

#define PCL_LIBRARY_STATIC 1
#define PCL_LIBRARY_DYNAMIC 2
#define PCL_LIBRARY_SERVER 3

// Definitions
#define PCL_VERMAJOR 1
#define PCL_VERMINOR 15
#define PCL_PURE =0
#define PCL_PREFIX 0xC0DA0000uL
#define PCL_CONTAINER_MASK 0x00010000uL

// Conditionals
#ifdef NDEBUG
#	define PCL_ISDEBUG false
#else
#	define PCL_ISDEBUG true
#endif

#ifdef PCL_IMPLEMENTATION
#	define PCL_API PCL_API_IMP
#else
#	define PCL_API PCL_API_USE
#endif

// Some useful macrodefinitions
#define PCL_STRING(x) #x
#define countof(x) (sizeof(x) / sizeof(x[0]))

// IDL-related definitions
#ifdef PCL_IDLPASS
#	define IDL_ATTRIBUTE(x) [x]
#	define IDL_METHOD(x) [helpstring(PCL_STRING(method ::##x))] HRESULT x
#	define NON_IDL(x) /*NON_IDL:x*/
#	define IDL_ONLY(x) x
#else // Non-IDL definitions
#	define IDL_ATTRIBUTE(x) /*[x]*/
#	define IDL_METHOD(x) STDMETHOD(x)
#	define NON_IDL(x) x
#	define IDL_ONLY(x) /*IDL_ONLY:x*/
#endif
#define IDL_METHOD_IMPL(c,x) STDMETHODIMP c::x

#endif // __PCL_DEFINE_H__
