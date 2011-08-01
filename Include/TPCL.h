#ifndef __TPCL_H__
#define __TPCL_H__

template <class T>
class VectorOf : public LVector {
public:
	VectorOf() : LVector(sizeof(T)) {
	}
	void Insert(ZPosition Pos, T Item) {
		LVector::Insert(Pos, &Item);
	}
	void Insert(ZPosition Pos, T* pItem) {
		LVector::Insert(Pos, pItem);
	}
	T* GetData(void) {
		return (T*)m_head;
	}
	const VectorOf<T>& operator =(T Src) {
		LVector::RemoveAll();
		Insert(ZHead, Src);
		return *this;
	}
	const VectorOf<T>& operator +=(T Src) {
		Insert(ZTail, Src);
		return *this;
	}
	const VectorOf<T>& operator ^=(T Src) {
		Insert(ZHead, Src);
		return *this;
	}
};

template <class T>
class CollectionOf : public LCollection {
public:
	CollectionOf() : LCollection() {
	}
	void Insert(ZPosition Pos, T Item, uint Len) {
		LCollection::Insert(Pos, &Item, Len);
	}
	void Insert(ZPosition Pos, T* pItem, uint Len) {
		LCollection::Insert(Pos, pItem, Len);
	}
};

class StrPool : public LCollection {
public:
	StrPool() : LCollection() {
	}
	const StrPool& operator =(cstr Src) {
		LCollection::RemoveAll();
		Insert(ZHead, (pvoid)Src, strlen(Src) + 1);
		return *this;
	}
	const StrPool& operator +=(cstr Src) {
		Insert(ZTail, (pvoid)Src, strlen(Src) + 1);
		return *this;
	}
	const StrPool& operator ^=(cstr Src) {
		Insert(ZHead, (pvoid)Src, strlen(Src) + 1);
		return *this;
	}
};

#endif //__TPCL_H__
