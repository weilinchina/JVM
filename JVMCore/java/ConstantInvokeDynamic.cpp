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
 **	File Name        : ConstantInvokeDynamic.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantInvokeDynamic.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantInvokeDynamic::ConstantInvokeDynamic() : Constant()
{
	this->bootstrap_method_attr_index_ = 0;
	this->name_and_type_index_ = 0;
}

ConstantInvokeDynamic::~ConstantInvokeDynamic()
{
	// TODO Auto-generated destructor stub
}

JVM_U2 ConstantInvokeDynamic::getBootstrapMethodAttrIndex() const
{
	return bootstrap_method_attr_index_;
}

JVM_U2 ConstantInvokeDynamic::getNameAndTypeIndex() const
{
	return name_and_type_index_;
}

bool ConstantInvokeDynamic::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->bootstrap_method_attr_index_, sizeof(this->bootstrap_method_attr_index_));
	if(size != sizeof(this->bootstrap_method_attr_index_))
	{
		ERROR("read bootstrap_method_attr_index of ConstantInvokeDynamic failed!");
		return false;
	}
	this->bootstrap_method_attr_index_ = swap_JVM_U2(this->bootstrap_method_attr_index_);

	size = stream.readBytes((JVM_BYTE *)&this->name_and_type_index_, sizeof(this->name_and_type_index_));
	if(size != sizeof(this->name_and_type_index_))
	{
		ERROR("read name_and_type_index of ConstantInvokeDynamic failed!");
		return false;
	}
	this->name_and_type_index_ = swap_JVM_U2(this->name_and_type_index_);

	return true;
}

} /* namespace diamon_jvm */
