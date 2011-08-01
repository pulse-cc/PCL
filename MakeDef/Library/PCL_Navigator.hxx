#ifndef __PCL_NAVIGATOR_H__
#define __PCL_NAVIGATOR_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

/*
PCL_CLASS_OF(GNavigator, TreeNavigator):
	friend class LTree;
protected:
	LTreeNavigator(LTree *Tree);
	virtual void Reset(); // force to point to nothing
	virtual void SetTo(ZPosition Pos);
	virtual bool SetToIndex(int Index);
	virtual void GetCurrent(pvoid *ppItem);
	virtual pvoid operator ()() const; // operator form of GetCurrent
	virtual pvoid operator ()(ZPosition Pos) const; // operator form of Get
	virtual pvoid operator [](int Index) const; // operator form of GetByIndex

	pvoid m_current;
	virtual void _MoveValid(ZDirection Dir);
	virtual pvoid _MoveToIndex(uint Index);
};
*/
#endif // __PCL_NAVIGATOR_H__