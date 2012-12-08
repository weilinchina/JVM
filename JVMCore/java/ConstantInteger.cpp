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
 **	File Name        : ConstantInteger.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantInteger.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantInteger::ConstantInteger() : ConstantValue()
{
	this->constantValueType_ = CONSTANT_VALUE_TYPE_INTEGER;

	this->bytes_ = 0;
}

ConstantInteger::~ConstantInteger()
{
	// TODO Auto-generated destructor stub
}

JVM_U4 ConstantInteger::getBytes() const
{
	return bytes_;
}

bool ConstantInteger::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->bytes_, sizeof(this->bytes_));
	if(size != sizeof(this->bytes_))
	{
		ERROR("read bytes of ConstantInteger failed!");
		return false;
	}
	this->bytes_ = swap_JVM_U4(this->bytes_);

	return true;
}

} /* namespace diamon_jvm */
