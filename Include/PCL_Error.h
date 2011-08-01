#ifndef __PCL_ERROR_H__
#define __PCL_ERROR_H__

///!
///! Error Handling Stuff
///!
typedef enum PCL_Error {
	XErr_First = 0,

	XErr_INTERNAL,
	XErr_INVALID_NESTING,
	XErr_INCOMPATIBLE_NESTING,
	XErr_TIMEOUT_EXCEEDED,

	XErr_Last
} XError;

#define PCL_ERR_(x) ((HRESULT)XErr_##x)

typedef enum PCL_ErrorLevel {
	XErrLev_INTERNAL		= 0x00,
	XErrLev_NOTIFICATION	= 0x01,
	XErrLev_NOTIF			= XErrLev_NOTIFICATION, // Alias
	XErrLev_RECOVERABLE		= 0x02,
	XErrLev_RECOVER			= XErrLev_RECOVERABLE, // Alias
	XErrLev_SEVERE			= 0x04,
	XErrLev_FATAL			= 0x08,

	XErrLev_WARNING			= XErrLev_NOTIFICATION | XErrLev_RECOVERABLE,
	XErrLev_ERROR			= XErrLev_SEVERE | XErrLev_FATAL,
	XErrLev_ALL				= XErrLev_WARNING | XErrLev_ERROR
} XErrorLevel;

#define PCL_ELEV_(x) (XErrLev_##x)

typedef enum PCL_ErrorAction {
	XErrAct_IGNORE		= 0x00, // do nothing
	XErrAct_KEEPTRACE	= 0x01, // add message to PCL error log file
	XErrAct_DISPLAY		= 0x02, // display message to the user
	XErrAct_ABORT		= 0x04, // terminate current application

	XErrAct_LOGUP = XErrAct_KEEPTRACE | XErrAct_DISPLAY,
	XErrAct_TERMINATE = XErrAct_LOGUP | XErrAct_ABORT
} XErrorAction;

#define PCL_EACT_(x) ((XErrorAction)XErrAct_##x)

///!
///! Default Error Level Mapping to Error Action:
///!
///!	NOTIFICATION	==> IGNORE
///!	RECOVERABLE		==> DISPLAY
///!	SEVERE			==> LOGUP
///!	FATAL			==> TERMINATE
///!
///! These defaults may be changed at runtime by the call to XErrorSetAction, BUT
///!	a) NOTIFICATION never leads to ABORT;
///!	b) FATAL always leads to ABORT;
///!	c) INTERNAL error processing cannot be changed.
///!

typedef struct PCL_ErrorInfo {
	HRESULT code;
	XErrorLevel level;
	pchar message;
} XErrorInfo, *pXErrorInfo;

#endif // __PCL_ERROR_H__
