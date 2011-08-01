#ifndef __PCL_STRING_H__
#define __PCL_STRING_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_GENERIC_CONTAINER(String):
	LMemory m_data, m_clip;
	ustr m_uni;
	struct {
		uint Found;
		uint Len;
		ZPosition Pos;
		uint Mode;
	} m_last;
	virtual uint _FindNext(void);
	virtual uint _FindAny(void);
	virtual uint _FindNot(void);

#include "PCL_VString.hxx"

};

PCL_CONTAINER_OF(GString, String):
	LString(cstr Body = NULL);
	LString(LString &Copy);
	virtual ~LString();
	// Asignments
	virtual const VString& operator =(LString& Src);
	virtual const VString& operator =(cstr Src) PCL_PURE;
	virtual const VString& operator +=(cstr Src) PCL_PURE;
	virtual const VString& operator ^=(cstr Src) PCL_PURE;

protected:
	// Inheritable variables and methods
	inline uint InitialLen() {return 80;}; // Long Live Punch Cards !!!
};

#endif // __PCL_STRING_H__
