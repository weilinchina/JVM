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
 **	File Name        : AttributeExceptions.cpp $
 **	Created on       : Nov 18, 2012 $
 **	Time             : 8:24:37 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeExceptions.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantClass.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeExceptions::AttributeExceptions() : Attribute()
{
	this->number_of_exceptions_ = 0;
	this->exception_index_table_ = NULL;

	this->exceptionNames_.clear();
}

AttributeExceptions::~AttributeExceptions()
{
	if(this->exception_index_table_ != NULL)
	{
		delete[] this->exception_index_table_;
		this->exception_index_table_ = NULL;
	}
}

JVM_U2 AttributeExceptions::getNumberOfExceptions() const
{
	return number_of_exceptions_;
}

const JVM_U2 AttributeExceptions::getExceptionIndexTable(int at) const
{
	if(at < 0 || at > number_of_exceptions_ - 1)
	{
		ERROR("invalid index to locate exception index! should be between %d and %d.", 0, number_of_exceptions_ - 1);
		return -1;
	}
	if(exception_index_table_ == NULL)
	{
		ERROR("no exception index defined!");
		return -1;
	}
	return exception_index_table_[at];
}

const std::vector<std::string> &AttributeExceptions::getExceptionNames() const
{
	return exceptionNames_;
}

bool AttributeExceptions::marshal(Stream &stream)
{
	// read @number_of_exceptions_
	size_t size = stream.readBytes((JVM_BYTE *)&this->number_of_exceptions_, sizeof(this->number_of_exceptions_));
	if(size != sizeof(this->number_of_exceptions_))
	{
		ERROR("read number_of_exceptions of AttributeExceptions failed!");
		return false;
	}
	this->number_of_exceptions_ = swap_JVM_U2(this->number_of_exceptions_);

	// read @exception_index_table_
	if(this->number_of_exceptions_ > 0)
	{
		this->exception_index_table_ = new JVM_U2[this->number_of_exceptions_];
		if(this->exception_index_table_ == NULL)
		{
			ERROR("allocate memory for exception_index_table of AttributeExceptions failed!");
			return false;
		}
		for(int i = 0; i < this->number_of_exceptions_; i ++)
		{
			size = stream.readBytes((JVM_BYTE *)&this->exception_index_table_[i], sizeof(this->exception_index_table_[i]));
			if(size != sizeof(this->exception_index_table_[i]))
			{
				ERROR("read exception_index_table %d of AttributeExceptions failed!", i);
				return false;
			}
			this->exception_index_table_[i] = swap_JVM_U2(this->exception_index_table_[i]);
			ConstantClass *javaCPClass_className = (ConstantClass *)(Constant::getConstant(this->exception_index_table_[i], this->constant_count_, this->constants_));
			if(javaCPClass_className != NULL)
			{
				ConstantUtf8 *javaCPUtf8_className = (ConstantUtf8 *)(Constant::getConstant(javaCPClass_className->getNameIndex(), this->constant_count_, this->constants_));
				if(javaCPUtf8_className != NULL)
				{
					std::string className((char *)(javaCPUtf8_className->getBytes()), javaCPUtf8_className->getLength());
					TRACE("exception class name is: %s", className.c_str());
					this->exceptionNames_.push_back(className);
				}
			}
		}
	}

	return true;
}

} /* namespace diamon_jvm */
