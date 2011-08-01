#ifndef __PCL_COLLECTION_H__
#define __PCL_COLLECTION_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

typedef struct PCL_CollectionHeader {
	uint itemSize;
	LMemory *pMem;
} ZCollectionHeader, *pZCollectionHeader;

class PCL_API _WCollectionHeader : public LVector {
public:
	_WCollectionHeader();
	~_WCollectionHeader();
	void AfterInsert(pvoid pItem, uint ItemSize);
	void BeforeRemove(pvoid pItem, uint ItemSize);
	pvoid m_pItem;
	uint m_itemSize;
	LException *m_pDbg;
};

PCL_CONTAINER_OF(GList, Collection):
	friend class LCollectionIterator;
	LCollection();
	virtual ~LCollection();

	// Iterator Management
	virtual VIterator& NewIterator(ZFilter pFilter);
	virtual void DeleteIterator(const VIterator& Iter);
	// Insert/Remove
	virtual void Insert(ZPosition Pos, pvoid pItem, uint ItemSize);
	virtual bool Remove(ZPosition Pos); // false if list is empty
	virtual void RemoveAll();
	// Reordering
	virtual void SwapWith(
		ZPosition Pos,
		const VIterator& Iter = *ZDefaultIterator
	);
	virtual void Swap(
		const VIterator& Iter1,
		const VIterator& Iter2 = *ZDefaultIterator
	);
	virtual void SortAsc(ZSortOrder Greater);
/*	// List Navigation
	virtual void Reset(); // force to point to nothing
	virtual void SetTo(ZPosition Pos);
	virtual bool SetToIndex(int Index);
	virtual bool Move(ZDirection Dir);
*/	// List Access
	virtual void GetCurrent(pvoid *ppItem) const;
	virtual pvoid operator ()() const; // operator form of GetCurrent
	virtual void Get(ZPosition Pos, pvoid *ppItem) const;
	virtual pvoid operator [](ZPosition Pos) const;
	virtual void GetByIndex(int Index, pvoid *ppItem) const;
	virtual pvoid operator [](int Index) const;
	// List Information
	virtual uint Count() const;
	virtual uint ItemSize() const; // returns size of the current item
//	virtual bool IsValid() const; // true if currently points to data
//	virtual bool IsAt(ZPosition Pos) const;
	virtual uint ItemSizeByIndex(int Index) const;
	virtual uint ItemSizeAt(ZPosition Pos) const;
	// Collection-specific method
	virtual void SetItemSize(
		uint NewSize, 
		const VIterator& Iter = *ZDefaultIterator
	);
//
	// Inheritable variables and methods
protected:
	virtual VIterator * _CreateIterator(ZFilter pFilter = NULL);
	virtual void _RemoveIterator(VIterator * pIter);
private:
	_WCollectionHeader m_cHdr;
};

#endif // __PCL_COLLECTION_H__