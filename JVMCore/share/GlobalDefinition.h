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
 **	File Name        : GlobalDefinition.h $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 5:10:21 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_GLOBALDEFINITION_H_
#define _JVM_GLOBALDEFINITION_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <stddef.h>
#include <memory.h>
#include <time.h>
#include <string.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>

#include "Debug.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

#ifdef ENABLE_INLINE
#define INLINE inline
#else
#define INLINE
#endif


// ***********************
// *** bellow are samples for 32 bits platform.
// *** you should change it to follow your CPU width.
// ***********************
typedef unsigned int           JVM_U4;
typedef unsigned short         JVM_U2;
typedef unsigned char          JVM_U1;

typedef unsigned char          JVM_BYTE;
typedef short                   JVM_CHAR;
typedef short                   JVM_SHORT;
typedef int                     JVM_INT;
typedef long long              JVM_LONG;
typedef float                  JVM_FLOAT;
typedef double                 JVM_DOUBLE;

typedef FILE *                  JVM_FILE_HANDLE;
typedef pthread_t               JVM_THREAD_HANDLE;
// ***********************

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_GLOBALDEFINITION_H_ */
