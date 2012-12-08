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
 **	File Name        : ConstantMethodHandle.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantMethodHandle.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantMethodHandle::ConstantMethodHandle() : Constant()
{
	this->reference_kind_ = 0;
	this->reference_index_ = 0;
}

ConstantMethodHandle::~ConstantMethodHandle()
{
	// TODO Auto-generated destructor stub
}

JVM_U1 ConstantMethodHandle::getReferenceKind() const
{
	return reference_kind_;
}

JVM_U2 ConstantMethodHandle::getReferenceIndex() const
{
	return reference_index_;
}

bool ConstantMethodHandle::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->reference_kind_, sizeof(this->reference_kind_));
	if(size != sizeof(this->reference_kind_))
	{
		ERROR("read reference_kind of ConstantMethodHandle failed!");
		return false;
	}

	size = stream.readBytes((JVM_BYTE *)&this->reference_index_, sizeof(this->reference_index_));
	if(size != sizeof(this->reference_index_))
	{
		ERROR("read reference_index of ConstantMethodHandle failed!");
		return false;
	}
	this->reference_index_ = swap_JVM_U2(this->reference_index_);

	return true;
}

} /* namespace diamon_jvm */
