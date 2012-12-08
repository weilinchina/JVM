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
 **	File Name        : AttributeInnerClasses.cpp $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 10:45:21 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeInnerClasses.h"

#include "JVMUtility.h"
#include "AccessFlags.h"
#include "Constant.h"
#include "ConstantClass.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeInnerClasses::AttributeInnerClasses() : Attribute()
{
	this->number_of_classes_ = 0;
	this->classes_ = NULL;
}

AttributeInnerClasses::~AttributeInnerClasses()
{
	if(this->classes_ != NULL)
	{
		delete[] this->classes_;
		this->classes_ = NULL;
	}
}

JVM_U2 AttributeInnerClasses::getNumberOfClasses() const
{
	return number_of_classes_;
}

const INNER_CLASS *AttributeInnerClasses::getClass(int at) const
{
	if(at < 0 || at > number_of_classes_ - 1)
	{
		ERROR("invalid index to locate inner class! should be between %d and %d.", 0, number_of_classes_ - 1);
		return NULL;
	}
	if(classes_ == NULL)
	{
		ERROR("no inner class defined!");
		return NULL;
	}
	return &classes_[at];
}

bool AttributeInnerClasses::marshal(Stream & stream)
{
	// read @number_of_classes_
	size_t size = stream.readBytes((JVM_BYTE*)(&this->number_of_classes_), sizeof(this->number_of_classes_));
	if(size != sizeof(this->number_of_classes_))
	{
		ERROR("read number_of_classes of AttributeInnerClasses failed!");
		return false;
	}
	this->number_of_classes_ = swap_JVM_U2(this->number_of_classes_);

	// read @classes_
	if(this->number_of_classes_ > 0)
	{
		this->classes_ = new INNER_CLASS[this->number_of_classes_];
		if(this->classes_ == NULL)
		{
			ERROR("allocate memory for classes of AttributeInnerClasses failed!");
			return false;
		}
		for(int i = 0; i < this->number_of_classes_; i++)
		{
			size = stream.readBytes((JVM_BYTE*)(&this->classes_[i]), sizeof(JVM_U2) * 4);
			if(size != sizeof(JVM_U2) * 4)
			{
				ERROR("read class %d of AttributeInnerClasses failed!", i);
				return false;
			}
			this->classes_[i].inner_class_info_index_ = swap_JVM_U2(this->classes_[i].inner_class_info_index_);
			this->classes_[i].outer_class_info_index_ = swap_JVM_U2(this->classes_[i].outer_class_info_index_);
			this->classes_[i].inner_name_index_ = swap_JVM_U2(this->classes_[i].inner_name_index_);
			this->classes_[i].inner_class_access_flags_ = swap_JVM_U2(this->classes_[i].inner_class_access_flags_);

			this->classes_[i].innerClassName_ = "";
			ConstantClass *javaConstantClass_inner_class = (ConstantClass *)Constant::getConstant(this->classes_[i].inner_class_info_index_, this->constant_count_, this->constants_);
			if(javaConstantClass_inner_class != NULL)
			{
				ConstantUtf8 *javaConstantUtf8_inner_class = (ConstantUtf8 *)Constant::getConstant(javaConstantClass_inner_class->getNameIndex(), this->constant_count_, this->constants_);
				if(javaConstantUtf8_inner_class != NULL)
				{
					this->classes_[i].innerClassName_.assign((char *)javaConstantUtf8_inner_class->getBytes(), javaConstantUtf8_inner_class->getLength());
					TRACE("inner class %d name is: %s", i, this->classes_[i].innerClassName_.c_str());
				}
			}

			this->classes_[i].outerClassName_ = "";
			if(this->classes_[i].outer_class_info_index_ != 0)
			{
				ConstantClass *javaConstantClass_outer_class = (ConstantClass *)Constant::getConstant(this->classes_[i].outer_class_info_index_, this->constant_count_, this->constants_);
				if(javaConstantClass_outer_class != NULL)
				{
					ConstantUtf8 *javaConstantUtf8_outer_class = (ConstantUtf8 *)Constant::getConstant(javaConstantClass_outer_class->getNameIndex(), this->constant_count_, this->constants_);
					if(javaConstantUtf8_outer_class != NULL)
					{
						this->classes_[i].outerClassName_.assign((char *)javaConstantUtf8_outer_class->getBytes(), javaConstantUtf8_outer_class->getLength());
						TRACE("outer class %d name is: %s", i, this->classes_[i].outerClassName_.c_str());
					}
				}
			}

			this->classes_[i].innerName_ = "";
			if(this->classes_[i].inner_name_index_ != 0)
			{
				ConstantUtf8 *javaConstantUtf8_inner_name = (ConstantUtf8 *)Constant::getConstant(this->classes_[i].inner_name_index_, this->constant_count_, this->constants_);
				if(javaConstantUtf8_inner_name != NULL)
				{
					this->classes_[i].innerName_.assign((char *)javaConstantUtf8_inner_name->getBytes(), javaConstantUtf8_inner_name->getLength());
					TRACE("inner name %d is: %s", i, this->classes_[i].innerName_.c_str());
				}
			}

			/*
			if(this->classes_[i].inner_class_access_flags_ & (~INNER_CLASS_ACC_FLAGS))
			{
				ERROR("check inner_class_access_flags_ %d of classes of AttributeInnerClasses failed!", i);
				return false;
			}
			*/
		}
	}

	return true;
}

} /* namespace diamon_jvm */
