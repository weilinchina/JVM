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
 **	File Name        : FileStream.cpp $
 **	Created on       : Nov 14, 2012 $
 **	Time             : 5:46:05 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "FileStream.h"

#include "OsFile.h"


namespace diamon_jvm
{

FileStream::FileStream(const char *filePath, const char *mode)
{
	ASSERT(filePath != NULL);
	ASSERT(mode != NULL);

	this->handle_ = NULL;
	this->filePath_ = filePath;
	this->mode_ = mode;
}

FileStream::~FileStream()
{
	close();
}

bool FileStream::tryOpenFile()
{
	if(this->handle_ == NULL)
	{
		this->handle_ = OsFile_open(this->filePath_.c_str(), this->mode_.c_str());
		if(this->handle_ == NULL)
		{
			return false;
		}
	}
	return true;
}

size_t FileStream::readBytes(JVM_BYTE *byteArray, size_t byteArraySize)
{
	ASSERT(byteArray != NULL);
	ASSERT(byteArraySize != 0);

	if(tryOpenFile() == false)
	{
		return -1;
	}

	size_t size = OsFile_read(this->handle_, byteArray, byteArraySize);
	if(size != sizeof(JVM_BYTE) * byteArraySize)
	{
		return -1;
	}
	return size;
}

size_t FileStream::writeBytes(const JVM_BYTE *byteArray, size_t byteArraySize)
{
	ASSERT(byteArray != NULL);
	ASSERT(byteArraySize != 0);

	if(tryOpenFile() == false)
	{
		return -1;
	}

	size_t size = OsFile_write(this->handle_, byteArray, byteArraySize);
	if(size != sizeof(JVM_BYTE) * byteArraySize)
	{
		return -1;
	}
	return size;
}

bool FileStream::flush()
{
	return OsFile_flush(this->handle_);
}

bool FileStream::seek(JVM_LONG offset, int whence)
{
	return OsFile_seek(this->handle_, offset, whence);
}

void FileStream::close()
{
	OsFile_close(this->handle_);
}

} /* namespace diamon_jvm */
