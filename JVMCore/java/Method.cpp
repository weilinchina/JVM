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
 **	File Name        : Method.cpp $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 5:53:48 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "Method.h"

#include "JVMUtility.h"
#include "AccessFlags.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

Method::Method()
{
	this->access_flags_ = 0;
	this->name_index_ = 0;
	this->descriptor_index_ = 0;

	this->methodName_ = "";
	this->methodDescriptor_ = "";
	this->attributeCode_ = NULL;
	this->attributeExceptions_ = NULL;
	this->attributeSignature_ = NULL;
	this->deprecated_ = false;

	this->constant_count_ = 0;
	this->constants_ = NULL;
}

Method::~Method()
{
	if(this->attributeCode_ != NULL)
	{
		delete this->attributeCode_;
		this->attributeCode_ = NULL;
	}

	if(this->attributeExceptions_ != NULL)
	{
		delete this->attributeExceptions_;
		this->attributeExceptions_ = NULL;
	}

	if(this->attributeSignature_ != NULL)
	{
		delete this->attributeSignature_;
		this->attributeSignature_ = NULL;
	}
}

JVM_U2 Method::getAccessFlags() const
{
	return access_flags_;
}

JVM_U2 Method::getDescriptorIndex() const
{
	return descriptor_index_;
}

JVM_U2 Method::getNameIndex() const
{
	return name_index_;
}

const std::string &Method::getMethodName() const
{
	return methodName_;
}

const std::string &Method::getMethodDescriptor() const
{
	return methodDescriptor_;
}

const AttributeCode *Method::getAttributeCode() const
{
	return attributeCode_;
}

const AttributeExceptions *Method::getAttributeExceptions() const
{
	return attributeExceptions_;
}

const AttributeSignature *Method::getAttributeSignature() const
{
	return attributeSignature_;
}

bool Method::isDeprecated()
{
	return deprecated_;
}

