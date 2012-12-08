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
 **	File Name        : Marshal.h $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 11:22:48 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_MARSHAL_H_
#define _JVM_MARSHAL_H_


#include "GlobalDefinition.h"
#include "Stream.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Marshal
{
public:
	virtual ~Marshal() {}
	virtual bool marshal(Stream &stream) = 0;
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_MARSHAL_H_ */
