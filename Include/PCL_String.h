#ifndef __PCL_STRING_H__ 
#define __PCL_STRING_H__ 
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
///! Virtual String
///!
///! Global Scope Definitions:
///!
typedef enum PCL_StrConversionCode { ZNullStrConversionCode = 0,
	ZUpperCase,
	ZLowerCase,
	ZNameStyle, // First Letter Uppercase, all the rest Lowercase
	ZOEM,
	ZANSI,
} ZStrConversionCode;
///!
inline bool IsEmpty(cstr Str) {
	return !Str || !Str[0];
};
///!
static const uint VStringClassCode = VIRTUALCODE(true);

class VString : public VContainer {
public:
///!
///! Public Methods
///!
public:
	// General Management
	virtual uint Length() const =0; // 0 for empty strings
	virtual void SetBody(cstr Body) =0;
	virtual cstr Body() const =0; // NULL for empty strings
	virtual int Compare(cstr CmpStr, bool IgnoreCase = false) const =0;
	// String Modification
	virtual void Append(cstr AppendixExp) =0;
	virtual void Prefix(cstr PrefixExp) =0;
	virtual void Cut(uint Count, ZPosition From = ZHead) =0;
	virtual void Convert(ZStrConversionCode Code) =0;
	virtual void Revert(void) =0;
	// String Tools: Chr/SetChr/SubStr/Select/Find/Replace
	// For Chr, SetChr, SubStr & Select: Start indicates position 1..Length()
	// Start == 0 signals NOTIFICATION and works as Start == 1
	// Count > RestOfString: SubStr/Select from Start to the end of string
	// Count == 0: SubStr returns NULL, Select selects empty field
	virtual char Chr(uint Start) const =0;
	virtual void SetChr(uint Start, char NewChr) =0;
	virtual cstr SubStr(uint Start, uint Count = ZUintMax) =0;
	virtual void Select(uint Start, uint Count = ZUintMax) =0;
	// For all Find: return value 0 - Not Found, 1..Length() - Position
	virtual uint FindChr(char SearchChr, ZPosition From = ZHead) =0;
	virtual uint FindStr(cstr SearchStr, ZPosition From = ZHead) =0;
	virtual uint FindAny(cstr SearchStr, ZPosition From = ZHead) =0;
	virtual uint FindNot(cstr SearchStr, ZPosition From = ZHead) =0;
	// FindNext works after any of FindChr, FindStr, FindNext, FindAny, FindNot
	virtual uint FindNext(void) =0;
	// Replace works after any of FindChr, FindStr, FindNext, FindAny, FindNot, Select
	virtual void Replace(cstr ReplExp) =0;
	// Import/Export
	// Unicode (wide character strings)
	virtual void ImportUnicode(ustr Src,
		bool AutoRelease = true,
		ZMemAdmType MemAdmCode = ZMemUnicode
	) =0;
	virtual ustr ExportUnicode(void) =0;
	// Environment variables
	virtual void ImportEnv(cstr Name) =0;
	virtual void ExportEnv(cstr Name) =0;
	// Resources
	virtual void ImportRes(uint ResID, pvoid Module = NULL) =0;
	// Scalars
	virtual void ImportInt(int Src, cstr Format = "%d") =0;
	virtual void ImportHex(uint Src, cstr Format = "%08lx") =0;
	virtual void ImportDbl(double Src, cstr Format = "%lf") =0;
///!
///! Public Operators
///!
public:
	virtual operator cstr() const =0; // operator form of .Body()
	virtual char& operator [](ZPosition Pos) =0;
	virtual cstr operator ()(uint Start) =0;
	virtual cstr operator ()(uint Start, uint End) =0;
	// Comparisons
	virtual bool operator ==(cstr Src) const =0;
	virtual bool operator !=(cstr Src) const =0;
	virtual bool operator >=(cstr Src) const =0;
	virtual bool operator <=(cstr Src) const =0;
	virtual bool operator >(cstr Src) const =0;
	virtual bool operator <(cstr Src) const =0;
};
///!===========================================================================!
///!
///! Definition of String
///!
static const uint GStringClassCode = CLASSCODE(VStringClassCode);

