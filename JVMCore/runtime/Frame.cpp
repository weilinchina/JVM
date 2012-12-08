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
 **	File Name        : Frame.cpp $
 **	Created on       : Dec 7, 2012 $
 **	Time             : 4:28:02 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "Frame.h"


namespace diamon_jvm
{

Frame::Frame()
{
	this->operandStack_ = NULL;
}

Frame::~Frame()
{
	if(this->operandStack_ != NULL)
	{
		delete this->operandStack_;
		this->operandStack_ = NULL;
	}
}

bool Frame::init()
{
	if(this->operandStack_ == NULL)
	{
		this->operandStack_ = new OperandStack(10);
		if(this->operandStack_ == NULL)
			return false;
	}
	return true;
}

} /* namespace diamon_jvm */
