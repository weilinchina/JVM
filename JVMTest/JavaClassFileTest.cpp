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
 ** Project          : JVMTest $
 **	File Name        : JavaClassFileTest.cpp $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 5:32:35 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#include "Class.h"
#include "Stream.h"
#include "FileStream.h"
#include "MemoryStream.h"
#include "BootstrapClassLoader.h"


using namespace diamon_jvm;


int main(int argc, char *argv[])
{
	const char **classPaths = new const char *[3];
	classPaths[0] = "/home/liwei/works/test/tools.jar";
	classPaths[1] = "/home/liwei/works/test";
	classPaths[2] = NULL;

	BootstrapClassLoader *bscl = new BootstrapClassLoader();
	bscl->launch(classPaths, "ServiceCalculator");
	bscl->launch(classPaths, "com/sun/xml/internal/xsom/SCD");
	bscl->launch(classPaths, "com/sun/codemodel/internal/ClassType");

	delete bscl;
	delete[] classPaths;

	return 0;
}


/*
int main(int argc, char *argv[])
{
	const char *classFilePath = "/home/liwei/works/test/TEST.class";

	Stream *stream = new FileStream(classFilePath, "rb");

	struct stat buf = {0};
	if(stat(classFilePath, &buf) != 0)
		return -1;
	FILE *fp = fopen(classFilePath, "rb");
	if(fp == NULL)
		return -1;
	JVM_BYTE *fileBuf = new JVM_BYTE[buf.st_size];
	int readSize = fread(fileBuf, 1, buf.st_size, fp);
	if(readSize != buf.st_size)
	{
		delete[] fileBuf;
		return -1;
	}
	Stream *stream = new MemoryStream(fileBuf, buf.st_size);
	delete[] fileBuf;

	Class *javaClass = new Class();
	bool ret = javaClass->marshal(*stream);

	delete javaClass;
	delete stream;

	return ret;
}
*/
