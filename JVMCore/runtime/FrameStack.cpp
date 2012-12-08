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
 **	File Name        : FrameStack.cpp $
 **	Created on       : Dec 7, 2012 $
 **	Time             : 4:17:00 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "FrameStack.h"


namespace diamon_jvm
{

FrameStack::FrameStack() : Stack<Frame *>()
{
}

FrameStack::~FrameStack()
{
}

void FrameStack::destroy()
{
	if(this->stack_ != NULL)
	{
		for(size_t i = 0; i < this->stackSize_; i ++)
		{
			Frame *frame = this->stack_[i];
			delete frame;
		}
	}
	Stack<Frame *>::destroy();
}

} /* namespace diamon_jvm */
