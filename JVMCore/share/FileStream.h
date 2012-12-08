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
 **	File Name        : FileStream.h $
 **	Created on       : Nov 14, 2012 $
 **	Time             : 5:46:05 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_FILESTREAM_H_
#define _JVM_FILESTREAM_H_


#include "GlobalDefinition.h"
#include "Stream.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class FileStream : public Stream
{
private:
	JVM_FILE_HANDLE handle_;
	std::string filePath_;
	std::string mode_;

	bool tryOpenFile();

public:
	FileStream(const char *filePath, const char *mode);
	virtual ~FileStream();
	size_t readBytes(JVM_BYTE *byteArray, size_t byteArraySize);
	size_t writeBytes(const JVM_BYTE *byteArray, size_t byteArraySize);
	bool flush();
	bool seek(JVM_LONG offset, int whence);
	void close();
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_FILESTREAM_H_ */
