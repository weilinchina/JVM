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
 **	File Name        : AttributeLocalVariableTable.cpp $
 **	Created on       : Nov 23, 2012 $
 **	Time             : 4:22:04 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeLocalVariableTable.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeLocalVariableTable::AttributeLocalVariableTable() : Attribute()
{
	this->local_variable_table_length_ = 0;
	this->local_variable_table_ = NULL;
}

AttributeLocalVariableTable::~AttributeLocalVariableTable()
{
	if(this->local_variable_table_ != NULL)
	{
		delete[] this->local_variable_table_;
		this->local_variable_table_ = NULL;
	}
}

const LOCAL_VARIABLE *AttributeLocalVariableTable::getLocalVariableTable(int at) const
{
	if(at < 0 || at > local_variable_table_length_ - 1)
	{
		ERROR("invalid index to locate LOCAL_VARIABLE! should be between %d and %d.", 0, local_variable_table_length_ - 1);
		return NULL;
	}
	if(local_variable_table_ == NULL)
	{
		ERROR("no LOCAL_VARIABLE defined!");
		return NULL;
	}
	return &local_variable_table_[at];
}

JVM_U2 AttributeLocalVariableTable::getLocalVariableTableLength() const
{
	return local_variable_table_length_;
}

bool AttributeLocalVariableTable::marshal(Stream & stream)
{
	// read @local_variable_table_length_
	size_t size = stream.readBytes((JVM_BYTE*)(&this->local_variable_table_length_), sizeof(this->local_variable_table_length_));
	if(size != sizeof(this->local_variable_table_length_))
	{
		ERROR("read local_variable_table_length of AttributeLocalVariableTable failed!");
		return false;
	}
	this->local_variable_table_length_ = swap_JVM_U2(this->local_variable_table_length_);

	// read @local_variable_table_
	if(this->local_variable_table_length_ > 0)
	{
		this->local_variable_table_ = new LOCAL_VARIABLE[this->local_variable_table_length_];
		if(this->local_variable_table_ == NULL)
		{
			ERROR("allocate memory for local_variable_table of AttributeLocalVariableTable failed!");
			return false;
		}
		for(int i = 0; i < this->local_variable_table_length_; i++)
		{
			size = stream.readBytes((JVM_BYTE *)&this->local_variable_table_[i], sizeof(JVM_U2) * 5);
			if(size != sizeof(JVM_U2) * 5)
			{
				ERROR("read local_variable_table %d of AttributeLocalVariableTable failed!", i);
				return false;
			}
			this->local_variable_table_[i].start_pc_ = swap_JVM_U2(this->local_variable_table_[i].start_pc_);
			this->local_variable_table_[i].length_ = swap_JVM_U2(this->local_variable_table_[i].length_);
			this->local_variable_table_[i].name_index_ = swap_JVM_U2(this->local_variable_table_[i].name_index_);
			this->local_variable_table_[i].descriptor_index_ = swap_JVM_U2(this->local_variable_table_[i].descriptor_index_);
			this->local_variable_table_[i].index_ = swap_JVM_U2(this->local_variable_table_[i].index_);
			ConstantUtf8 *javaConstantUtf8_name = (ConstantUtf8 *)Constant::getConstant(this->local_variable_table_[i].name_index_, this->constant_count_, this->constants_);
			if(javaConstantUtf8_name != NULL)
			{
				this->local_variable_table_[i].name_.assign((char *)javaConstantUtf8_name->getBytes(), javaConstantUtf8_name->getLength());
				TRACE("local variable table name is: %s", this->local_variable_table_[i].name_.c_str());
			}
			ConstantUtf8 *javaConstantUtf8_descriptor = (ConstantUtf8 *)Constant::getConstant(this->local_variable_table_[i].descriptor_index_, this->constant_count_, this->constants_);
			if(javaConstantUtf8_descriptor != NULL)
			{
				this->local_variable_table_[i].descriptor_.assign((char *)javaConstantUtf8_descriptor->getBytes(), javaConstantUtf8_descriptor->getLength());
				TRACE("local variable table descriptor is: %s", this->local_variable_table_[i].descriptor_.c_str());
			}
		}
	}

	return true;
}

} /* namespace diamon_jvm */
