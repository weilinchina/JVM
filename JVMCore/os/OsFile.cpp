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
 **	File Name        : OsFile.cpp $
 **	Created on       : Dec 5, 2012 $
 **	Time             : 7:02:18 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "OsFile.h"


namespace diamon_jvm
{

bool OsFile_isFile(const char *path)
{
	if(path == NULL)
		return false;

	struct stat st = {0};
	if(stat(path, &st) == -1)
		return false;

	return (st.st_mode & S_IFREG) != 0;
}

bool OsFile_isFolder(const char *path)
{
	if(path == NULL)
		return false;

	struct stat st = {0};
	if(stat(path, &st) == -1)
		return false;

	return (st.st_mode & S_IFDIR) != 0;
}

int OsFile_getFileSize(const char *filePath)
{
	if(filePath == NULL)
		return -1;

	struct stat st = {0};
	if(stat(filePath, &st) == -1)
		return -1;

	return st.st_size;
}

JVM_FILE_HANDLE OsFile_open(const char *filePath, const char *mode)
{
	if(filePath == NULL)
		return NULL;
	if(mode == NULL)
		return NULL;

	return fopen(filePath, mode);
}

void OsFile_close(JVM_FILE_HANDLE handle)
{
	if(handle == NULL)
		return;

	fclose(handle);
}

size_t OsFile_read(JVM_FILE_HANDLE handle, JVM_BYTE *buf, size_t bufSize)
{
	if(handle == NULL)
		return -1;
	if(buf == NULL)
		return -1;
	if(bufSize == 0)
		return -1;

	size_t size = fread(buf, sizeof(JVM_BYTE), bufSize, handle);
	if(size != sizeof(JVM_BYTE) * bufSize)
	{
		return -1;
	}
	return size;
}

size_t OsFile_write(JVM_FILE_HANDLE handle, const JVM_BYTE *buf, size_t bufSize)
{
	if(handle == NULL)
		return -1;
	if(buf == NULL)
		return -1;
	if(bufSize == 0)
		return -1;

	size_t size = fwrite(buf, sizeof(JVM_BYTE), bufSize, handle);
	if(size != sizeof(JVM_BYTE) * bufSize)
	{
		return -1;
	}
	return size;
}

bool OsFile_seek(JVM_FILE_HANDLE handle, JVM_LONG offset, int whence)
{
	if(handle == NULL)
		return false;
	if(whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END)
		return false;

	return fseek(handle, offset, whence) == 0;
}

bool OsFile_flush(JVM_FILE_HANDLE handle)
{
	if(handle == NULL)
		return false;

	return fflush(handle) == 0;
}

bool OsFile_readFile(const char *filePath, JVM_BYTE *buf, size_t bufSize)
{
	if(filePath == NULL)
		return false;
	if(buf == NULL)
		return false;
	if(bufSize == 0)
		return false;

	JVM_FILE_HANDLE handle = OsFile_open(filePath, "rb");
	if(handle == NULL)
		return false;

	size_t readSize = OsFile_read(handle, buf, bufSize);
	OsFile_close(handle);

	return readSize == bufSize;
}

} /* namespace diamon_jvm */
