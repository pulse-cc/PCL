///!
//*!===========================================================================!
//*! PCL stands for Portable Class Library and is designed for development
//*! of applications portable between different environments,
//*! first of all between MS Windows and GNU Linux.
//*!
//*! CopyFree Pulse Computer Consulting, 2001, 2002
//*!
//*! CopyFree License Agreement:
//*!	1.You may do with this code whatever you like.
//*!	2.In no case Pulse Computer Consulting is responsible for your results.
//*!
//*! E-mail: pulse.cc@mail.ru
//*!===========================================================================!
///!
#define PCL_API __declspec(dllexport)
#include "PCL.h"

///! Implementation of LRegistry
bool LRegistry::_Init(void) {
	if (m_ref++) { // Nested Initialization
		return Mem._Init() && CSect._Init();
	}
	// First Time (Actual) Initialization
	try {
		if (!Mem._Init()) return false;
		if (!CSect._Init()) return false;
	}
	catch (...) {
		LSetLastError(E_UNEXPECTED, "LRegistry::_Init{Mem._Init, CSect._Init}");
		return false;
	}
	HKEY baseKey;
	if (m_DBName == pclClassInfo) {
		baseKey = HKEY_CLASSES_ROOT;
	}
	if (m_DBName == pclSystemInfo) {
		baseKey = HKEY_LOCAL_MACHINE;
	}
	if (m_DBName == pclUserInfo) {
		baseKey = HKEY_CURRENT_USER;
	}
	else {
		LSetLastError(E_UNEXPECTED, "LRegistry::DBName unknown");
	}
	if (m_access == pclRead) {
		m_sam = KEY_QUERY_VALUE;
	}
	else if (m_access == pclWrite) {
		m_sam = KEY_SET_VALUE;
	}
	else if (m_access == pclWrite) {
		m_sam = KEY_ALL_ACCESS;
	}
	else {
		LSetLastError(E_UNEXPECTED, "LRegistry::Access code unknown");
	}
	m_regRC = ::RegOpenKeyEx(
		baseKey,
		NULL,
		0,
		m_sam,
		&m_rootKey
	);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot open");
		return false;
	}
	m_keyReady = true;
	return true;
}
bool LRegistry::_Exit(void) {
	if (!m_ref) { // Invalid Nesting
		LSetLastError(PCL_E_(INVALID_NESTING), "LRegistry::_Exit");
		return false;
	}
	if (--m_ref) { // Nested Uninitialization
		return Mem._Exit() && CSect._Exit();
	}
	// Actual Uninitialization
	m_regRC = ::RegCloseKey(m_rootKey);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot close");
		return false;
	}
	m_keyReady = false;
	return Mem._Exit() && CSect._Exit();
}

bool LRegistry::OpenKey(const LString Name) {
	if (!m_keyReady) {
		LSetLastError(E_UNEXPECTED, "LRegistry::NestedOpen");
		return false;
	}
	m_regRC = ::RegOpenKeyEx(
		m_rootKey,
		(pchar)Name,
		0,
		m_sam,
		&m_key
	);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot open key");
		return false;
	}
	m_keyReady = false;
	return true;
}
bool LRegistry::CloseKey(void) {
	m_regRC = ::RegCloseKey(m_key);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot close key");
		return false;
	}
	m_keyReady = true;
	return true;
}
bool LRegistry::ReadString(const LString Name, LString Value) {
	m_valSize = 256;
	m_regRC = ::RegQueryValueEx(
		m_key,
		Name,
		NULL,
		&m_valType,
		(puchar)Value,
		&m_valSize
	);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot read string");
		return false;
	}
	return true;
}
bool LRegistry::WriteString(const LString Name, LString Value) {
	m_regRC = ::RegSetValueEx(
		m_key,
		Name,
		NULL,
		REG_SZ,
		(puchar)Value,
		LLength(Value) + 1
	);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot write string");
		return false;
	}
	return true;
}
bool LRegistry::ReadNumber(const LString Name, puint pValue) {
	m_regRC = ::RegQueryValueEx(
		m_key,
		Name,
		NULL,
		&m_valType,
		(puchar)pValue,
		&m_valSize
	);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot read number");
		return false;
	}
	return true;
}
bool LRegistry::WriteNumber(const LString Name, uint Value) {
	m_regRC = ::RegSetValueEx(
		m_key,
		Name,
		NULL,
		REG_DWORD,
		(puchar)&Value,
		sizeof(uint)
	);
	if (m_regRC != ERROR_SUCCESS) {
		LSetLastError(E_UNEXPECTED, "LRegistry::Cannot write number");
		return false;
	}
	return true;
}
