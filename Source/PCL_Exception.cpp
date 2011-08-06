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

///! Exception
LException::LException(ZExceptionMode Mode) {
	m_mode = Mode;
	m_title = "PCL.Exception";
	m_lastMsg = "Nothing Happened";
	m_lastCode = 0;
}

void LException::Signal(cstr Message, uint Code) {
	m_lastMsg = Message;
	m_lastCode = Code;
	switch (m_mode) {
		case ZLog: {
			LString logFileName(m_title);
			logFileName += ".log";
			FILE *logFile = fopen(logFileName, "at");
			if (!logFile) {
				XErrorSetLast(E_UNEXPECTED, "Exception Log Fail");
				XErrorSignal("LException::Signal");
			}
			fprintf(logFile, Code ? "\n%s [0x%08lx]" : "\n%s", Message, Code);
			fclose(logFile);
		} break;
		case ZOutput: {
			fprintf(stdout, Code ? "\n%s:%s [0x%08lx]" : "\n%s:%s", 
				(cstr)m_title, 
				Message, 
				Code
			);
			fflush(stdout);
		} break;
		case ZShow: {
			char buf[MAX_PATH];
			sprintf(buf, Code ? "%s [0x%08lx]" : "%s", Message, Code);
			switch (::MessageBox(NULL, buf, m_title, 
				MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION | MB_DEFBUTTON3)) {
				case IDABORT: {
					m_mode = ZAbort;
					Signal(Message, Code);
				} break;
				case IDRETRY: {
					int mbrc = ::MessageBox(NULL,
						"Send rest of exceptions to log file ?"
						"\n\tNO - stay in show mode"
						"\n\tCANCEL - switch to ignore mode", m_title, 
						MB_YESNOCANCEL | MB_ICONQUESTION
					);
					if (IDYES == mbrc) {
						m_mode = ZLog;
						Signal(Message, Code);
					}
					else if (IDCANCEL == mbrc) {
						m_mode = ZIgnore;
					}
				} break;
			}
		} break;
		case ZThrow: {
			throw this;
		} break;
		case ZAbort: {
			LTerminate(Message);
		} break;
	}
}

cstr LException::LastMessage(void) const {
	return (cstr)m_lastMsg;
}

uint LException::LastCode(void) const {
	return m_lastCode;
}

void LException::SetMode(ZExceptionMode NewMode) {
	m_mode = NewMode;
}

ZExceptionMode LException::Mode(void) const {
	return m_mode;
}

void LException::SetTitle(cstr NewTitle) {
	m_title = NewTitle;
}

cstr LException::Title(void) const {
	return m_title;
}
