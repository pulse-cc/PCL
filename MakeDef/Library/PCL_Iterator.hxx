#ifndef __PCL_ITERATOR_H__
#define __PCL_ITERATOR_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_CLASS_OF(GIterator, ListIterator):
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

PCL_CLASS_OF(GIterator, VectorIterator):
	friend class LVector;
protected:
	LVectorIterator(LVector *Vector);
	virtual void SetTo(ZPosition Pos);
	virtual void GetCurrent(pvoid *ppItem) const;
	virtual pvoid operator ()() const; // operator form of GetCurrent

	virtual pvoid _MoveToIndex(uint Index);
};

PCL_CLASS_OF(GIterator, CollectionIterator):
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

#endif // __PCL_ITERATOR_H__