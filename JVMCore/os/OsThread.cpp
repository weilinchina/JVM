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
 **	File Name        : OsThread.cpp $
 **	Created on       : Dec 6, 2012 $
 **	Time             : 2:55:48 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "OsThread.h"


namespace diamon_jvm
{

OsThread::OsThread()
{
	this->handle_ = 0;
}

OsThread::~OsThread()
{
	// TODO Auto-generated destructor stub
}

bool OsThread::start()
{
	if(this->handle_ == 0)
	{
		if(pthread_create(&this->handle_, NULL, threadProc, this) != 0)
			return false;
	}
	return true;
}

void OsThread::stop()
{
	wait();
}

void OsThread::wait()
{
	if(this->handle_ != 0)
	{
		pthread_join(this->handle_, NULL);
		this->handle_ = 0;
	}
}

void OsThread::suspend()
{
	if(this->handle_ != 0)
		pthread_kill(this->handle_, SIGSTOP);
}

void OsThread::resume()
{
	if(this->handle_ != 0)
		pthread_kill(this->handle_, SIGCONT);
}

/**
 * do NOT change this function.
 */
void *OsThread::threadProc(void *arg)
{
	ASSERT(arg != NULL);

	OsThread *osThread = (OsThread *)arg;
	osThread->run();

	return NULL;
}

} /* namespace diamon_jvm */
