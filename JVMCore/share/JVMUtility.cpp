/**=============================================================================
 ** Copyright (C) 2011- WEILin beijing.
 ** =============================================================================
 **
 ** This document contains proprietary information belonging to gemalto.
 ** Technologies. Passing on and copying of this document, use and communication
 ** of its contents is not permitted without prior written authorisation.
 **
 ** =============================================================================
 **	Information :
 ** Project          : JVMCore $
 **	File Name        : JVMUtility.cpp $
 **	Created on       : Nov 14, 2012 $
 **	Time             : 2:31:11 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "JVMUtility.h"


namespace diamon_jvm
{

INLINE
JVM_U4 swap_JVM_U4(JVM_U4 u4)
{
	return (u4 & 0xFF) << 24 | (u4 & 0xFF00) << 8 | (u4 & 0xFF0000) >> 8 | (u4 & 0xFF000000) >> 24;
}

INLINE
JVM_U2 swap_JVM_U2(JVM_U2 u2)
{
	return (u2 & 0xFF) << 8 | (u2 & 0xFF00) >> 8;
}

INLINE
JVM_DOUBLE combine_JVM_DOUBLE(JVM_U2 u1, JVM_U2 u2)
{
	char buf[20 + 1] = {0};
	snprintf(buf, 20, "%d.%d", u1, u2);
	return atof(buf);
}

}
