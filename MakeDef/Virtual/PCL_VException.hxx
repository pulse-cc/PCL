///!
///! Public Methods
///!
public:
	virtual void Signal(cstr Message, uint Code = 0) PCL_PURE;
	virtual cstr LastMessage(void) const PCL_PURE;
	virtual uint LastCode(void) const PCL_PURE;
	virtual void SetMode(ZExceptionMode NewMode) PCL_PURE;
	virtual ZExceptionMode Mode(void) const PCL_PURE;
	virtual void SetTitle(cstr NewTitle) PCL_PURE;
	virtual cstr Title(void) const PCL_PURE;
