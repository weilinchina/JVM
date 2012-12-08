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
 **	File Name        : AttributeCode.cpp $
 **	Created on       : Nov 17, 2012 $
 **	Time             : 9:02:57 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeCode.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantClass.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeCode::AttributeCode() : Attribute()
{
	this->code_length_ = 0;
	this->code_ = NULL;
	this->max_stack_ = 0;
	this->max_locals_ = 0;
	this->exception_table_length_ = 0;
	this->exception_table_ = NULL;

	this->javaAttributeLineNumberTable_ = NULL;
	this->javaAttributeLocalVariableTable_ = NULL;
	this->javaAttributeLocalVariableTypeTable_ = NULL;
}

AttributeCode::~AttributeCode()
{
	if(this->code_ != NULL)
	{
		delete[] this->code_;
		this->code_ = NULL;
	}

	if(this->exception_table_ != NULL)
	{
		delete[] this->exception_table_;
		this->exception_table_ = NULL;
	}

	if(this->javaAttributeLineNumberTable_ != NULL)
	{
		delete this->javaAttributeLineNumberTable_;
		this->javaAttributeLineNumberTable_ = NULL;
	}

	if(this->javaAttributeLocalVariableTable_ != NULL)
	{
		delete this->javaAttributeLocalVariableTable_;
		this->javaAttributeLocalVariableTable_ = NULL;
	}

	if(this->javaAttributeLocalVariableTypeTable_ != NULL)
	{
		delete this->javaAttributeLocalVariableTypeTable_;
		this->javaAttributeLocalVariableTypeTable_ = NULL;
	}
}

const JVM_BYTE *AttributeCode::getCode() const
{
    return code_;
}

JVM_U4 AttributeCode::getCodeLength() const
{
    return code_length_;
}

const EXCEPTION_TABLE *AttributeCode::getExceptionTable(int at) const
{
	if(at < 0 || at > exception_table_length_ - 1)
	{
		ERROR("invalid index to locate EXCEPTION_TABLE! should be between %d and %d.", 0, exception_table_length_ - 1);
		return NULL;
	}
	if(exception_table_ == NULL)
	{
		ERROR("no EXCEPTION_TABLE defined!");
		return NULL;
	}
    return &exception_table_[at];
}

JVM_U2 AttributeCode::getExceptionTableLength() const
{
    return exception_table_length_;
}

JVM_U2 AttributeCode::getMaxLocals() const
{
    return max_locals_;
}

JVM_U2 AttributeCode::getMaxStack() const
{
    return max_stack_;
}

const AttributeLineNumberTable *AttributeCode::getJavaAttributeLineNumberTable() const
{
	return javaAttributeLineNumberTable_;
}

const AttributeLocalVariableTable *AttributeCode::getJavaAttributeLocalVariableTable() const
{
	return javaAttributeLocalVariableTable_;
}

const AttributeLocalVariableTypeTable *AttributeCode::getJavaAttributeLocalVariableTypeTable() const
{
	return javaAttributeLocalVariableTypeTable_;
}

