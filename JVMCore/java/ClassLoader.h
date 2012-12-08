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
 **	File Name        : ClassLoader.h $
 **	Created on       : Nov 27, 2012 $
 **	Time             : 10:13:58 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_CLASSLOADER_H_
#define _JVM_CLASSLOADER_H_


#include "GlobalDefinition.h"
#include "Package.h"
#include "Class.h"

#include "unzip.h"

#include <map>
#include <string>
#include <vector>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class ClassLoader
{
protected:
	ClassLoader *parent_;
	std::map<std::string, Package *> packageMap_;
	std::map<std::string, Class *> classMap_;

	std::vector<std::string> classPaths_;
	std::map<std::string, unzFile> classPathHandles_;

private:
	bool parseLibraryFile(const char *libFilePath);
	const Class *getClassFromLibrary(const char *className, const char *libFilePath);
	const Class *getClassFromFolder(const char *className, const char *libFolderPath);
	void storeClass(const Class *clz);
	static int scanDirFilter(const struct dirent *d);
	const Class *createClassFromMemory(const JVM_BYTE *buf, int size) const;

protected:
	const Class *loadClass(const char *className, bool resolve);

public:
	ClassLoader();
	/**
	 * @classPaths is an array of "const char *".
	 * The array size should be number of class path plus 1.
	 * The last element should be NULL, specify the end of array.
	 */
	ClassLoader(const char *classPaths[]);
	ClassLoader(const char *classPaths[], const ClassLoader &parent);
	virtual ~ClassLoader();

	const ClassLoader *getParent() const;
	const std::map<std::string, Package *> &getPackageMap() const;
	const std::map<std::string, Class *> &getClassMap() const;

	const Class *findClass(const char *className) const;
	const Class *loadClass(const char *className);

	/**
	 * update '.' to '/'
	 */
	static void formatClassName(char *className);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_CLASSLOADER_H_ */
