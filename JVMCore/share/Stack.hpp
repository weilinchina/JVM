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
 **	File Name        : Stack.cpp $
 **	Created on       : Dec 6, 2012 $
 **	Time             : 2:23:11 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_STACK_HPP_
#define _JVM_STACK_HPP_


#define STACK_STEP_SIZE              10


#include "Stack.h"


namespace diamon_jvm
{

template <typename STACK_ELEMENT>
Stack<STACK_ELEMENT>::Stack()
{
	this->stack_ = NULL;
	this->stackSize_ = 0;
	this->stackTop_ = 0;
	this->expectedSize_ = 0;
}

template <typename STACK_ELEMENT>
Stack<STACK_ELEMENT>::Stack(size_t expectedSize)
{
	this->stack_ = NULL;
	this->stackSize_ = 0;
	this->stackTop_ = 0;
	this->expectedSize_ = expectedSize;
}

template <typename STACK_ELEMENT>
Stack<STACK_ELEMENT>::~Stack()
{
	destroy();
}

template <typename STACK_ELEMENT>
bool Stack<STACK_ELEMENT>::allocateSpace()
{
	if(this->stack_ == NULL)
	{
		ASSERT(this->stackTop_ == 0);
		ASSERT(this->stackSize_ == 0);

		if(this->expectedSize_ != 0)
		{
			this->stack_ = new STACK_ELEMENT[this->expectedSize_];
			if(this->stack_ == NULL)
				return false;
			this->stackSize_ = this->expectedSize_;
		}
		else
		{
			this->stack_ = new STACK_ELEMENT[STACK_STEP_SIZE];
			if(this->stack_ == NULL)
				return false;
			this->stackSize_ = STACK_STEP_SIZE;
		}
	}
	else
	{
		ASSERT(this->stackSize_ != 0);

		if(this->expectedSize_ == 0)
		{
			if(this->stackTop_ >= this->stackSize_)
			{
				size_t newStackSize = this->stackSize_ + STACK_STEP_SIZE;
				STACK_ELEMENT *newStackPtr = new STACK_ELEMENT[newStackSize];
				if(newStackPtr == NULL)
				{
					ERROR("allocate new memory for stack failed! new stack size is %u.", newStackSize);
					return false;
				}
				memcpy(newStackPtr, this->stack_, sizeof(STACK_ELEMENT) * this->stackSize_);
				delete[] this->stack_;
				this->stack_ = newStackPtr;
				this->stackSize_ = newStackSize;
			}
		}
	}
	return true;
}

template <typename STACK_ELEMENT>
void Stack<STACK_ELEMENT>::destroy()
{
	if(this->stack_ != NULL)
	{
		delete[] this->stack_;
		this->stack_ = NULL;
		this->stackSize_ = 0;
		this->stackTop_ = 0;
	}
}

template <typename STACK_ELEMENT>
bool Stack<STACK_ELEMENT>::push(STACK_ELEMENT element)
{
	if(allocateSpace() == false)
	{
		ERROR("allocate space for stack failed!");
		return false;
	}

	if(this->stackTop_ >= this->stackSize_)
	{
		ERROR("stack overflow!");
		return false;
	}
	this->stack_[this->stackTop_ ++] = element;
}

template <typename STACK_ELEMENT>
STACK_ELEMENT Stack<STACK_ELEMENT>::pop()
{
	if(this->stackTop_ <= 0)
	{
		ERROR("stack is empty!");
		return NULL;
	}
	return this->stack_[-- this->stackTop_];
}

} /* namespace diamon_jvm */


#endif /* _JVM_STACK_HPP_ */
