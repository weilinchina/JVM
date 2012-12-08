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
 **	File Name        : ConstantFieldRef.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:22:32 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantFieldRef.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantFieldRef::ConstantFieldRef() : Constant()
{
	this->class_index_ = 0;
	this->name_and_type_index_ = 0;
}

ConstantFieldRef::~ConstantFieldRef()
{
	// TODO Auto-generated destructor stub
}

JVM_U2 ConstantFieldRef::getClassIndex() const
{
	return class_index_;
}

JVM_U2 ConstantFieldRef::getNameAndTypeIndex() const
{
	return name_and_type_index_;
}

bool ConstantFieldRef::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->class_index_, sizeof(this->class_index_));
	if(size != sizeof(this->class_index_))
	{
		ERROR("read class_index of ConstantFieldRef failed!");
		return false;
	}
	this->class_index_ = swap_JVM_U2(this->class_index_);

	size = stream.readBytes((JVM_BYTE *)&this->name_and_type_index_, sizeof(this->name_and_type_index_));
	if(size != sizeof(this->name_and_type_index_))
	{
		ERROR("read name_and_type_index of ConstantFieldRef failed!");
		return false;
	}
	this->name_and_type_index_ = swap_JVM_U2(this->name_and_type_index_);

	return true;
}

} /* namespace diamon_jvm */
