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
 **	File Name        : Field.cpp $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 5:59:53 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "Field.h"

#include "JVMUtility.h"
#include "AccessFlags.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

Field::Field()
{
	this->access_flags_ = 0;
	this->name_index_ = 0;
	this->descriptor_index_ = 0;

	this->fieldName_ = "";
	this->fieldDescriptor_ = "";
	this->attributeConstantValue_ = NULL;
	this->attributeSignature_ = NULL;
	this->deprecated_ = false;

	this->constant_count_ = 0;
	this->constants_ = NULL;
}

Field::~Field()
{
	if(this->attributeConstantValue_ != NULL)
	{
		delete this->attributeConstantValue_;
		this->attributeConstantValue_ = NULL;
	}

	if(this->attributeSignature_ != NULL)
	{
		delete this->attributeSignature_;
		this->attributeSignature_ = NULL;
	}
}

JVM_U2 Field::getAccessFlags() const
{
	return access_flags_;
}

JVM_U2 Field::getNameIndex() const
{
	return name_index_;
}

JVM_U2 Field::getDescriptorIndex() const
{
	return descriptor_index_;
}

const std::string &Field::getFieldName() const
{
	return fieldName_;
}

const std::string &Field::getFieldDescriptor() const
{
	return fieldDescriptor_;
}

const AttributeConstantValue *Field::getAttributeConstantValue() const
{
	return attributeConstantValue_;
}

const AttributeSignature *Field::getAttributeSignature() const
{
	return attributeSignature_;
}

bool Field::isDeprecated()
{
	return deprecated_;
}

