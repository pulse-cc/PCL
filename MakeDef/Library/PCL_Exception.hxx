#ifndef __PCL_EXCEPTION_H__
#define __PCL_EXCEPTION_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

// Exception Class
PCL_CLASS(Exception):
	LException(ZExceptionMode Mode = ZIgnore);
#include "PCL_VException.hxx"
private:
	LString m_title;
	ZExceptionMode m_mode;
	LString m_lastMsg;
	uint m_lastCode;
};

/*
// Error Handling Class
PCL_CLASS_OF(LException, Error):
	LError();
	virtual void Report(ZErrorLevel Level, cstr Text, uint Code);
	virtual void SetAction(ZErrorLevel Level, ZExceptionMode Mode);
};
*/

#endif // __PCL_EXCEPTION_H__
