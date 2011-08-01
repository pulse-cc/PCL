#ifndef __PCL_SET_H__ 
#define __PCL_SET_H__ 
#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif
///!
//*!===========================================================================!
//*! PCL stands for Portable Class Library and is designed for development
//*! of applications portable between different environments,
//*! first of all between MS Windows and GNU Linux.
//*!
//*! CopyFree Pulse Computer Consulting, 2001 - 2004
//*!
//*! CopyFree License Agreement:
//*!	1.You may do with this code whatever you like.
//*!	2.In no case Pulse Computer Consulting is responsible for your results.
//*!
//*! E-mail: pulse.cc@mail.ru
//*!===========================================================================!
///!
///!
///! Virtual Set
///!
static const uint VSetClassCode = VIRTUALCODE(false); class VSet { public:
///!
///! Public Methods
///!
public:
	// General Management
	virtual uint Length() const =0; // 0 for empty set
	virtual void SetLength(uint NewLength) =0; // 0 to make set empty
	virtual void SetAll(bool NewValue) =0;
	virtual void Copy(const VSet &SourceSet) =0;
	virtual void SetValue(uint Member, bool NewValue) =0;
	virtual bool Value(uint Member) const =0;
	// Set Logics
	virtual void Not(void) =0;
	virtual void And(const VSet &Set) =0;
	virtual void Or(const VSet &Set) =0;
	virtual void Xor(const VSet &Set) =0;
	virtual bool IsEqual(const VSet &Set) const =0;
	virtual bool IsEmpty(void) const =0;
///!
///! Public Operators
///!
public:
	virtual bool operator [](uint Member) const =0; // .Value() {Same as Pascal's 'in'}
	// Assignments
	virtual const VSet& operator =(bool NewValue) =0; // .SetAll(NewValue)
	virtual const VSet& operator &=(const VSet &Set) =0; // .And(Set)
	virtual const VSet& operator |=(const VSet &Set) =0; // .Or(Set)
	virtual const VSet& operator ^=(const VSet &Set) =0; // .Xor(Set)
	virtual const VSet& operator +=(uint Member) =0; // .SetValue(Member, true)
	virtual const VSet& operator -=(uint Member) =0; // .SetValue(Member, false)
	// Comparisons
	virtual bool operator ==(const VSet &Set) const =0; // .IsEqual(Set)
	virtual bool operator !=(const VSet &Set) const =0; // !.IsEqual(Set)
///!
///! Protected Methods (Direct access to the set)
///!
	virtual uint _Size(void) const =0;
	virtual puchar _Addr(void) const =0;
};
///!===========================================================================!
///!
///! Definition of Set of cardinal numbers
///!
static const uint LSetClassCode = CLASSCODE(VSetClassCode); class PCL_API LSet : public VSet { public: static const uint ClassCode() {return LSetClassCode;}; public:
	LSet(uint InitialLength = 0, bool InitialValue = false);
	LSet(const LSet &Set);
	virtual ~LSet();
	virtual const VSet& operator =(const LSet &Set);
///!
///! Public Methods
///!
public:
	// General Management
	virtual uint Length() const ; // 0 for empty set
	virtual void SetLength(uint NewLength) ; // 0 to make set empty
	virtual void SetAll(bool NewValue) ;
	virtual void Copy(const VSet &SourceSet) ;
	virtual void SetValue(uint Member, bool NewValue) ;
	virtual bool Value(uint Member) const ;
	// Set Logics
	virtual void Not(void) ;
	virtual void And(const VSet &Set) ;
	virtual void Or(const VSet &Set) ;
	virtual void Xor(const VSet &Set) ;
	virtual bool IsEqual(const VSet &Set) const ;
	virtual bool IsEmpty(void) const ;
///!
///! Public Operators
///!
public:
	virtual bool operator [](uint Member) const ; // .Value() {Same as Pascal's 'in'}
	// Assignments
	virtual const VSet& operator =(bool NewValue) ; // .SetAll(NewValue)
	virtual const VSet& operator &=(const VSet &Set) ; // .And(Set)
	virtual const VSet& operator |=(const VSet &Set) ; // .Or(Set)
	virtual const VSet& operator ^=(const VSet &Set) ; // .Xor(Set)
	virtual const VSet& operator +=(uint Member) ; // .SetValue(Member, true)
	virtual const VSet& operator -=(uint Member) ; // .SetValue(Member, false)
	// Comparisons
	virtual bool operator ==(const VSet &Set) const ; // .IsEqual(Set)
	virtual bool operator !=(const VSet &Set) const ; // !.IsEqual(Set)
///!
///! Protected Methods (Direct access to the set)
///!
	virtual uint _Size(void) const ;
	virtual puchar _Addr(void) const ;
private:
	LMemory m_set;
	uint m_length;
	uchar m_tailMask;
};
#endif // __PCL_SET_H__ 
