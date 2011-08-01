///!
///! Public Methods
///!
public:
	virtual void Release(void) PCL_PURE;
	virtual bool Wait(sint Timeout = INFINITE) PCL_PURE; // false if timed-out
