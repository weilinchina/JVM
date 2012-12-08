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
 **	File Name        : Thread.cpp $
 **	Created on       : Dec 6, 2012 $
 **	Time             : 2:22:31 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "Thread.h"


namespace diamon_jvm
{

Thread::Thread() : OsThread()
{
	this->frameStack_ = NULL;
}

Thread::~Thread()
{
	if(this->frameStack_ != NULL)
	{
		delete this->frameStack_;
		this->frameStack_ = NULL;
	}
}

bool Thread::start()
{
	if(this->frameStack_ == NULL)
	{
		this->frameStack_ = new FrameStack();
		if(this->frameStack_ == NULL)
			return false;
	}
	return OsThread::start();
}

void Thread::run()
{

}

} /* namespace diamon_jvm */