bool AttributeCode::marshal(Stream &stream)
{
	// read @max_stack_
	size_t size = stream.readBytes((JVM_BYTE *)&this->max_stack_, sizeof(this->max_stack_));
	if(size != sizeof(this->max_stack_))
	{
		ERROR("read max_stack of AttributeCode failed!");
		return false;
	}
	this->max_stack_ = swap_JVM_U2(this->max_stack_);

	// read @max_locals_
	size = stream.readBytes((JVM_BYTE *)&this->max_locals_, sizeof(this->max_locals_));
	if(size != sizeof(this->max_locals_))
	{
		ERROR("read max_locals of AttributeCode failed!");
		return false;
	}
	this->max_locals_ = swap_JVM_U2(this->max_locals_);

	// read @code_length_
	size = stream.readBytes((JVM_BYTE *)&this->code_length_, sizeof(this->code_length_));
	if(size != sizeof(this->code_length_))
	{
		ERROR("read code_length of AttributeCode failed!");
		return false;
	}
	this->code_length_ = swap_JVM_U4(this->code_length_);

	// read @code_
	if(this->code_length_ > 0)
	{
		this->code_ = new JVM_BYTE[this->code_length_];
		if(this->code_ == NULL)
		{
			ERROR("allocate memory for code of AttributeCode failed!");
			return false;
		}
		size = stream.readBytes(this->code_, this->code_length_);
		if(size != this->code_length_)
		{
			ERROR("read code of AttributeCode failed!");
			return false;
		}
	}

	// read @exception_table_length_
	size = stream.readBytes((JVM_BYTE *)&this->exception_table_length_, sizeof(this->exception_table_length_));
	if(size != sizeof(this->exception_table_length_))
	{
		ERROR("read exception_table_length of AttributeCode failed!");
		return false;
	}
	this->exception_table_length_ = swap_JVM_U2(this->exception_table_length_);

	// read @exception_table_
	if(this->exception_table_length_ > 0)
	{
		this->exception_table_ = new EXCEPTION_TABLE[this->exception_table_length_];
		if(this->exception_table_ == NULL)
		{
			ERROR("allocate memory for exception_table of AttributeCode failed!");
			return false;
		}
		for(int i = 0; i < this->exception_table_length_; i ++)
		{
			size = stream.readBytes((JVM_BYTE *)&this->exception_table_[i], sizeof(JVM_U2) * 4);
			if(size != sizeof(JVM_U2) * 4)
			{
				ERROR("read exception_table %d of AttributeCode failed!", i);
				return false;
			}
			this->exception_table_[i].start_pc_ = swap_JVM_U2(this->exception_table_[i].start_pc_);
			this->exception_table_[i].end_pc_ = swap_JVM_U2(this->exception_table_[i].end_pc_);
			this->exception_table_[i].handler_pc_ = swap_JVM_U2(this->exception_table_[i].handler_pc_);
			this->exception_table_[i].catch_type_ = swap_JVM_U2(this->exception_table_[i].catch_type_);
			this->exception_table_[i].exceptionClassName_ = "";
			if(this->exception_table_[i].catch_type_ != 0)
			{
				ConstantClass *javaConstantClass = (ConstantClass *)Constant::getConstant(this->exception_table_[i].catch_type_, this->constant_count_, this->constants_);
				if(javaConstantClass != NULL)
				{
					ConstantUtf8 *javaConstantUtf8 = (ConstantUtf8 *)Constant::getConstant(javaConstantClass->getNameIndex(), this->constant_count_, this->constants_);
					if(javaConstantUtf8 != NULL)
					{
						this->exception_table_[i].exceptionClassName_.assign((char *)javaConstantUtf8->getBytes(), javaConstantUtf8->getLength());
						TRACE("exception class name %d is: %s", i, this->exception_table_[i].exceptionClassName_.c_str());
					}
				}
			}
		}
	}

	// read @attributes_count_
	JVM_U2 attributes_count = 0;
	size = stream.readBytes((JVM_BYTE*)(&attributes_count), sizeof(attributes_count));
	if(size != sizeof(attributes_count))
	{
		ERROR("read attributes_count of AttributeCode failed!");
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
				ERROR("read attribute_name_index %d of AttributeCode failed!", i);
				return false;
			}
			attribute_name_index = swap_JVM_U2(attribute_name_index);
			ConstantUtf8 *javaCPUtf8_name = (ConstantUtf8 *)Constant::getConstant(attribute_name_index, this->constant_count_, this->constants_);
			if(javaCPUtf8_name == NULL)
			{
				ERROR("locate attribute_name by attribute_name_index #%d of AttributeCode failed!", attribute_name_index);
				return false;
			}
			std::string attributeName((char *)(javaCPUtf8_name->getBytes()), javaCPUtf8_name->getLength());
			TRACE("attribute name is: %s", attributeName.c_str());

			// read @attribute_length
			JVM_U4 attribute_length = 0;
			size = stream.readBytes((JVM_BYTE*)(&attribute_length), sizeof(attribute_length));
			if(size != sizeof(attribute_length))
			{
				ERROR("read attribute_length %d of AttributeCode failed!", i);
				return false;
			}
			attribute_length = swap_JVM_U4(attribute_length);

			if(attributeName.compare("LineNumberTable") == 0)
			{
				this->javaAttributeLineNumberTable_ = new AttributeLineNumberTable();
				if(this->javaAttributeLineNumberTable_ == NULL)
				{
					ERROR("allocate memory for AttributeLineNumberTable of AttributeCode failed!");
					return false;
				}
				this->javaAttributeLineNumberTable_->attribute_name_index_ = attribute_name_index;
				this->javaAttributeLineNumberTable_->attribute_length_ = attribute_length;
				this->javaAttributeLineNumberTable_->attributeName_ = attributeName;
				this->javaAttributeLineNumberTable_->constant_count_ = this->constant_count_;
				this->javaAttributeLineNumberTable_->constants_ = this->constants_;
				if(this->javaAttributeLineNumberTable_->marshal(stream) == false)
				{
					ERROR("marshal AttributeLineNumberTable of AttributeCode failed!");
					return false;
				}
			}
			else if(attributeName.compare("LocalVariableTable") == 0)
			{
				this->javaAttributeLocalVariableTable_ = new AttributeLocalVariableTable();
				if(this->javaAttributeLocalVariableTable_ == NULL)
				{
					ERROR("allocate memory for AttributeLocalVariableTable of AttributeCode failed!");
					return false;
				}
				this->javaAttributeLocalVariableTable_->attribute_name_index_ = attribute_name_index;
				this->javaAttributeLocalVariableTable_->attribute_length_ = attribute_length;
				this->javaAttributeLocalVariableTable_->attributeName_ = attributeName;
				this->javaAttributeLocalVariableTable_->constant_count_ = this->constant_count_;
				this->javaAttributeLocalVariableTable_->constants_ = this->constants_;
				if(this->javaAttributeLocalVariableTable_->marshal(stream) == false)
				{
					ERROR("marshal AttributeLocalVariableTable of AttributeCode failed!");
					return false;
				}
			}
			else if(attributeName.compare("LocalVariableTypeTable") == 0)
			{
				this->javaAttributeLocalVariableTypeTable_ = new AttributeLocalVariableTypeTable();
				if(this->javaAttributeLocalVariableTypeTable_ == NULL)
				{
					ERROR("allocate memory for AttributeLocalVariableTypeTable of AttributeCode failed!");
					return false;
				}
				this->javaAttributeLocalVariableTypeTable_->attribute_name_index_ = attribute_name_index;
				this->javaAttributeLocalVariableTypeTable_->attribute_length_ = attribute_length;
				this->javaAttributeLocalVariableTypeTable_->attributeName_ = attributeName;
				this->javaAttributeLocalVariableTypeTable_->constant_count_ = this->constant_count_;
				this->javaAttributeLocalVariableTypeTable_->constants_ = this->constants_;
				if(this->javaAttributeLocalVariableTypeTable_->marshal(stream) == false)
				{
					ERROR("marshal AttributeLocalVariableTypeTable of AttributeCode failed!");
					return false;
				}
			}
			else
			{
				if(Attribute::marshal(stream, attribute_name_index, attribute_length) == false)
				{
					ERROR("marshal attribute %d of AttributeCode failed!", i);
					return false;
				}
			}
		}
	}

	return true;
}

} /* namespace diamon_jvm */
