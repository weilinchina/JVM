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
 **	File Name        : AttributeLocalVariableTypeTable.cpp $
 **	Created on       : Nov 23, 2012 $
 **	Time             : 5:21:41 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeLocalVariableTypeTable.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeLocalVariableTypeTable::AttributeLocalVariableTypeTable() : Attribute()
{
	this->local_variable_type_table_length_ = 0;
	this->local_variable_type_table_ = NULL;
}

AttributeLocalVariableTypeTable::~AttributeLocalVariableTypeTable()
{
	if(this->local_variable_type_table_ != NULL)
	{
		delete[] this->local_variable_type_table_;
		this->local_variable_type_table_ = NULL;
	}
}

const LOCAL_VARIABLE_TYPE *AttributeLocalVariableTypeTable::getLocalVariableTypeTable(int at) const
{
	if(at < 0 || at > local_variable_type_table_length_ - 1)
	{
		ERROR("invalid index to locate LOCAL_VARIABLE_TYPE! should be between %d and %d.", 0, local_variable_type_table_length_ - 1);
		return NULL;
	}
	if(local_variable_type_table_ == NULL)
	{
		ERROR("no LOCAL_VARIABLE_TYPE defined!");
		return NULL;
	}
	return &local_variable_type_table_[at];
}

JVM_U2 AttributeLocalVariableTypeTable::getLocalVariableTypeTableLength() const
{
	return local_variable_type_table_length_;
}

bool AttributeLocalVariableTypeTable::marshal(Stream & stream)
{
	// read @local_variable_table_length_
	size_t size = stream.readBytes((JVM_BYTE*)(&this->local_variable_type_table_length_), sizeof(this->local_variable_type_table_length_));
	if(size != sizeof(this->local_variable_type_table_length_))
	{
		ERROR("read local_variable_type_table_length of AttributeLocalVariableTypeTable failed!");
		return false;
	}
	this->local_variable_type_table_length_ = swap_JVM_U2(this->local_variable_type_table_length_);

	// read @local_variable_table_
	if(this->local_variable_type_table_length_ > 0)
	{
		this->local_variable_type_table_ = new LOCAL_VARIABLE_TYPE[this->local_variable_type_table_length_];
		if(this->local_variable_type_table_ == NULL)
		{
			ERROR("allocate memory for local_variable_type_table of AttributeLocalVariableTypeTable failed!");
			return false;
		}
		for(int i = 0; i < this->local_variable_type_table_length_; i++)
		{
			size = stream.readBytes((JVM_BYTE *)&this->local_variable_type_table_[i], sizeof(JVM_U2) * 5);
			if(size != sizeof(JVM_U2) * 5)
			{
				ERROR("read local_variable_type_table %d of AttributeLocalVariableTypeTable failed!", i);
				return false;
			}
			this->local_variable_type_table_[i].start_pc_ = swap_JVM_U2(this->local_variable_type_table_[i].start_pc_);
			this->local_variable_type_table_[i].length_ = swap_JVM_U2(this->local_variable_type_table_[i].length_);
			this->local_variable_type_table_[i].name_index_ = swap_JVM_U2(this->local_variable_type_table_[i].name_index_);
			this->local_variable_type_table_[i].signature_index_ = swap_JVM_U2(this->local_variable_type_table_[i].signature_index_);
			this->local_variable_type_table_[i].index_ = swap_JVM_U2(this->local_variable_type_table_[i].index_);
			ConstantUtf8 *javaConstantUtf8_name = (ConstantUtf8 *)Constant::getConstant(this->local_variable_type_table_[i].name_index_, this->constant_count_, this->constants_);
			if(javaConstantUtf8_name != NULL)
			{
				this->local_variable_type_table_[i].name_.assign((char *)javaConstantUtf8_name->getBytes(), javaConstantUtf8_name->getLength());
				TRACE("local variable type table name is: %s", this->local_variable_type_table_[i].name_.c_str());
			}
			ConstantUtf8 *javaConstantUtf8_signature = (ConstantUtf8 *)Constant::getConstant(this->local_variable_type_table_[i].signature_index_, this->constant_count_, this->constants_);
			if(javaConstantUtf8_signature != NULL)
			{
				this->local_variable_type_table_[i].signature_.assign((char *)javaConstantUtf8_signature->getBytes(), javaConstantUtf8_signature->getLength());
				TRACE("local variable type table signature is: %s", this->local_variable_type_table_[i].signature_.c_str());
			}
		}
	}

	return true;
}

} /* namespace diamon_jvm */
