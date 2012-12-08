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
 **	File Name        : AttributeSourceDebugExtension.cpp $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 9:51:17 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeSourceDebugExtension.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

AttributeSourceDebugExtension::AttributeSourceDebugExtension() : Attribute()
{
	this->debug_extension_ = NULL;
}

AttributeSourceDebugExtension::~AttributeSourceDebugExtension()
{
	if(this->debug_extension_ != NULL)
	{
		delete[] this->debug_extension_;
		this->debug_extension_ = NULL;
	}
}

const JVM_U1 *AttributeSourceDebugExtension::getDebugExtension() const
{
	return debug_extension_;
}

bool AttributeSourceDebugExtension::marshal(Stream &stream)
{
	// read @debug_extension_
	if(this->attribute_length_ > 0)
	{
		this->debug_extension_ = new JVM_U1[this->attribute_length_];
		if(this->debug_extension_ == NULL)
		{
			ERROR("allocate memory for debug_extension of AttributeSourceDebugExtension failed!");
			return false;
		}
		size_t size = stream.readBytes((JVM_BYTE *)this->debug_extension_, this->attribute_length_);
		if(size != this->attribute_length_)
		{
			ERROR("read debug_extension of AttributeSourceDebugExtension failed!");
			return false;
		}
	}

	return true;
}

} /* namespace diamon_jvm */
