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
 **	File Name        : Runnable.h $
 **	Created on       : Dec 6, 2012 $
 **	Time             : 3:17:21 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_RUNNABLE_H_
#define _JVM_RUNNABLE_H_


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Runnable
{
protected:
	virtual void run() = 0;

public:
	virtual ~Runnable() {}
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_RUNNABLE_H_ */
