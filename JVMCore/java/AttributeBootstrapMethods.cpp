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
 **	File Name        : AttributeBootstrapMethods.cpp $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 10:12:53 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeBootstrapMethods.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantMethodHandle.h"


namespace diamon_jvm
{

AttributeBootstrapMethods::AttributeBootstrapMethods() : Attribute()
{
	this->num_bootstrap_methods_ = 0;
	this->bootstrap_methods_ = NULL;
}

AttributeBootstrapMethods::~AttributeBootstrapMethods()
{
	if(this->bootstrap_methods_ != NULL)
	{
		for(int i = 0; i < this->num_bootstrap_methods_; i ++)
		{
			BOOTSTRAP_METHOD &bootStrapMethod = this->bootstrap_methods_[i];
			if(bootStrapMethod.bootstrap_arguments_ != NULL)
			{
				delete[] bootStrapMethod.bootstrap_arguments_;
				bootStrapMethod.bootstrap_arguments_ = NULL;
			}
		}
		delete[] this->bootstrap_methods_;
		this->bootstrap_methods_ = NULL;
	}
}

JVM_U2 AttributeBootstrapMethods::getNumBootstrapMethods() const
{
	return num_bootstrap_methods_;
}

const BOOTSTRAP_METHOD *AttributeBootstrapMethods::getBootstrapMethod(int at) const
{
	if(at < 0 || at > num_bootstrap_methods_ - 1)
	{
		ERROR("invalid index to locate BOOTSTRAP_METHOD! should be between %d and %d.", 0, num_bootstrap_methods_ - 1);
		return NULL;
	}
	if(bootstrap_methods_ == NULL)
	{
		ERROR("no BOOTSTRAP_METHOD defined!");
		return NULL;
	}
	return &bootstrap_methods_[at];
}

bool AttributeBootstrapMethods::marshal(Stream &stream)
{
	// read @num_bootstrap_methods_
	size_t size = stream.readBytes((JVM_BYTE *)&this->num_bootstrap_methods_, sizeof(this->num_bootstrap_methods_));
	if(size != sizeof(this->num_bootstrap_methods_))
	{
		ERROR("read num_bootstrap_methods of AttributeBootstrapMethods failed!");
		return false;
	}
	this->num_bootstrap_methods_ = swap_JVM_U2(this->num_bootstrap_methods_);

	// read @bootstrap_methods_
	if(this->num_bootstrap_methods_ > 0)
	{
		this->bootstrap_methods_ = new BOOTSTRAP_METHOD[this->num_bootstrap_methods_];
		if(this->bootstrap_methods_ == NULL)
		{
			ERROR("allocate memory for bootstrap_methods of AttributeBootstrapMethods failed!");
			return false;
		}
		for(int i = 0; i < this->num_bootstrap_methods_; i ++)
		{
			size = stream.readBytes((JVM_BYTE *)&this->bootstrap_methods_[i], sizeof(JVM_U2) * 2);
			if(size != sizeof(JVM_U2) * 3)
			{
				ERROR("read bootstrap_method %d of AttributeBootstrapMethods failed!", i);
				return false;
			}
			this->bootstrap_methods_[i].bootstrap_method_ref_ = swap_JVM_U2(this->bootstrap_methods_[i].bootstrap_method_ref_);
			ConstantMethodHandle *javaConstantMethodHandle_method_ref = (ConstantMethodHandle *)Constant::getConstant(this->bootstrap_methods_[i].bootstrap_method_ref_, this->constant_count_, this->constants_);
			if(javaConstantMethodHandle_method_ref != NULL)
			{
				if(javaConstantMethodHandle_method_ref->getReferenceKind() < 1 || javaConstantMethodHandle_method_ref->getReferenceKind() > 8)
				{
					ERROR("check reference_kind of bootstrap_method %d of AttributeBootstrapMethods failed!", i);
					return false;
				}
				if(javaConstantMethodHandle_method_ref->getReferenceKind() == 1 ||
						javaConstantMethodHandle_method_ref->getReferenceKind() == 2 ||
						javaConstantMethodHandle_method_ref->getReferenceKind() == 3 ||
						javaConstantMethodHandle_method_ref->getReferenceKind() == 4)
				{

				}
				else if(javaConstantMethodHandle_method_ref->getReferenceKind() == 5 ||
						javaConstantMethodHandle_method_ref->getReferenceKind() == 6 ||
						javaConstantMethodHandle_method_ref->getReferenceKind() == 7 ||
						javaConstantMethodHandle_method_ref->getReferenceKind() == 8)
				{

				}
				else if(javaConstantMethodHandle_method_ref->getReferenceKind() == 9)
				{

				}
			}

			this->bootstrap_methods_[i].num_bootstrap_arguments_ = swap_JVM_U2(this->bootstrap_methods_[i].num_bootstrap_arguments_);
			this->bootstrap_methods_[i].bootstrap_arguments_ = NULL;
			if(this->bootstrap_methods_[i].num_bootstrap_arguments_ > 0)
			{
				this->bootstrap_methods_[i].bootstrap_arguments_ = new JVM_U2[this->bootstrap_methods_[i].num_bootstrap_arguments_];
				if(this->bootstrap_methods_[i].bootstrap_arguments_ == NULL)
				{
					ERROR("allocate memory for bootstrap_arguments of bootstrap_method %d of AttributeBootstrapMethods failed!", i);
					return false;
				}
				for(int j = 0; j < this->bootstrap_methods_[i].num_bootstrap_arguments_; j ++)
				{
					size = stream.readBytes((JVM_BYTE *)&this->bootstrap_methods_[i].bootstrap_arguments_[j], sizeof(this->bootstrap_methods_[i].bootstrap_arguments_[j]));
					if(size != sizeof(this->bootstrap_methods_[i].bootstrap_arguments_[j]))
					{
						ERROR("read bootstrap_argument %d of bootstrap_method %d of AttributeBootstrapMethods failed!", j, i);
						return false;
					}
					// TODO: to parse bootstrap argument ...

				}
			}
		}
	}

	return true;
}

} /* namespace diamon_jvm */
