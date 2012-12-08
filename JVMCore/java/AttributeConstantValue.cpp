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
 **	File Name        : AttributeConstantValue.cpp $
 **	Created on       : Nov 18, 2012 $
 **	Time             : 10:29:06 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeConstantValue.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantString.h"
#include "ConstantInteger.h"
#include "ConstantDouble.h"
#include "ConstantFloat.h"
#include "ConstantLong.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeConstantValue::AttributeConstantValue() : Attribute()
{
	this->constantvalue_index_ = 0;

	this->javaConstantValue_ = NULL;
}

AttributeConstantValue::~AttributeConstantValue()
{
}

JVM_U2 AttributeConstantValue::getConstantvalueIndex() const
{
	return constantvalue_index_;
}

const ConstantValue *AttributeConstantValue::getJavaConstantValue() const
{
	return javaConstantValue_;
}

const CONSTANT_VALUE_TYPE AttributeConstantValue::getValueType() const
{
	return this->javaConstantValue_->getConstantValueType();
}

const std::string AttributeConstantValue::getValue() const
{
	if(this->javaConstantValue_->getConstantValueType() == CONSTANT_VALUE_TYPE_LONG)
	{
		char buf[20 + 1] = {0};
		snprintf(buf, 20, "%ld", getLongValue());
		std::string s(buf);
		return s;
	}
	else if(this->javaConstantValue_->getConstantValueType() == CONSTANT_VALUE_TYPE_FLOAT)
	{
		char buf[20 + 1] = {0};
		snprintf(buf, 20, "%f", getFloatValue());
		std::string s(buf);
		return s;
	}
	else if(this->javaConstantValue_->getConstantValueType() == CONSTANT_VALUE_TYPE_DOUBLE)
	{
		char buf[20 + 1] = {0};
		snprintf(buf, 20, "%f", getDoubleValue());
		std::string s(buf);
		return s;
	}
	else if(this->javaConstantValue_->getConstantValueType() == CONSTANT_VALUE_TYPE_INTEGER)
	{
		char buf[20 + 1] = {0};
		snprintf(buf, 20, "%d", getIntValue());
		std::string s(buf);
		return s;
	}
	else if(this->javaConstantValue_->getConstantValueType() == CONSTANT_VALUE_TYPE_STRING)
	{
		return getStringValue();
	}

	ERROR("no such constant value type %d!", this->javaConstantValue_->getConstantValueType());
	ASSERT(false);
}

const std::string AttributeConstantValue::getStringValue() const
{
	ConstantUtf8 *javaConstantUtf8 = (ConstantUtf8 *)Constant::getConstant(((ConstantString *)this->javaConstantValue_)->getStringIndex(), this->constant_count_, this->constants_);
	if(javaConstantUtf8 == NULL)
		return "";
	return std::string((char *)javaConstantUtf8->getBytes(), javaConstantUtf8->getLength());
}

JVM_INT AttributeConstantValue::getIntValue() const
{
	return (JVM_INT)((ConstantInteger *)this->javaConstantValue_)->getBytes();
}

JVM_DOUBLE AttributeConstantValue::getDoubleValue() const
{
	return (JVM_DOUBLE)(((ConstantDouble *)this->javaConstantValue_)->getHighBytes() << 32 | ((ConstantDouble *)this->javaConstantValue_)->getLowBytes());
}

JVM_FLOAT AttributeConstantValue::getFloatValue() const
{
	return (JVM_FLOAT)((ConstantFloat *)this->javaConstantValue_)->getBytes();
}

JVM_LONG AttributeConstantValue::getLongValue() const
{
	return (JVM_LONG)(((ConstantLong *)this->javaConstantValue_)->getHighBytes() << 32 | ((ConstantLong *)this->javaConstantValue_)->getLowBytes());
}

bool AttributeConstantValue::marshal(Stream &stream)
{
	// read @constantvalue_index_
	size_t size = stream.readBytes((JVM_BYTE *)&this->constantvalue_index_, sizeof(this->constantvalue_index_));
	if(size != sizeof(this->constantvalue_index_))
	{
		ERROR("read constantvalue_index of AttributeConstantValue failed!");
		return false;
	}
	this->constantvalue_index_ = swap_JVM_U2(this->constantvalue_index_);
	this->javaConstantValue_ = (ConstantValue *)Constant::getConstant(this->constantvalue_index_, this->constant_count_, this->constants_);
	if(this->javaConstantValue_ == NULL)
	{
		ERROR("constant for constant value not exist!");
		return false;
	}
	TRACE("const value type: %d - const value: %s", getValueType(), getValue().c_str());

	return true;
}

} /* namespace diamon_jvm */
