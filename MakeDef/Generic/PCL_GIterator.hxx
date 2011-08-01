#ifndef __PCL_GENERIC_ITERATOR_H__
#define __PCL_GENERIC_ITERATOR_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_GENERIC_CLASS(Iterator):
	// Inheritable variables and methods
	VList *m_list;
	uint m_index;
	ZFilter m_pFilter;
	virtual bool _Move(ZDirection Dir);
	virtual pvoid _MoveToIndex(uint Index);
	virtual void _MoveValid(ZDirection Dir);

	GIterator(VList *List);

#include "PCL_VIterator.hxx"

	// For implementation aids only
	void _IncIndex();
	void _DecIndex();
	void _SetFilter(ZFilter pFilter);
};

#endif // __PCL_GENERIC_ITERATOR_H__