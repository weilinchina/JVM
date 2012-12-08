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
 **	File Name        : Thread.h $
 **	Created on       : Dec 6, 2012 $
 **	Time             : 2:22:31 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_THREAD_H_
#define _JVM_THREAD_H_


#include "GlobalDefinition.h"
#include "OsThread.h"
#include "FrameStack.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Thread : OsThread
{
protected:
	FrameStack *frameStack_;

protected:
	void run();

public:
	Thread();
	virtual ~Thread();

	bool start();
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_THREAD_H_ */
