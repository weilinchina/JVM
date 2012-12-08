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
 **	File Name        : Attribute.cpp $
 **	Created on       : Nov 17, 2012 $
 **	Time             : 8:57:52 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "Attribute.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

Attribute::Attribute()
{
	this->attribute_name_index_ = 0;
	this->attribute_length_ = 0;
	this->info_ = NULL;

	this->attributeName_ = "";

	this->constant_count_ = 0;
	this->constants_ = NULL;
}

Attribute::~Attribute()
{
	if(this->info_ != NULL)
	{
		delete[] this->info_;
		this->info_ = NULL;
	}
}

JVM_U4 Attribute::getAttributeLength() const
{
	return attribute_length_;
}

JVM_U2 Attribute::getAttributeNameIndex() const
{
	return attribute_name_index_;
}

const JVM_BYTE *Attribute::getInfo() const
{
	return info_;
}

const std::string &Attribute::getAttributeName() const
{
	return attributeName_;
}

bool Attribute::marshal(Stream &stream)
{
	// read @attribute_name_index_
	size_t size = stream.readBytes((JVM_BYTE *)(&this->attribute_name_index_), sizeof(this->attribute_name_index_));
	if(size != sizeof(this->attribute_name_index_))
	{
		ERROR("read attribute_name_index of Attribute failed!");
		return false;
	}
	this->attribute_name_index_ = swap_JVM_U2(this->attribute_name_index_);
	ConstantUtf8 *javaCPUtf8_name = (ConstantUtf8 *)Constant::getConstant(this->attribute_name_index_, this->constant_count_, this->constants_);
	if(javaCPUtf8_name != NULL)
	{
		this->attributeName_.assign((char *)(javaCPUtf8_name->getBytes()), javaCPUtf8_name->getLength());
		TRACE("attribute name is: %s", this->attributeName_.c_str());
	}

	// read @attribute_length_
	size = stream.readBytes((JVM_BYTE*)(&this->attribute_length_), sizeof(this->attribute_length_));
	if(size != sizeof(this->attribute_length_))
	{
		ERROR("read attribute_length of Attribute failed!");
		return false;
	}
	this->attribute_length_ = swap_JVM_U4(this->attribute_length_);

	// read @info_
	if(this->attribute_length_ > 0)
	{
		this->info_ = new JVM_BYTE[this->attribute_length_];
		size = stream.readBytes(this->info_, this->attribute_length_);
		if(size != this->attribute_length_)
		{
			ERROR("read info of Attribute failed!");
			return false;
		}
	}

	return true;
}

bool Attribute::marshal(Stream &stream, JVM_U2 attribute_name_index, JVM_U4 attribute_length)
{
	if(attribute_length > 0)
	{
		JVM_U1 *info = new JVM_BYTE[attribute_length];
		if(info == NULL)
		{
			ERROR("allocate memory for info of Attribute failed!");
			return false;
		}
		size_t size = stream.readBytes(info, attribute_length);
		delete[] info;
		if(size != attribute_length)
		{
			ERROR("read info of Attribute failed!");
			return false;
		}
	}

	return true;
}

} /* namespace diamon_jvm */
