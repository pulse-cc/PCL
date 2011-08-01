#ifndef __PCL_NUMERIC_H__
#define __PCL_NUMERIC_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_CLASS(Set):
	LSet(uint InitialLength = 0, bool InitialValue = false);
	LSet(const LSet &Set);
	virtual ~LSet();
	virtual const VSet& operator =(const LSet &Set);
#include "PCL_VSet.hxx"
private:
	LMemory m_set;
	uint m_length;
	uchar m_tailMask;
};

#endif // __PCL_NUMERIC_H__