class PCL_API GString : public VString {
public: static const uint ClassCode() {return GStringClassCode;};
protected: GString();
	virtual ~GString(); GString(const pcont pContainer);
	virtual void Import(const pcont pContainer, bool AutoRelease = true);
	virtual const pcont Export(void);
protected:
	LMemory m_data, m_clip;
	ustr m_uni;
	struct {
		uint Found;
		uint Len;
		ZPosition Pos;
		uint Mode;
	} m_last;
	virtual uint _FindNext(void);
	virtual uint _FindAny(void);
	virtual uint _FindNot(void);
///!
///! Public Methods
///!
public:
	// General Management
	virtual uint Length() const ; // 0 for empty strings
	virtual void SetBody(cstr Body) ;
	virtual cstr Body() const ; // NULL for empty strings
	virtual int Compare(cstr CmpStr, bool IgnoreCase = false) const ;
	// String Modification
	virtual void Append(cstr AppendixExp) ;
	virtual void Prefix(cstr PrefixExp) ;
	virtual void Cut(uint Count, ZPosition From = ZHead) ;
	virtual void Convert(ZStrConversionCode Code) ;
	virtual void Revert(void) ;
	// String Tools: Chr/SetChr/SubStr/Select/Find/Replace
	// For Chr, SetChr, SubStr & Select: Start indicates position 1..Length()
	// Start == 0 signals NOTIFICATION and works as Start == 1
	// Count > RestOfString: SubStr/Select from Start to the end of string
	// Count == 0: SubStr returns NULL, Select selects empty field
	virtual char Chr(uint Start) const ;
	virtual void SetChr(uint Start, char NewChr) ;
	virtual cstr SubStr(uint Start, uint Count = ZUintMax) ;
	virtual void Select(uint Start, uint Count = ZUintMax) ;
	// For all Find: return value 0 - Not Found, 1..Length() - Position
	virtual uint FindChr(char SearchChr, ZPosition From = ZHead) ;
	virtual uint FindStr(cstr SearchStr, ZPosition From = ZHead) ;
	virtual uint FindAny(cstr SearchStr, ZPosition From = ZHead) ;
	virtual uint FindNot(cstr SearchStr, ZPosition From = ZHead) ;
	// FindNext works after any of FindChr, FindStr, FindNext, FindAny, FindNot
	virtual uint FindNext(void) ;
	// Replace works after any of FindChr, FindStr, FindNext, FindAny, FindNot, Select
	virtual void Replace(cstr ReplExp) ;
	// Import/Export
	// Unicode (wide character strings)
	virtual void ImportUnicode(ustr Src,
		bool AutoRelease = true,
		ZMemAdmType MemAdmCode = ZMemUnicode
	) ;
	virtual ustr ExportUnicode(void) ;
	// Environment variables
	virtual void ImportEnv(cstr Name) ;
	virtual void ExportEnv(cstr Name) ;
	// Resources
	virtual void ImportRes(uint ResID, pvoid Module = NULL) ;
	// Scalars
	virtual void ImportInt(int Src, cstr Format = "%d") ;
	virtual void ImportHex(uint Src, cstr Format = "%08lx") ;
	virtual void ImportDbl(double Src, cstr Format = "%lf") ;
///!
///! Public Operators
///!
public:
	virtual operator cstr() const ; // operator form of .Body()
	virtual char& operator [](ZPosition Pos) ;
	virtual cstr operator ()(uint Start) ;
	virtual cstr operator ()(uint Start, uint End) ;
	// Comparisons
	virtual bool operator ==(cstr Src) const ;
	virtual bool operator !=(cstr Src) const ;
	virtual bool operator >=(cstr Src) const ;
	virtual bool operator <=(cstr Src) const ;
	virtual bool operator >(cstr Src) const ;
	virtual bool operator <(cstr Src) const ;
};
static const uint LStringClassCode = CLASSCODE(GStringClassCode);

class PCL_API LString : public GString {
public: static const uint ClassCode() {return LStringClassCode;};
public: LString(const pcont pContainer);
	virtual void Import(const pcont pContainer, bool AutoRelease = true);
	virtual const pcont Export(void);
public:
	LString(cstr Body = NULL);
	LString(LString &Copy);
	virtual ~LString();
	// Asignments
	virtual const VString& operator =(LString& Src);
	virtual const VString& operator =(cstr Src) ;
	virtual const VString& operator +=(cstr Src) ;
	virtual const VString& operator ^=(cstr Src) ;
protected:
	// Inheritable variables and methods
	inline uint InitialLen() {return 80;}; // Long Live Punch Cards !!!
};
#endif // __PCL_STRING_H__ 
