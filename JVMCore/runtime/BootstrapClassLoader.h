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
 **	File Name        : BootstrapClassLoader.h $
 **	Created on       : Dec 4, 2012 $
 **	Time             : 9:23:49 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_BOOTSTRAPCLASSLOADER_H_
#define _JVM_BOOTSTRAPCLASSLOADER_H_


#include "GlobalDefinition.h"
#include "ClassLoader.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class BootstrapClassLoader : public ClassLoader
{
public:
	BootstrapClassLoader();
	virtual ~BootstrapClassLoader();

	bool launch(const char *classPaths[], const char *mainClassName);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_BOOTSTRAPCLASSLOADER_H_ */
