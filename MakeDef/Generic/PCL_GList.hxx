#ifndef __PCL_GENERIC_LIST_H__
#define __PCL_GENERIC_LIST_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_GENERIC_CONTAINER(List):
	// Inheritable variables and methods
	pvoid m_head, m_last;
	uint m_itemSize, m_count, m_iterCount;
	VIterator **m_pIter; // Iterator Vector, m_pIter[0] points to default
	virtual VIterator * _CreateIterator(ZFilter pFilter);
	virtual void _RemoveIterator(VIterator * pIter);
	virtual uint _FindIterator(const VIterator& Iter);
	virtual void _InternalSwap(pvoid pItem1, pvoid pItem2);

#include "PCL_VList.hxx"
#include "PCL_VIterator.hxx"
};

#endif // __PCL_GENERIC_LIST_H__