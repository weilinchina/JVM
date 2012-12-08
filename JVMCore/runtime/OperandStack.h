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
 **	File Name        : OperandStack.h $
 **	Created on       : Dec 7, 2012 $
 **	Time             : 4:18:09 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_OPERANDSTACK_H_
#define _JVM_OPERANDSTACK_H_


#include "GlobalDefinition.h"
#include "Stack.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class OperandStack : public Stack<JVM_INT>
{
public:
	OperandStack(size_t expectedSize);
	virtual ~OperandStack();
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_OPERANDSTACK_H_ */
