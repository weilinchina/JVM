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
 **	File Name        : ConstantString.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantString.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantString::ConstantString() : ConstantValue()
{
	this->constantValueType_ = CONSTANT_VALUE_TYPE_STRING;

	this->string_index_ = 0;
}

ConstantString::~ConstantString()
{
	// TODO Auto-generated destructor stub
}

JVM_U2 ConstantString::getStringIndex() const
{
	return string_index_;
}

bool ConstantString::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->string_index_, sizeof(this->string_index_));
	if(size != sizeof(this->string_index_))
	{
		ERROR("read string_index of ConstantString failed!");
		return false;
	}
	this->string_index_ = swap_JVM_U2(this->string_index_);

	return true;
}

} /* namespace diamon_jvm */
