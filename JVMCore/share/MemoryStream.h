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
 **	File Name        : MemoryStream.h $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 11:28:14 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_MEMORYSTREAM_H_
#define _JVM_MEMORYSTREAM_H_


#include "Stream.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class MemoryStream : public Stream
{
private:
	JVM_BYTE *memory_;
	size_t memorySize_;
	size_t offset_;
	bool nocopy_;

public:
	MemoryStream(const JVM_BYTE *memory, size_t memorySize);
	MemoryStream(const JVM_BYTE *memory, size_t memorySize, bool nocopy);
	virtual ~MemoryStream();

	size_t readBytes(JVM_BYTE *byteArray, size_t byteArraySize);
	size_t writeBytes(JVM_BYTE *byteArray, size_t byteArraySize);
	bool seek(JVM_LONG offset, int whence);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_MEMORYSTREAM_H_ */
