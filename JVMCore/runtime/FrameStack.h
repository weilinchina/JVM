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
 **	File Name        : FrameStack.h $
 **	Created on       : Dec 7, 2012 $
 **	Time             : 4:17:00 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_FRAMESTACK_H_
#define _JVM_FRAMESTACK_H_


#include "GlobalDefinition.h"
#include "Frame.h"

#include "Stack.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class FrameStack : public Stack<Frame *>
{
public:
	FrameStack();
	virtual ~FrameStack();

	void destroy();
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_FRAMESTACK_H_ */
