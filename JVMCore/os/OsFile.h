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
 **	File Name        : OsFile.h $
 **	Created on       : Dec 5, 2012 $
 **	Time             : 7:02:17 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_OSFILE_H_
#define _JVM_OSFILE_H_


#include "GlobalDefinition.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

INLINE
bool OsFile_isFile(const char *path);

INLINE
bool OsFile_isFolder(const char *path);

INLINE
int OsFile_getFileSize(const char *filePath);

INLINE
JVM_FILE_HANDLE OsFile_open(const char *filePath, const char *mode);

INLINE
void OsFile_close(JVM_FILE_HANDLE handle);

INLINE
size_t OsFile_read(JVM_FILE_HANDLE handle, JVM_BYTE *buf, size_t bufSize);

INLINE
size_t OsFile_write(JVM_FILE_HANDLE handle, const JVM_BYTE *buf, size_t bufSize);

INLINE
bool OsFile_seek(JVM_FILE_HANDLE handle, JVM_LONG offset, int whence);

INLINE
bool OsFile_flush(JVM_FILE_HANDLE handle);

INLINE
bool OsFile_readFile(const char *filePath, JVM_BYTE *buf, size_t bufSize);

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_OSFILE_H_ */
