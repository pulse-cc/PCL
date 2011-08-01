#ifndef __PCL_GENERIC_MEMADM_H__
#define __PCL_GENERIC_MEMADM_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_GENERIC_CLASS(MemAdm):
	// Inheritable variables and methods
	virtual pvoid _Alloc(uint Size);
	virtual pvoid _Realloc(pvoid ptr, uint Size);
	virtual void _Dealloc(pvoid ptr);

#include "PCL_VMemAdm.hxx"
};

#endif // __PCL_GENERIC_MEMADM_H__
