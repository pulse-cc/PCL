#ifndef __PCL_CLASSCODE_H__
#define __PCL_CLASSCODE_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

///!
///! PCL Class Code Generation
///!
static const uint VIRTUALCODE(bool IsContainer) {
	static uint Number = 0;
	if (!Number++) return PCL_PREFIX | PCL_CONTAINER_MASK; // Special case for VContainer
	return PCL_PREFIX | (IsContainer ? PCL_CONTAINER_MASK : 0) | (Number++ << 7);
}
static const uint CLASSCODE(uint BaseCode) {
	static uint Number = 0;
	if (++Number == 256) Number = 1;
	return (BaseCode & 0xFFFFFF00uL) | Number;
}

#endif //__PCL_CLASSCODE_H__


