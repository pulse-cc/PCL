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
#define PCL_IMPLEMENTATION
#include "PCL.hxx"

LSet::LSet(uint InitialLength, bool InitialValue) {
	m_length = 0;
	m_tailMask = 0;
	SetLength(InitialLength);
	if (InitialLength && InitialValue) SetAll(InitialValue);
}

LSet::LSet(const LSet &Set) {
	m_length = 0;
	m_tailMask = 0;
	Copy(Set);
}

LSet::~LSet(void) {
	// Nothing to destruct
}

uint LSet::_Size(void) const {
	return m_set.Size();
}

puchar LSet::_Addr(void) const {
	return m_set.Addr();
}

uint LSet::Length() const {
	return m_length;
}

void LSet::SetLength(uint NewLength) {
	m_tailMask = 0;
	uint newSize = NewLength >> 3;
	uint oldSize = m_set.Size();
	uchar tailCount = NewLength & 7;
	if (tailCount) {
		newSize++;
		m_tailMask = 0xFF >> (8 - tailCount);
	}
	m_set.SetSize(newSize);
	if (newSize > oldSize) { // Exclude newly allocated members
		memset(_Addr() + oldSize, 0, newSize - oldSize);
	}
	m_length = NewLength;
}

void LSet::SetAll(bool NewValue) {
	if (m_length) {
		int fillByte = NewValue ? 0xFF : 0;
		uint fillCount = m_set.Size();
		if (NewValue && m_tailMask) {
			fillCount--;
			puchar pLastByte = _Addr() + fillCount;
			*pLastByte = m_tailMask;
		}
		memset(_Addr(), fillByte, fillCount);
	}
	else {
		XErrorSetLast(E_FAIL, "Invalid operation on zero length set");
		XErrorSignal("LSet::SetAll");
	}
}

void LSet::Copy(const VSet &SourceSet) {
	uint newLength = SourceSet.Length();
	if (newLength != m_length) SetLength(newLength);
	memcpy(_Addr(), SourceSet._Addr(), _Size());
}

void LSet::SetValue(uint Member, bool NewValue) {
	if (Member >= m_length) {
		XErrorSetLast(E_INVALIDARG, "Member is out of set");
		XErrorSignal("LSet::SetValue");
		return;
	}
	uint byteIdx = Member >> 3;
	uint bitIdx = Member & 7;
	puchar pTargetByte = _Addr() + byteIdx;
	uchar bitMask = 1 << bitIdx;
	if (NewValue) {
		*pTargetByte |= bitMask;
	}
	else {
		*pTargetByte &= ~bitMask;
	}
}

bool LSet::Value(uint Member) const {
	if (Member >= m_length) {
		XErrorSetLast(E_INVALIDARG, "Member is out of set");
		XErrorSignal("LSet::Value");
		return false;
	}
	uint byteIdx = Member >> 3;
	uint bitIdx = Member & 7;
	puchar pTargetByte = _Addr() + byteIdx;
	uchar bitMask = 1 << bitIdx;
	return (*pTargetByte & bitMask) ? true : false;
}

void LSet::Not(void) {
	puchar pTargetByte;
	for (uint byteIdx = 0; byteIdx < _Size(); byteIdx++) {
		pTargetByte = _Addr() + byteIdx;
		*pTargetByte = ~(*pTargetByte);
	}
	if (m_tailMask) *pTargetByte &= m_tailMask;
}

void LSet::And(const VSet &Set) {
	uint length = Set.Length();
	if (length > m_length) SetLength(length);
	for (uint byteIdx = 0; byteIdx < _Size(); byteIdx++) {
		puchar pTargetByte = _Addr() + byteIdx;
		puchar pSourceByte = Set._Addr() + byteIdx;
		*pTargetByte &= *pSourceByte;
	}
}

void LSet::Or(const VSet &Set) {
	uint length = Set.Length();
	if (length > m_length) SetLength(length);
	for (uint byteIdx = 0; byteIdx < _Size(); byteIdx++) {
		puchar pTargetByte = _Addr() + byteIdx;
		puchar pSourceByte = Set._Addr() + byteIdx;
		*pTargetByte |= *pSourceByte;
	}
}

void LSet::Xor(const VSet &Set) {
	uint length = Set.Length();
	if (length > m_length) SetLength(length);
	for (uint byteIdx = 0; byteIdx < _Size(); byteIdx++) {
		puchar pTargetByte = _Addr() + byteIdx;
		puchar pSourceByte = Set._Addr() + byteIdx;
		*pTargetByte ^= *pSourceByte;
	}
}

bool LSet::IsEqual(const VSet &Set) const {
	if (Set.Length() != m_length) return false;
	int rc = memcmp(_Addr(), Set._Addr(), _Size());
	if (rc) return false;
	return true;
}

bool LSet::IsEmpty(void) const {
	if (!m_length) return true;
	for (uint byteIdx = 0; byteIdx < _Size(); byteIdx++) {
		puchar pTargetByte = _Addr() + byteIdx;
		if (*pTargetByte) return false;
	}
	return true;
}

bool LSet::operator [](uint Member) const { // .Value() {Same as Pascal's 'in'}
	return Value(Member);
}

const VSet& LSet::operator =(const LSet &Set) { // .Copy(Set)
	Copy(Set);
	return *this;
}

const VSet& LSet::operator =(bool NewValue) { // .SetAll(NewValue)
	SetAll(NewValue);
	return *this;
}

const VSet& LSet::operator &=(const VSet &Set) { // .And(Set)
	And(Set);
	return *this;
}

const VSet& LSet::operator |=(const VSet &Set) { // .Or(Set)
	Or(Set);
	return *this;
}

const VSet& LSet::operator ^=(const VSet &Set) { // .Xor(Set)
	Xor(Set);
	return *this;
}

const VSet& LSet::operator +=(uint Member) { // .SetValue(Member, true)
	SetValue(Member, true);
	return *this;
}

const VSet& LSet::operator -=(uint Member) { // .SetValue(Member, false)
	SetValue(Member, false);
	return *this;
}

bool LSet::operator ==(const VSet &Set) const { // .IsEqual(Set)
	return IsEqual(Set);
}

bool LSet::operator !=(const VSet &Set) const { // !.IsEqual(Set)
	return !IsEqual(Set);
}