bool Method::marshal(Stream & stream)
{
	// read @access_flags_
	size_t size = stream.readBytes((JVM_BYTE*)(&this->access_flags_), sizeof(this->access_flags_));
	if(size != sizeof(this->access_flags_))
	{
		ERROR("read access_flags of Method failed!");
		return false;
	}
	this->access_flags_ = swap_JVM_U2(this->access_flags_);
	/*
	if(this->access_flags_ & (~METHOD_ACC_FLAGS))
	{
		ERROR("check access_flags of Method failed!");
		return false;
	}
	*/

	// read @name_index_
	size = stream.readBytes((JVM_BYTE*)(&this->name_index_), sizeof(this->name_index_));
	if(size != sizeof(this->name_index_))
	{
		ERROR("read name_index of Method failed!");
		return false;
	}
	this->name_index_ = swap_JVM_U2(this->name_index_);
	ConstantUtf8 *javaCPUtf8_name = (ConstantUtf8 *)Constant::getConstant(this->name_index_, this->constant_count_, this->constants_);
	if(javaCPUtf8_name != NULL)
	{
		this->methodName_.assign((char *)(javaCPUtf8_name->getBytes()), javaCPUtf8_name->getLength());
		TRACE("method name is: %s", this->methodName_.c_str());
	}

	// read @descriptor_index_
	size = stream.readBytes((JVM_BYTE*)(&this->descriptor_index_), sizeof(this->descriptor_index_));
	if(size != sizeof(this->descriptor_index_))
	{
		ERROR("read descriptor_index of Method failed!");
		return false;
	}
	this->descriptor_index_ = swap_JVM_U2(this->descriptor_index_);
	ConstantUtf8 *javaCPUtf8_descriptor = (ConstantUtf8 *)Constant::getConstant(this->descriptor_index_, this->constant_count_, this->constants_);
	if(javaCPUtf8_descriptor != NULL)
	{
		this->methodDescriptor_.assign((char *)(javaCPUtf8_descriptor->getBytes()), javaCPUtf8_descriptor->getLength());
		TRACE("method descriptor is: %s", this->methodDescriptor_.c_str());
	}

	// read @attributes_count_
	JVM_U2 attributes_count = 0;
	size = stream.readBytes((JVM_BYTE*)(&attributes_count), sizeof(attributes_count));
	if(size != sizeof(attributes_count))
	{
		ERROR("read attributes_count of Method failed!");
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
				ERROR("read attribute_name_index %d of Method failed!", i);
				return false;
			}
			attribute_name_index = swap_JVM_U2(attribute_name_index);
			ConstantUtf8 *javaCPUtf8_name = (ConstantUtf8 *)Constant::getConstant(attribute_name_index, this->constant_count_, this->constants_);
			if(javaCPUtf8_name == NULL)
			{
				ERROR("locate attribute_name by attribute_name_index #%d of Method failed!", attribute_name_index);
				return false;
			}
			std::string attributeName((char *)(javaCPUtf8_name->getBytes()), javaCPUtf8_name->getLength());
			TRACE("attribute name is: %s", attributeName.c_str());

			// read @attribute_length
			JVM_U4 attribute_length = 0;
			size = stream.readBytes((JVM_BYTE*)(&attribute_length), sizeof(attribute_length));
			if(size != sizeof(attribute_length))
			{
				ERROR("read attribute_length %d of Method failed!", i);
				return false;
			}
			attribute_length = swap_JVM_U4(attribute_length);

			if(attributeName.compare("Code") == 0)
			{
				this->attributeCode_ = new AttributeCode();
				if(this->attributeCode_ == NULL)
				{
					ERROR("allocate memory for AttributeCode of Method failed!");
					return false;
				}
				this->attributeCode_->attribute_name_index_ = attribute_name_index;
				this->attributeCode_->attribute_length_ = attribute_length;
				this->attributeCode_->attributeName_ = attributeName;
				this->attributeCode_->constant_count_ = this->constant_count_;
				this->attributeCode_->constants_ = this->constants_;
				if(this->attributeCode_->marshal(stream) == false)
				{
					ERROR("marshal AttributeCode of Method failed!");
					return false;
				}
			}
			else if(attributeName.compare("Exceptions") == 0)
			{
				this->attributeExceptions_ = new AttributeExceptions();
				if(this->attributeExceptions_ == NULL)
				{
					ERROR("allocate memory for AttributeExceptions of Method failed!");
					return false;
				}
				this->attributeExceptions_->attribute_name_index_ = attribute_name_index;
				this->attributeExceptions_->attribute_length_ = attribute_length;
				this->attributeExceptions_->attributeName_ = attributeName;
				this->attributeExceptions_->constant_count_ = this->constant_count_;
				this->attributeExceptions_->constants_ = this->constants_;
				if(this->attributeExceptions_->marshal(stream) == false)
				{
					ERROR("marshal AttributeExceptions of Method failed!");
					return false;
				}
			}
			else if(attributeName.compare("Synthetic") == 0)
			{
				TRACE("set flag ACC_SYNTHETIC for method.");
				this->access_flags_ |= ACC_SYNTHETIC;
			}
			// for class file version equals or above 49.0
			else if(attributeName.compare("Signature") == 0)
			{
				this->attributeSignature_ = new AttributeSignature();
				if(this->attributeSignature_ == NULL)
				{
					ERROR("allocate memory for AttributeSignature of Method failed!");
					return false;
				}
				this->attributeSignature_->attribute_name_index_ = attribute_name_index;
				this->attributeSignature_->attribute_length_ = attribute_length;
				this->attributeSignature_->attributeName_ = attributeName;
				this->attributeSignature_->constant_count_ = this->constant_count_;
				this->attributeSignature_->constants_ = this->constants_;
				if(this->attributeSignature_->marshal(stream) == false)
				{
					ERROR("marshal AttributeSignature of Method failed!");
					return false;
				}
			}
			else if(attributeName.compare("Deprecated") == 0)
			{
				TRACE("set flag DEPRECATED for method.");
				this->deprecated_ = true;
			}
			else
			{
				if(Attribute::marshal(stream, attribute_name_index, attribute_length) == false)
				{
					ERROR("marshal attribute %d of Method failed!", i);
					return false;
				}
			}
		}
	}

	return true;
}

INLINE
const Method *Method::getMethod(JVM_U2 at, JVM_U2 methods_count, Method **methods)
{
	if(at < 0 || at > methods_count - 1)
	{
		ERROR("invalid index to locate method!, should be between %d and %d", 0, methods_count - 1);
		return NULL;
	}
	if(methods == NULL)
	{
		ERROR("no method defined in class!");
		return NULL;
	}
	return methods[at];
}

} /* namespace diamon_jvm */
