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
 **	File Name        : ConstantUtf8.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ConstantUtf8.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

ConstantUtf8::ConstantUtf8() : Constant()
{
	this->length_ = 0;
	this->bytes_ = NULL;
}

ConstantUtf8::~ConstantUtf8()
{
	if(this->bytes_ != NULL)
	{
		delete[] this->bytes_;
		this->bytes_ = NULL;
	}
}

JVM_U2 ConstantUtf8::getLength() const
{
	return length_;
}

const JVM_U1 *ConstantUtf8::getBytes() const
{
	return bytes_;
}

bool ConstantUtf8::marshal(Stream &stream)
{
	size_t size = stream.readBytes((JVM_BYTE *)&this->length_, sizeof(this->length_));
	if(size != sizeof(this->length_))
	{
		ERROR("read length of ConstantUtf8 failed!");
		return false;
	}
	this->length_ = swap_JVM_U2(this->length_);

	if(this->length_ > 0)
	{
		this->bytes_ = new JVM_BYTE[this->length_];
		if(this->bytes_ == NULL)
		{
			ERROR("allocate memory for bytes of ConstantUtf8 failed!");
			return false;
		}
		size = stream.readBytes((JVM_BYTE *)this->bytes_, this->length_);
		if(size != this->length_)
		{
			ERROR("read bytes of ConstantUtf8 failed!");
			return false;
		}
	}

	return true;
}

} /* namespace diamon_jvm */
