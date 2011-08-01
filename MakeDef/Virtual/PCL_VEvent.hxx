///!
///! Public Methods
///!
public:
	virtual void Signal(void) PCL_PURE;
	virtual void Clear(void) PCL_PURE;
	virtual void Pulse(void) PCL_PURE;
	virtual bool Wait(sint Timeout = INFINITE) PCL_PURE; // false if timed-out
