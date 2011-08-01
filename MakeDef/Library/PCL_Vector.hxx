#ifndef __PCL_VECTOR_H__
#define __PCL_VECTOR_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_CONTAINER_OF(GList, Vector):
	LVector(uint ItemSize);
	virtual ~LVector();

	// Insert/Remove
	virtual void Insert(ZPosition Pos, pvoid pItem, uint ItemSize = 0);
	virtual bool Remove(ZPosition Pos); // false if list is empty
	virtual void RemoveAll();

	// Inheritable variables and methods
	virtual void CollectGarbage(); // make Realloc() to force m_allocCount == m_count
protected:
	virtual VIterator * _CreateIterator(ZFilter pFilter);
	virtual void _RemoveIterator(VIterator * pIter);
	inline uint BlockCount() {return 16;};
	uint m_allocCount;
};

#endif // __PCL_VECTOR_H__
