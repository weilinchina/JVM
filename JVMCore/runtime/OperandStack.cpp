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
 **	File Name        : OperandStack.cpp $
 **	Created on       : Dec 7, 2012 $
 **	Time             : 4:18:09 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "OperandStack.h"


namespace diamon_jvm
{

OperandStack::OperandStack(size_t expectedSize) : Stack<JVM_INT>(expectedSize)
{
	// TODO Auto-generated constructor stub

}

OperandStack::~OperandStack()
{
	// TODO Auto-generated destructor stub
}

} /* namespace diamon_jvm */
