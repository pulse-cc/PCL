#ifndef __PCL_LIST_H__
#define __PCL_LIST_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_CONTAINER_OF(GList, List):
	LList(uint ItemSize);
	virtual ~LList();

	// Insert/Remove
	virtual void Insert(ZPosition Pos, pvoid pItem, uint ItemSize = 0);
	virtual bool Remove(ZPosition Pos); // false if list is empty
	virtual void RemoveAll();

	// Inheritable variables and methods
protected:
	virtual VIterator * _CreateIterator(ZFilter pFilter);
	virtual void _RemoveIterator(VIterator * pIter);
};

typedef struct PCL_ListHeader {
	PCL_ListHeader * pNext;
	PCL_ListHeader * pPrev;
} ZListHeader, *pZListHeader;

#endif // __PCL_LIST_H__