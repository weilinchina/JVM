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
 **	File Name        : AttributeSourceFile.cpp $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 6:43:55 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeSourceFile.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeSourceFile::AttributeSourceFile()
{
	this->sourcefile_index_ = 0;

	this->sourceFileName_ = "";
}

AttributeSourceFile::~AttributeSourceFile()
{
	// TODO Auto-generated destructor stub
}

JVM_U2 AttributeSourceFile::getSourcefileIndex() const
{
	return sourcefile_index_;
}

const std::string &AttributeSourceFile::getSourceFileName() const
{
	return sourceFileName_;
}

bool AttributeSourceFile::marshal(Stream &stream)
{
	// read @sourcefile_index_
	size_t size = stream.readBytes((JVM_BYTE *)&this->sourcefile_index_, sizeof(this->sourcefile_index_));
	if(size != sizeof(this->sourcefile_index_))
	{
		ERROR("read sourcefile_index of AttributeSourceFile failed!");
		return false;
	}
	this->sourcefile_index_ = swap_JVM_U2(this->sourcefile_index_);
	ConstantUtf8 *javaConstantUtf8_source_file = (ConstantUtf8 *)Constant::getConstant(this->sourcefile_index_, this->constant_count_, this->constants_);
	if(javaConstantUtf8_source_file != NULL)
	{
		this->sourceFileName_.assign((char *)javaConstantUtf8_source_file->getBytes(), javaConstantUtf8_source_file->getLength());
		TRACE("source file name is: %s", this->sourceFileName_.c_str());
	}

	return true;
}

} /* namespace diamon_jvm */
