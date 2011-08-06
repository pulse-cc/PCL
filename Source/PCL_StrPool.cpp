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
#include "PCL_IMPL.h"


ZStringKey LGenericString::GetKey() {
	return PCL_INVALID_UINT;
};

/*
///! Implementation of LSmartString
void LSmartString::_ClearSplit() {
	if (m_pSplitter && m_splitter) *m_pSplitter = m_splitter;
	m_pHead = m_pTail = m_pSplitter = NULL;
	m_headLen = m_tailLen = 0;
	m_splitter = 0;
};

LSmartString::LSmartString(cstr Body) {
	m_allocLen = InitialLen();
	m_pData = LMem.Alloc(m_allocLen);
	SetBody(Body);
	m_splitter = 0;
	_ClearSplit();
};

LSmartString::~LSmartString() {
	LMem.Dealloc(m_pData);
};

LSmartString::LSmartString(const pcont pContainer) {
	m_pData = NULL;
	m_allocLen = 0;
	Import(pContainer);
	m_splitter = 0;
	_ClearSplit();
};

const pcont LSmartString::Export() {
	return LGenericString::Export();
};

void LSmartString::Import(const pcont pContainer, bool AutoRelease) {
	LGenericString::Import(pContainer, AutoRelease);
	_ClearSplit();
};

pvoid LSmartString::_GetDataAddr() {
	return m_pData;
};

void LSmartString::_SetDataLen(uint NewLen) {
	m_len = NewLen;
	if (!NewLen) return;
	if (m_allocLen < NewLen + 1) {
		m_allocLen = NewLen + 1;
		m_pData = LMem.Realloc(m_pData, m_allocLen);
	}
};

cstr LSmartString::GetBody() {
	if (!m_len) return NULL;
	if (m_pSplitter && m_splitter) *m_pSplitter = m_splitter;
	return (cstr)_GetDataAddr();
};

LSmartString::operator cstr() const {
	return const_cast<LSmartString*>(this)->GetBody();
};

void LSmartString::SetBody(cstr Body) {
	LGenericString::SetBody(Body);
	_ClearSplit();
};

void LSmartString::SetTail(cstr Tail) {
	if (!m_len) SetBody(Tail);
};

void LSmartString::SetHead(cstr Head) {
	if (!m_len) SetBody(Head);
};
*/