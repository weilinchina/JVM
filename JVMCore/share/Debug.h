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
 **	File Name        : Common.h $
 **	Created on       : Nov 26, 2012 $
 **	Time             : 5:09:59 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_DEBUG_H_
#define _JVM_DEBUG_H_


#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/timeb.h>
#include <string>


#ifdef _DEBUG
#define ASSERT(t)              diamon_jvm::assert(t)
#define TRACE                  diamon_jvm::trace
#define ERROR                  diamon_jvm::error
#else
#define ASSERT(t)
#define TRACE
#define ERROR                  diamon_jvm::error
#endif


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

void assert(bool expr);
void trace(const char *format, ...);
void error(const char *format, ...);
std::string vformat(const char *format, va_list args);

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_DEBUG_H_ */
