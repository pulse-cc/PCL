#ifndef __PCL_TYPES_H__
#define __PCL_TYPES_H__

#if !defined(__PCL_H__) && !defined(__PCL_IDL_H__)
#	error Do not include this file directly. Include "PCL.h"/"PCL_IDL.h" instead
#endif
///!===========================================================================!
///!
///! Fundamental Data Types
///!
typedef void *pvoid;
// char
NON_IDL(typedef char *pchar;)
typedef unsigned char uchar, *puchar;
// short
typedef signed short sshort, *pshort, *psshort;
typedef unsigned short ushort, *pushort;
// int
typedef signed int sint, *pint, *psint;
typedef unsigned int uint, *puint;
// long
typedef signed long slong, *plong, *pslong;
typedef unsigned long ulong, *pulong;
// float
typedef float *pfloat;
// double
typedef double *pdouble;
// strings
NON_IDL(typedef const char *cstr;)
typedef unsigned short *ustr, **pustr;

///!===========================================================================!
///!
///! Special Values In Unsigned Integer Arithmetic
///!
const uint ZUintInvalid = 0xFFFFFFFFuL;
///! Assertion U1 (wrong ordering):
///!	ZUintInvalid + 1 < ZUintInvalid
const uint ZUintMax = 0xFFFFFFFEuL;
///! Assertion U2 (derived from U1):
///!	ZUintMax + 1 == ZUintInvalid
const uint ZUintMin = 0x0uL;
///! Assertion U3 (derived from U1):
///!	ZUintMin - 1 == ZUintInvalid
///!===========================================================================!
///!
///! Special Values In Signed Integer Arithmetic
///!
const sint ZSintInvalid = 0x80000000L;
///! Assertion S1 (wrong ordering):
///!	ZSintInvalid - 1 > ZSintInvalid
///! Assertion S2 (another zero):
///!	-ZSintInvalid == ZSintInvalid
const sint ZSintMax = 0x7FFFFFFFL;
///! Assertion S3 (derived from S1 or S2):
///!	ZSintMax + 1 == ZSintInvalid
const sint ZSintMin = 0x80000001L;
///! Assertion S4:
///!	ZSintMin - 1 == ZSintInvalid

#ifndef PCL_HIDE_STRUCTURES
///!===========================================================================!
///!
///! Serialized Container Type
///!
typedef struct PCL_Container {
	uint dataSize;	// Total size of the container (including the header)
	uint classCode;	// PCL actual class code (probably generic)
	IDL_ONLY([size_is(dataSize - (sizeof(uint)<<1))] uchar data[*];)
} ZContainer, *pZContainer;
typedef IDL_ATTRIBUTE(public) ZContainer *pcont;
///!===========================================================================!
///!
///! Generic Item Descriptor
///!
typedef struct PCL_Descriptor {
	uint ClassCode;	// PCL class code (ZUintInvalid or 0 if unknown)
	uint Size;		// Size in uchar's of memory chunk pointed by Addr
	IDL_ATTRIBUTE(size_is(Size)) puchar Addr;
	uint Info;		// User defined tag (0 if unused)
} ZDescriptor, ZItem, *pZItem, *pZDescriptor;
typedef IDL_ATTRIBUTE(public) ZDescriptor *pdescr;

#endif // PCL_HIDE_STRUCTURES

#endif // __PCL_TYPES_H__
