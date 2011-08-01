///!
///! CallBacks: 
///!	Methods to be Overrided in Descendant Classes (doing nothing by default)
///!
protected:
	virtual void AfterInsert(pvoid pItem, uint ItemSize) PCL_PURE;
	virtual void BeforeRemove(pvoid pItem, uint ItemSize) PCL_PURE;
///!
///! Public Methods
///!
public:
	// Iterator Management
	virtual VIterator& NewIterator(ZFilter pFilter = NULL) PCL_PURE;
	virtual void DeleteIterator(const VIterator& Iter) PCL_PURE;
	// Insert/Remove
	virtual void Insert(ZPosition Pos, pvoid pItem, uint ItemSize = 0) PCL_PURE;
	virtual bool Remove(ZPosition Pos) PCL_PURE; // false if list is empty
	virtual void RemoveAll() PCL_PURE;
	// Reordering
	virtual void SwapWith(
		ZPosition Pos,
		const VIterator& Iter = *ZDefaultIterator
	) PCL_PURE;
	virtual void Swap(
		const VIterator& Iter1,
		const VIterator& Iter2 = *ZDefaultIterator
	) PCL_PURE;
	virtual void SortAsc(ZSortOrder Greater) PCL_PURE;