bool Field::marshal(Stream &stream)
{
	// read @access_flags_
	size_t size = stream.readBytes((JVM_BYTE *)(&this->access_flags_), sizeof(this->access_flags_));
	if(size != sizeof(this->access_flags_))
	{
		ERROR("read access_flags of Field failed!");
		return false;
	}
	this->access_flags_ = swap_JVM_U2(this->access_flags_);
	/*
	if(this->access_flags_ & (~FIELD_ACC_FLAGS))
	{
		ERROR("check access_flags of Field failed!");
		return false;
	}
	*/

	// read @name_index_
	size = stream.readBytes((JVM_BYTE*)(&this->name_index_), sizeof(this->name_index_));
	if(size != sizeof(this->name_index_))
	{
		ERROR("read name_index of Field failed!");
		return false;
	}
	this->name_index_ = swap_JVM_U2(this->name_index_);
	ConstantUtf8 *javaCPUtf8_name = (ConstantUtf8 *)Constant::getConstant(this->name_index_, this->constant_count_, this->constants_);
	if(javaCPUtf8_name != NULL)
	{
		this->fieldName_.assign((char *)(javaCPUtf8_name->getBytes()), javaCPUtf8_name->getLength());
		TRACE("field name is: %s", this->fieldName_.c_str());
	}

	// read @descriptor_index_
	size = stream.readBytes((JVM_BYTE*)(&this->descriptor_index_), sizeof(this->descriptor_index_));
	if(size != sizeof(this->descriptor_index_))
	{
		ERROR("read descriptor_index of Field failed!");
		return false;
	}
	this->descriptor_index_ = swap_JVM_U2(this->descriptor_index_);
	ConstantUtf8 *javaCPUtf8_descriptor = (ConstantUtf8 *)Constant::getConstant(this->descriptor_index_, this->constant_count_, this->constants_);
	if(javaCPUtf8_descriptor != NULL)
	{
		this->fieldDescriptor_.assign((char *)(javaCPUtf8_descriptor->getBytes()), javaCPUtf8_descriptor->getLength());
		TRACE("field descriptor is: %s", this->fieldDescriptor_.c_str());
	}

	// read @attributes_count_
	JVM_U2 attributes_count = 0;
	size = stream.readBytes((JVM_BYTE*)(&attributes_count), sizeof(attributes_count));
	if(size != sizeof(attributes_count))
	{
		ERROR("read attributes_count of Field failed!");
		return false;
	}
	attributes_count = swap_JVM_U2(attributes_count);

	// read @attributes_
	if(attributes_count > 0)
	{
		for(size_t i = 0; i < attributes_count; i++)
		{
			// read @attribute_name_index
			JVM_U2 attribute_name_index = 0;
			size_t size = stream.readBytes((JVM_BYTE *)(&attribute_name_index), sizeof(attribute_name_index));
			if(size != sizeof(attribute_name_index))
			{
				ERROR("read attribute_name_index %d of Field failed!", i);
				return false;
			}
			attribute_name_index = swap_JVM_U2(attribute_name_index);
			ConstantUtf8 *javaCPUtf8_name = (ConstantUtf8 *)Constant::getConstant(attribute_name_index, this->constant_count_, this->constants_);
			if(javaCPUtf8_name == NULL)
			{
				ERROR("locate attribute_name by attribute_name_index #%d of Field failed!", attribute_name_index);
				return false;
			}
			std::string attributeName((char *)(javaCPUtf8_name->getBytes()), javaCPUtf8_name->getLength());
			TRACE("attribute name is: %s", attributeName.c_str());

			// read @attribute_length
			JVM_U4 attribute_length = 0;
			size = stream.readBytes((JVM_BYTE*)(&attribute_length), sizeof(attribute_length));
			if(size != sizeof(attribute_length))
			{
				ERROR("read attribute_length %d of Field failed!", i);
				return false;
			}
			attribute_length = swap_JVM_U4(attribute_length);

			if(attributeName.compare("ConstantValue") == 0)
			{
				this->attributeConstantValue_ = new AttributeConstantValue();
				if(this->attributeConstantValue_ == NULL)
				{
					ERROR("allocate memory for AttributeConstantValue of Field failed!");
					return false;
				}
				this->attributeConstantValue_->attribute_name_index_ = attribute_name_index;
				this->attributeConstantValue_->attribute_length_ = attribute_length;
				this->attributeConstantValue_->attributeName_ = attributeName;
				this->attributeConstantValue_->constant_count_ = this->constant_count_;
				this->attributeConstantValue_->constants_ = this->constants_;
				if(this->attributeConstantValue_->marshal(stream) == false)
				{
					ERROR("marshal AttributeConstantValue of Field failed!");
					return false;
				}
			}
			else if(attributeName.compare("Synthetic") == 0)
			{
				TRACE("set flag ACC_SYNTHETIC for field.");
				this->access_flags_ |= ACC_SYNTHETIC;
			}
			// for class file version equals or above 49.0
			else if(attributeName.compare("Signature") == 0)
			{
				this->attributeSignature_ = new AttributeSignature();
				if(this->attributeSignature_ == NULL)
				{
					ERROR("allocate memory for AttributeSignature of Field failed!");
					return false;
				}
				this->attributeSignature_->attribute_name_index_ = attribute_name_index;
				this->attributeSignature_->attribute_length_ = attribute_length;
				this->attributeSignature_->attributeName_ = attributeName;
				this->attributeSignature_->constant_count_ = this->constant_count_;
				this->attributeSignature_->constants_ = this->constants_;
				if(this->attributeSignature_->marshal(stream) == false)
				{
					ERROR("marshal AttributeSignature of Field failed!");
					return false;
				}
			}
			else if(attributeName.compare("Deprecated") == 0)
			{
				TRACE("set flag DEPRECATED for field.");
				this->deprecated_ = true;
			}
			else
			{
				if(Attribute::marshal(stream, attribute_name_index, attribute_length) == false)
				{
					ERROR("marshal attribute %d of Field failed!", i);
					return false;
				}
			}
		}
	}

	return true;
}

const Field *Field::getField(JVM_U2 at, JVM_U2 fields_count, Field **fields)
{
	if(at < 0 || at > fields_count - 1)
	{
		ERROR("invalid index to locate field!, should be between %d and %d", 0, fields_count - 1);
		return NULL;
	}
	if(fields == NULL)
	{
		ERROR("no field defined in class!");
		return NULL;
	}
	return fields[at];
}

} /* namespace diamon_jvm */
