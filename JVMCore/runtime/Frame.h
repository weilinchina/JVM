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
 **	File Name        : Frame.h $
 **	Created on       : Dec 7, 2012 $
 **	Time             : 4:28:02 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_FRAME_H_
#define _JVM_FRAME_H_


#include "GlobalDefinition.h"
#include "OperandStack.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Frame
{
protected:
	OperandStack *operandStack_;

public:
	Frame();
	virtual ~Frame();

	bool init();
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_FRAME_H_ */
