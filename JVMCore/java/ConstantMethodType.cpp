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
 **	File Name        : ConstantMethodType.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantMethodType.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantMethodType::ConstantMethodType() : Constant()
{
	this->descriptor_index_ = 0;
}

ConstantMethodType::~ConstantMethodType()
{
	// TODO Auto-generated destructor stub
}

JVM_U2 ConstantMethodType::getDescriptorIndex() const
{
	return descriptor_index_;
}

bool ConstantMethodType::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->descriptor_index_, sizeof(this->descriptor_index_));
	if(size != sizeof(this->descriptor_index_))
	{
		ERROR("read descriptor_index of ConstantMethodType failed!");
		return false;
	}
	this->descriptor_index_ = swap_JVM_U2(this->descriptor_index_);

	return true;
}

} /* namespace diamon_jvm */
