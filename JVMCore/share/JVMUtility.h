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
 **	File Name        : JVMUtility.h $
 **	Created on       : Nov 14, 2012 $
 **	Time             : 2:30:58 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_JVMUTILITY_H_
#define _JVM_JVMUTILITY_H_


#include "GlobalDefinition.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

INLINE
JVM_U4 swap_JVM_U4(JVM_U4 u4);

INLINE
JVM_U2 swap_JVM_U2(JVM_U2 u2);

INLINE
JVM_DOUBLE combine_JVM_DOUBLE(JVM_U2 u1, JVM_U2 u2);

}


#ifdef __cplusplus
}
#endif


#endif /* _JVM_JVMUTILITY_H_ */
