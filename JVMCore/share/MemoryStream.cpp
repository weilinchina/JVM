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
 **	File Name        : MemoryStream.cpp $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 11:28:14 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "MemoryStream.h"


namespace diamon_jvm
{

MemoryStream::MemoryStream(const JVM_BYTE *memory, size_t memorySize)
{
	ASSERT(memory != NULL);
	ASSERT(memorySize != 0);

	this->memory_ = new JVM_BYTE[memorySize];
	memcpy(this->memory_, memory, memorySize);
	this->memorySize_ = memorySize;

	this->offset_ = 0;
	this->nocopy_ = false;
}

MemoryStream::MemoryStream(const JVM_BYTE *memory, size_t memorySize, bool nocopy)
{
	ASSERT(memory != NULL);
	ASSERT(memorySize != 0);

	if(nocopy)
	{
		this->memory_ = (JVM_BYTE *)memory;
		this->memorySize_ = memorySize;
	}
	else
	{
		this->memory_ = new JVM_BYTE[memorySize];
		memcpy(this->memory_, memory, memorySize);
		this->memorySize_ = memorySize;
	}
	this->offset_ = 0;
	this->nocopy_ = nocopy;
}

MemoryStream::~MemoryStream()
{
	if(this->nocopy_ == false)
	{
		if(this->memory_ != NULL)
		{
			delete[] this->memory_;
			this->memory_ = NULL;
			this->memorySize_ = 0;
		}
	}
}

size_t MemoryStream::readBytes(JVM_BYTE *byteArray, size_t byteArraySize)
{
	ASSERT(byteArray != NULL);
	ASSERT(byteArraySize != 0);

	size_t canRead = byteArraySize;
	if(canRead > this->memorySize_ - this->offset_)
		canRead = this->memorySize_ - this->offset_;

	if(canRead > 0)
	{
		memcpy(byteArray, this->memory_ + this->offset_, canRead);
		this->offset_ += canRead;
	}
	return canRead;
}

size_t MemoryStream::writeBytes(JVM_BYTE *byteArray, size_t byteArraySize)
{
	ASSERT(byteArray != NULL);
	ASSERT(byteArraySize != 0);

	size_t canWrite = byteArraySize;
	if(canWrite > this->memorySize_ - this->offset_)
		canWrite = this->memorySize_ - this->offset_;

	if(canWrite > 0)
	{
		memcpy(this->memory_ + this->offset_, byteArray, canWrite);
		this->offset_ += canWrite;
	}
	return canWrite;
}

bool MemoryStream::seek(JVM_LONG offset, int whence)
{
	ASSERT(whence == SEEK_SET || whence == SEEK_END || whence == SEEK_CUR);

	if(whence == SEEK_SET)
	{
		if(offset > this->memorySize_)
			return false;
		this->offset_ = offset;
		return true;
	}
	else if(whence == SEEK_END)
	{
		if(offset > this->memorySize_)
			return false;
		this->offset_ = this->memorySize_ - offset;
		return true;
	}
	else if(whence == SEEK_CUR)
	{
		if(this->offset_ + offset > this->memorySize_)
			return false;
		this->offset_ += offset;
		return true;
	}

	ASSERT(false);
	return false;
}


} /* namespace diamon_jvm */
