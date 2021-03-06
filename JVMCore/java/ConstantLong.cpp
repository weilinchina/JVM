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
 **	File Name        : ConstantLong.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantLong.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantLong::ConstantLong() : ConstantValue()
{
	this->constantValueType_ = CONSTANT_VALUE_TYPE_LONG;

	this->high_bytes_ = 0;
	this->low_bytes_ = 0;
}

ConstantLong::~ConstantLong()
{
	// TODO Auto-generated destructor stub
}

JVM_U4 ConstantLong::getHighBytes() const
{
	return high_bytes_;
}

JVM_U4 ConstantLong::getLowBytes() const
{
	return low_bytes_;
}

bool ConstantLong::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->high_bytes_, sizeof(this->high_bytes_));
	if(size != sizeof(this->high_bytes_))
	{
		ERROR("read high_bytes of ConstantLong failed!");
		return false;
	}
	this->high_bytes_ = swap_JVM_U4(this->high_bytes_);

	size = stream.readBytes((JVM_BYTE *)&this->low_bytes_, sizeof(this->low_bytes_));
	if(size != sizeof(this->low_bytes_))
	{
		ERROR("read low_bytes of ConstantLong failed!");
		return false;
	}
	this->low_bytes_ = swap_JVM_U4(this->low_bytes_);

	return true;
}

} /* namespace diamon_jvm */
