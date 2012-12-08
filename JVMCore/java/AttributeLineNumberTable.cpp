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
 **	File Name        : AttributeLineNumberTable.cpp $
 **	Created on       : Nov 23, 2012 $
 **	Time             : 4:04:42 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeLineNumberTable.h"

#include "JVMUtility.h"


namespace diamon_jvm
{

AttributeLineNumberTable::AttributeLineNumberTable() : Attribute()
{
	this->line_number_table_length_ = 0;
	this->line_number_table_ = NULL;
}

AttributeLineNumberTable::~AttributeLineNumberTable()
{
	if(this->line_number_table_ != NULL)
	{
		delete[] this->line_number_table_;
		this->line_number_table_ = NULL;
	}
}

const LINE_NUMBER *AttributeLineNumberTable::getLineNumberTable(int at) const
{
	if(at < 0 || at > line_number_table_length_ - 1)
	{
		ERROR("invalid index to locate LINE_NUMBER! should be between %d and %d.", 0, line_number_table_length_ - 1);
		return NULL;
	}
	if(line_number_table_ == NULL)
	{
		ERROR("no LINE_NUMBER defined!");
		return NULL;
	}
	return &line_number_table_[at];
}

JVM_U2 AttributeLineNumberTable::getLineNumberTableLength() const
{
	return line_number_table_length_;
}

bool AttributeLineNumberTable::marshal(Stream &stream)
{
	// read @line_number_table_length_
	size_t size = stream.readBytes((JVM_BYTE *)&this->line_number_table_length_, sizeof(this->line_number_table_length_));
	if(size != sizeof(this->line_number_table_length_))
	{
		ERROR("read line_number_table_length of AttributeLineNumberTable failed!");
		return false;
	}
	this->line_number_table_length_ = swap_JVM_U2(this->line_number_table_length_);

	// read @line_number_table_
	if(this->line_number_table_length_ > 0)
	{
		this->line_number_table_ = new LINE_NUMBER[this->line_number_table_length_];
		if(this->line_number_table_ == NULL)
		{
			ERROR("allocate memory for line_number_table of AttributeLineNumberTable failed!");
			return false;
		}
		for(int i = 0; i < this->line_number_table_length_; i ++)
		{
			size = stream.readBytes((JVM_BYTE *)&this->line_number_table_[i], sizeof(this->line_number_table_[i]));
			if(size != sizeof(this->line_number_table_[i]))
			{
				ERROR("read line_number_table %d of AttributeLineNumberTable failed!", i);
				return false;
			}
			this->line_number_table_[i].start_pc_ = swap_JVM_U2(this->line_number_table_[i].start_pc_);
			this->line_number_table_[i].line_number_ = swap_JVM_U2(this->line_number_table_[i].line_number_);
		}
	}

	return true;
}

} /* namespace diamon_jvm */
