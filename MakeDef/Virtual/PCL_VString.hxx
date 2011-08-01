///!
///! Public Methods
///!
public:
	// General Management
	virtual uint Length() const PCL_PURE; // 0 for empty strings
	virtual void SetBody(cstr Body) PCL_PURE;
	virtual cstr Body() const PCL_PURE; // NULL for empty strings
	virtual int Compare(cstr CmpStr, bool IgnoreCase = false) const PCL_PURE;
	// String Modification
	virtual void Append(cstr AppendixExp) PCL_PURE;
	virtual void Prefix(cstr PrefixExp) PCL_PURE;
	virtual void Cut(uint Count, ZPosition From = ZHead) PCL_PURE;
	virtual void Convert(ZStrConversionCode Code) PCL_PURE;
	virtual void Revert(void) PCL_PURE;
	// String Tools: Chr/SetChr/SubStr/Select/Find/Replace
	// For Chr, SetChr, SubStr & Select: Start indicates position 1..Length()
	// Start == 0 signals NOTIFICATION and works as Start == 1
	// Count > RestOfString: SubStr/Select from Start to the end of string
	// Count == 0: SubStr returns NULL, Select selects empty field
	virtual char Chr(uint Start) const PCL_PURE;
	virtual void SetChr(uint Start, char NewChr) PCL_PURE;
	virtual cstr SubStr(uint Start, uint Count = ZUintMax) PCL_PURE;
	virtual void Select(uint Start, uint Count = ZUintMax) PCL_PURE;
	// For all Find: return value 0 - Not Found, 1..Length() - Position
	virtual uint FindChr(char SearchChr, ZPosition From = ZHead) PCL_PURE;
	virtual uint FindStr(cstr SearchStr, ZPosition From = ZHead) PCL_PURE;
	virtual uint FindAny(cstr SearchStr, ZPosition From = ZHead) PCL_PURE;
	virtual uint FindNot(cstr SearchStr, ZPosition From = ZHead) PCL_PURE;
	// FindNext works after any of FindChr, FindStr, FindNext, FindAny, FindNot
	virtual uint FindNext(void) PCL_PURE;
	// Replace works after any of FindChr, FindStr, FindNext, FindAny, FindNot, Select
	virtual void Replace(cstr ReplExp) PCL_PURE;
	// Import/Export
	// Unicode (wide character strings)
	virtual void ImportUnicode(ustr Src,
		bool AutoRelease = true,
		ZMemAdmType MemAdmCode = ZMemUnicode
	) PCL_PURE;
	virtual ustr ExportUnicode(void) PCL_PURE;
	// Environment variables
	virtual void ImportEnv(cstr Name) PCL_PURE;
	virtual void ExportEnv(cstr Name) PCL_PURE;
	// Resources
	virtual void ImportRes(uint ResID, pvoid Module = NULL) PCL_PURE;
	// Scalars
	virtual void ImportInt(int Src, cstr Format = "%d") PCL_PURE;
	virtual void ImportHex(uint Src, cstr Format = "%08lx") PCL_PURE;
	virtual void ImportDbl(double Src, cstr Format = "%lf") PCL_PURE;
///!
///! Public Operators
///!
public:
	virtual operator cstr() const PCL_PURE; // operator form of .Body()
	virtual char& operator [](ZPosition Pos) PCL_PURE;
	virtual cstr operator ()(uint Start) PCL_PURE;
	virtual cstr operator ()(uint Start, uint End) PCL_PURE;
	// Comparisons
	virtual bool operator ==(cstr Src) const PCL_PURE;
	virtual bool operator !=(cstr Src) const PCL_PURE;
	virtual bool operator >=(cstr Src) const PCL_PURE;
	virtual bool operator <=(cstr Src) const PCL_PURE;
	virtual bool operator >(cstr Src) const PCL_PURE;
	virtual bool operator <(cstr Src) const PCL_PURE;
