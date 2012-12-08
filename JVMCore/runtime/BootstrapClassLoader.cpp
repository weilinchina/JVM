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
 **	File Name        : BootstrapClassLoader.cpp $
 **	Created on       : Dec 4, 2012 $
 **	Time             : 9:23:49 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "BootstrapClassLoader.h"

#include "unzip.h"


namespace diamon_jvm
{

BootstrapClassLoader::BootstrapClassLoader() : ClassLoader()
{
	// TODO Auto-generated constructor stub

}

BootstrapClassLoader::~BootstrapClassLoader()
{
	// TODO Auto-generated destructor stub
}

bool BootstrapClassLoader::launch(const char *classPaths[], const char *mainClassName)
{
	ASSERT(classPaths != NULL);
	ASSERT(mainClassName != NULL);

	int index = 0;
	while(true)
	{
		const char *classPath = classPaths[index ++];
		if(classPath == NULL)
			break;
		this->classPaths_.push_back(classPath);
	}

	const Class *clz = loadClass(mainClassName, false);
	if(clz == NULL)
	{
		ERROR("load class %s failed!", mainClassName);
		return false;
	}

	// TODO: ...



	return true;
}

} /* namespace diamon_jvm */
