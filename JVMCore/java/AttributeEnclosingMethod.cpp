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
 **	File Name        : AttributeEnclosingMethod.cpp $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 1:06:18 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeEnclosingMethod.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantClass.h"
#include "ConstantUtf8.h"
#include "ConstantNameAndType.h"


namespace diamon_jvm
{

AttributeEnclosingMethod::AttributeEnclosingMethod() : Attribute()
{
	this->class_index_ = 0;
	this->method_index_ = 0;

	this->className_ = "";
	this->methodName_ = "";
	this->methodDescriptor_ = "";
}

AttributeEnclosingMethod::~AttributeEnclosingMethod()
{
	// TODO Auto-generated destructor stub
}

JVM_U2 AttributeEnclosingMethod::getClassIndex() const
{
	return class_index_;
}

JVM_U2 AttributeEnclosingMethod::getMethodIndex() const
{
	return method_index_;
}

const std::string &AttributeEnclosingMethod::getClassName() const
{
	return className_;
}

const std::string &AttributeEnclosingMethod::getMethodDescriptor() const
{
	return methodDescriptor_;
}

const std::string &AttributeEnclosingMethod::getMethodName() const
{
	return methodName_;
}

bool AttributeEnclosingMethod::marshal(Stream &stream)
{
	// read @class_index_
	size_t size = stream.readBytes((JVM_BYTE *)&this->class_index_, sizeof(this->class_index_));
	if(size != sizeof(this->class_index_))
	{
		ERROR("read class_index of AttributeEnclosingMethod failed!");
		return false;
	}
	this->class_index_ = swap_JVM_U2(this->class_index_);
	ConstantClass *javaConstantClass_class = (ConstantClass *)Constant::getConstant(this->class_index_, this->constant_count_, this->constants_);
	if(javaConstantClass_class != NULL)
	{
		ConstantUtf8 *javaConstantUtf8_class = (ConstantUtf8 *)Constant::getConstant(javaConstantClass_class->getNameIndex(), this->constant_count_, this->constants_);
		if(javaConstantUtf8_class != NULL)
		{
			this->className_.assign((char *)javaConstantUtf8_class->getBytes(), javaConstantUtf8_class->getLength());
			TRACE("enclosing class name is: %s", this->className_.c_str());
		}
	}

	// read @method_index_
	size = stream.readBytes((JVM_BYTE *)&this->method_index_, sizeof(this->method_index_));
	if(size != sizeof(this->method_index_))
	{
		ERROR("read method_index of AttributeEnclosingMethod failed!");
		return false;
	}
	this->method_index_ = swap_JVM_U2(this->method_index_);

	this->methodName_ = "";
	this->methodDescriptor_ = "";
	if(this->method_index_ != 0)
	{
		ConstantNameAndType *javaConstantNameAndType_method = (ConstantNameAndType *)Constant::getConstant(this->method_index_, this->constant_count_, this->constants_);
		if(javaConstantNameAndType_method != NULL)
		{
			ConstantUtf8 *javaConstantUtf8_method_name = (ConstantUtf8 *)Constant::getConstant(javaConstantNameAndType_method->getNameIndex(), this->constant_count_, this->constants_);
			if(javaConstantUtf8_method_name != NULL)
			{
				this->methodName_.assign((char *)javaConstantUtf8_method_name->getBytes(), javaConstantUtf8_method_name->getLength());
				TRACE("enclosing class method name is: %s", this->methodName_.c_str());
			}
			ConstantUtf8 *javaConstantUtf8_method_descriptor = (ConstantUtf8 *)Constant::getConstant(javaConstantNameAndType_method->getDescriptorIndex(), this->constant_count_, this->constants_);
			if(javaConstantUtf8_method_descriptor != NULL)
			{
				this->methodDescriptor_.assign((char *)javaConstantUtf8_method_descriptor->getBytes(), javaConstantUtf8_method_descriptor->getLength());
				TRACE("enclosing class method name is: %s", this->methodDescriptor_.c_str());
			}
		}
	}

	return true;
}

} /* namespace diamon_jvm */
