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
 **	File Name        : Stack.h $
 **	Created on       : Dec 6, 2012 $
 **	Time             : 2:23:11 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_STACK_H_
#define _JVM_STACK_H_


#include "GlobalDefinition.h"


namespace diamon_jvm
{

template <typename STACK_ELEMENT>
class Stack
{
protected:
	STACK_ELEMENT *stack_;
	size_t stackSize_;
	size_t stackTop_;
	size_t expectedSize_;

protected:
	bool allocateSpace();
	virtual void destroy();

public:
	Stack();
	Stack(size_t expectedSize);
	virtual ~Stack();

	bool push(STACK_ELEMENT element);
	STACK_ELEMENT pop();
};

} /* namespace diamon_jvm */


#include "Stack.hpp"


#endif /* _JVM_STACK_H_ */
