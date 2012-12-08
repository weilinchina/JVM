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
 **	File Name        : OsThread.h $
 **	Created on       : Dec 6, 2012 $
 **	Time             : 2:55:48 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_OSTHREAD_H_
#define _JVM_OSTHREAD_H_


#include "GlobalDefinition.h"
#include "Runnable.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class OsThread : Runnable
{
private:
	JVM_THREAD_HANDLE handle_;

private:
	/**
	 * do NOT change this function.
	 */
	static void *threadProc(void *arg);

public:
	OsThread();
	virtual ~OsThread();

	virtual bool start();
	/**
	 * stop just invoke wait.
	 */
	virtual void stop();
	void wait();
	void suspend();
	void resume();
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_OSTHREAD_H_ */
