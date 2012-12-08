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
 **	File Name        : Stream.h $
 **	Created on       : Nov 14, 2012 $
 **	Time             : 5:34:03 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_STREAM_H_
#define _JVM_STREAM_H_


#include "GlobalDefinition.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Stream
{
public:
	virtual ~Stream() {}
	virtual size_t readBytes(JVM_BYTE *byteArray, size_t byteArraySize) = 0;
	virtual size_t writeBytes(JVM_BYTE *byteArray, size_t byteArraySize) = 0;
	virtual bool flush() { return 0; }
	virtual bool seek(JVM_LONG offset, int whence) = 0;
	virtual void close() {}
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_STREAM_H_ */
