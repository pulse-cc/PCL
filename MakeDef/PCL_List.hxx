#ifndef __PCL_LIST_H__ 
#define __PCL_LIST_H__ 
#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif
///!
//*!===========================================================================!
//*! PCL stands for Portable Class Library and is designed for development
//*! of applications portable between different environments,
//*! first of all between MS Windows and GNU Linux.
//*!
//*! CopyFree Pulse Computer Consulting, 2001 - 2011
//*!
//*! CopyFree License Agreement:
//*!	1.You may do with this code WHATEVER YOU LIKE.
//*!	2.In NO CASE Pulse Computer Consulting is responsible for your results.
//*!
//*! E-mail: pulse.cc@mail.ru, pulse.cc@gmail.com
//*!===========================================================================!
///!
///!
///! Virtual Iterator (Helper Class for navigation into Virtual Lists)
///!
///! Global Scope Definitions:
///!
typedef enum PCL_Position { ZNullPosition = 0,
	ZHead,
	ZFirst = ZHead,
	ZTop = ZHead,
///!
	ZTail,
	ZLast = ZTail,
	ZBottom = ZTail,
} ZPosition;
///!
typedef enum PCL_Direction { ZNullDirection = 0,
	ZPrev,
	ZUp = ZPrev,
	ZBackward = ZPrev,
///!
	ZNext,
	ZDown = ZNext,
	ZForward = ZNext,
} ZDirection;
static const uint VIteratorClassCode = VIRTUALCODE(false); class VIterator { public:
///!
///! Public Methods
///!
public:
	// List Navigation
	virtual void Reset() =0; // force to point to nothing
	virtual void SetTo(ZPosition Pos) =0;
	virtual bool SetToIndex(int Index) =0;
		// true if current position succesfully set
		// false if invalid index, current position remains unchanged
	virtual bool Move(ZDirection Dir) =0;
		// false if no more items in direction
	// List Access
	virtual void GetCurrent(pvoid *ppItem) const =0;
		// fills *ppItem with NULL if points to nothing
	virtual void Get(ZPosition Pos, pvoid *ppItem) const =0;
		// fills *ppItem with NULL if the list is emplty
	virtual void GetByIndex(int Index, pvoid *ppItem) const =0;
		// fills *ppItem with NULL if index is out of Count
	// List Information
	virtual uint Count() const =0;
		// returns number of items (0 for empty list)
	virtual uint ItemSize() const =0; // returns size of the current item
	virtual uint ItemSizeAt(ZPosition Pos) const =0;
	virtual uint ItemSizeByIndex(int Index) const =0;
	virtual bool IsValid() const =0; // true if currently points to data
	virtual bool IsAt(ZPosition Pos) const =0;
		// true if currently at specified position
///!
///! Public Operators
///!
public:
	virtual pvoid operator ()() const =0;
		// operator form of GetCurrent
	virtual pvoid operator [](ZPosition Pos) const =0;
		// operator form of Get
	virtual pvoid operator [](int Index) const =0;
		// operator form of GetByIndex
};
///!===========================================================================!
///!
///! Virtual List (may be implemented as dynamic array or linked list or ...)
///!
///! Global Scope Definitions:
///!
///!	Pointer to user-defined filter function
typedef bool (*ZFilter)(pvoid pItem); // true if item match criterium
///!	Pointer to user-defined sort ordering function
typedef bool (*ZSortOrder)(pvoid pItem1, pvoid pItem2); // true if Greater
///!	Special reference value indicating default (built-in) iterator
static const VIterator *ZDefaultIterator = NULL;
static const uint VListClassCode = VIRTUALCODE(true); class VList : public VContainer, public VIterator { public:
///!
///! CallBacks: 
///!	Methods to be Overrided in Descendant Classes (doing nothing by default)
///!
protected:
	virtual void AfterInsert(pvoid pItem, uint ItemSize) =0;
	virtual void BeforeRemove(pvoid pItem, uint ItemSize) =0;
///!
///! Public Methods
///!
public:
	// Iterator Management
	virtual VIterator& NewIterator(ZFilter pFilter = NULL) =0;
	virtual void DeleteIterator(const VIterator& Iter) =0;
	// Insert/Remove
	virtual void Insert(ZPosition Pos, pvoid pItem, uint ItemSize = 0) =0;
	virtual bool Remove(ZPosition Pos) =0; // false if list is empty
	virtual void RemoveAll() =0;
	// Reordering
	virtual void SwapWith(
		ZPosition Pos,
		const VIterator& Iter = *ZDefaultIterator
	) =0;
	virtual void Swap(
		const VIterator& Iter1,
		const VIterator& Iter2 = *ZDefaultIterator
	) =0;
	virtual void SortAsc(ZSortOrder Greater) =0;
};
///!===========================================================================!
///!
///! Definition of Generic Iterator & List
///!
static const uint GIteratorClassCode = CLASSCODE(VIteratorClassCode); class PCL_API GIterator : public VIterator { public: static const uint ClassCode() {return GIteratorClassCode;}; protected: GIterator(); virtual ~GIterator(); protected:
	// Inheritable variables and methods
	VList *m_list;
	uint m_index;
	ZFilter m_pFilter;
	virtual bool _Move(ZDirection Dir);
	virtual pvoid _MoveToIndex(uint Index);
	virtual void _MoveValid(ZDirection Dir);
	GIterator(VList *List);
///!
///! Public Methods
///!
public:
	// List Navigation
	virtual void Reset() ; // force to point to nothing
	virtual void SetTo(ZPosition Pos) ;
	virtual bool SetToIndex(int Index) ;
		// true if current position succesfully set
		// false if invalid index, current position remains unchanged
	virtual bool Move(ZDirection Dir) ;
		// false if no more items in direction
	// List Access
	virtual void GetCurrent(pvoid *ppItem) const ;
		// fills *ppItem with NULL if points to nothing
	virtual void Get(ZPosition Pos, pvoid *ppItem) const ;
		// fills *ppItem with NULL if the list is emplty
	virtual void GetByIndex(int Index, pvoid *ppItem) const ;
		// fills *ppItem with NULL if index is out of Count
	// List Information
	virtual uint Count() const ;
		// returns number of items (0 for empty list)
	virtual uint ItemSize() const ; // returns size of the current item
	virtual uint ItemSizeAt(ZPosition Pos) const ;
	virtual uint ItemSizeByIndex(int Index) const ;
	virtual bool IsValid() const ; // true if currently points to data
	virtual bool IsAt(ZPosition Pos) const ;
		// true if currently at specified position
///!
///! Public Operators
///!
public:
	virtual pvoid operator ()() const ;
		// operator form of GetCurrent
	virtual pvoid operator [](ZPosition Pos) const ;
		// operator form of Get
	virtual pvoid operator [](int Index) const ;
		// operator form of GetByIndex
	// For implementation aids only
	void _IncIndex();
	void _DecIndex();
	void _SetFilter(ZFilter pFilter);
};
static const uint GListClassCode = CLASSCODE(VListClassCode); class PCL_API GList : public VList { public: static const uint ClassCode() {return GListClassCode;}; protected: GList(); virtual ~GList(); GList(const pcont pContainer); virtual void Import(const pcont pContainer, bool AutoRelease = true); virtual const pcont Export(void); protected:
	// Inheritable variables and methods
	pvoid m_head, m_last;
	uint m_itemSize, m_count, m_iterCount;
	VIterator **m_pIter; // Iterator Vector, m_pIter[0] points to default
	virtual VIterator * _CreateIterator(ZFilter pFilter);
	virtual void _RemoveIterator(VIterator * pIter);
	virtual uint _FindIterator(const VIterator& Iter);
	virtual void _InternalSwap(pvoid pItem1, pvoid pItem2);
///!
///! CallBacks: 
///!	Methods to be Overrided in Descendant Classes (doing nothing by default)
///!
protected:
	virtual void AfterInsert(pvoid pItem, uint ItemSize) ;
	virtual void BeforeRemove(pvoid pItem, uint ItemSize) ;
///!
///! Public Methods
///!
public:
	// Iterator Management
	virtual VIterator& NewIterator(ZFilter pFilter = NULL) ;
	virtual void DeleteIterator(const VIterator& Iter) ;
	// Insert/Remove
	virtual void Insert(ZPosition Pos, pvoid pItem, uint ItemSize = 0) ;
	virtual bool Remove(ZPosition Pos) ; // false if list is empty
	virtual void RemoveAll() ;
	// Reordering
	virtual void SwapWith(
		ZPosition Pos,
		const VIterator& Iter = *ZDefaultIterator
	) ;
	virtual void Swap(
		const VIterator& Iter1,
		const VIterator& Iter2 = *ZDefaultIterator
	) ;
	virtual void SortAsc(ZSortOrder Greater) ;
///!
///! Public Methods
///!
public:
	// List Navigation
	virtual void Reset() ; // force to point to nothing
	virtual void SetTo(ZPosition Pos) ;
	virtual bool SetToIndex(int Index) ;
		// true if current position succesfully set
		// false if invalid index, current position remains unchanged
	virtual bool Move(ZDirection Dir) ;
		// false if no more items in direction
	// List Access
	virtual void GetCurrent(pvoid *ppItem) const ;
		// fills *ppItem with NULL if points to nothing
	virtual void Get(ZPosition Pos, pvoid *ppItem) const ;
		// fills *ppItem with NULL if the list is emplty
	virtual void GetByIndex(int Index, pvoid *ppItem) const ;
		// fills *ppItem with NULL if index is out of Count
	// List Information
	virtual uint Count() const ;
		// returns number of items (0 for empty list)
	virtual uint ItemSize() const ; // returns size of the current item
	virtual uint ItemSizeAt(ZPosition Pos) const ;
	virtual uint ItemSizeByIndex(int Index) const ;
	virtual bool IsValid() const ; // true if currently points to data
	virtual bool IsAt(ZPosition Pos) const ;
		// true if currently at specified position
///!
///! Public Operators
///!
public:
	virtual pvoid operator ()() const ;
		// operator form of GetCurrent
	virtual pvoid operator [](ZPosition Pos) const ;
		// operator form of Get
	virtual pvoid operator [](int Index) const ;
		// operator form of GetByIndex
};
///!===========================================================================!
///!
///! Definition of Iterators & Lists
///!
static const uint LListIteratorClassCode = CLASSCODE(GIteratorClassCode); class PCL_API LListIterator : public GIterator { public: static const uint ClassCode() {return LListIteratorClassCode;}; public:
	friend class LList;
protected:
	LListIterator(LList *List);
	virtual void Reset(); // force to point to nothing
	virtual void SetTo(ZPosition Pos);
	virtual bool SetToIndex(int Index /*zero based*/);
	virtual void GetCurrent(pvoid *ppItem) const;
	virtual pvoid operator ()() const; // operator form of GetCurrent
	virtual pvoid operator [](ZPosition Pos) const; // operator form of Get
	virtual pvoid operator [](int Index) const; // operator form of GetByIndex
	pvoid m_current;
	virtual void _MoveValid(ZDirection Dir);
	virtual pvoid _MoveToIndex(uint Index);
};
static const uint LVectorIteratorClassCode = CLASSCODE(GIteratorClassCode); class PCL_API LVectorIterator : public GIterator { public: static const uint ClassCode() {return LVectorIteratorClassCode;}; public:
	friend class LVector;
protected:
	LVectorIterator(LVector *Vector);
	virtual void SetTo(ZPosition Pos);
	virtual void GetCurrent(pvoid *ppItem) const;
	virtual pvoid operator ()() const; // operator form of GetCurrent
	virtual pvoid _MoveToIndex(uint Index);
};
static const uint LCollectionIteratorClassCode = CLASSCODE(GIteratorClassCode); class PCL_API LCollectionIterator : public GIterator { public: static const uint ClassCode() {return LCollectionIteratorClassCode;}; public:
	friend class LCollection;
protected:
	LCollectionIterator(LCollection *Collection);
	~LCollectionIterator();
	virtual void Reset(); // force to point to nothing
	virtual void SetTo(ZPosition Pos);
	virtual bool SetToIndex(int Index);
	virtual bool Move(ZDirection Dir);
	// List Access
	virtual void GetCurrent(pvoid *ppItem) const;
	virtual pvoid operator ()() const; // operator form of GetCurrent
	virtual void Get(ZPosition Pos, pvoid *ppItem) const;
	virtual pvoid operator [](ZPosition Pos) const;
	virtual void GetByIndex(int Index, pvoid *ppItem) const;
	virtual pvoid operator [](int Index) const;
	// List Information
	virtual uint Count() const;
	virtual uint ItemSize() const; // returns size of the current item
	virtual uint ItemSizeAt(ZPosition Pos) const;
	virtual uint ItemSizeByIndex(int Index) const;
	virtual bool IsValid() const; // true if currently points to data
	virtual bool IsAt(ZPosition Pos) const;
private:
	VIterator &Iter;
};
static const uint LListClassCode = CLASSCODE(GListClassCode); class PCL_API LList : public GList { public: static const uint ClassCode() {return LListClassCode;}; public: LList(const pcont pContainer); virtual void Import(const pcont pContainer, bool AutoRelease = true); virtual const pcont Export(void); public:
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
static const uint LVectorClassCode = CLASSCODE(GListClassCode); class PCL_API LVector : public GList { public: static const uint ClassCode() {return LVectorClassCode;}; public: LVector(const pcont pContainer); virtual void Import(const pcont pContainer, bool AutoRelease = true); virtual const pcont Export(void); public:
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
static const uint LCollectionClassCode = CLASSCODE(GListClassCode); class PCL_API LCollection : public GList { public: static const uint ClassCode() {return LCollectionClassCode;}; public: LCollection(const pcont pContainer); virtual void Import(const pcont pContainer, bool AutoRelease = true); virtual const pcont Export(void); public:
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
#endif // __PCL_LIST_H__ 
