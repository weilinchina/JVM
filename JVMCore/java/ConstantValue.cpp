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
 **	File Name        : ConstantValue.cpp $
 **	Created on       : Nov 24, 2012 $
 **	Time             : 5:30:13 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantValue.h"


namespace diamon_jvm
{

ConstantValue::ConstantValue() : Constant()
{
	this->constantValueType_ = CONSTANT_VALUE_TYPE_UNKNOWN;
}

ConstantValue::~ConstantValue()
{
	// TODO Auto-generated destructor stub
}

const CONSTANT_VALUE_TYPE ConstantValue::getConstantValueType() const
{
	return constantValueType_;
}

} /* namespace diamon_jvm */
