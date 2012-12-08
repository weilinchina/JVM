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
 **	File Name        : Package.h $
 **	Created on       : Nov 28, 2012 $
 **	Time             : 9:20:41 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_PACKAGE_H_
#define _JVM_PACKAGE_H_


#include "GlobalDefinition.h"
#include "Class.h"

#include <map>
#include <string>
#include <vector>


#define PACKAGE_SEPARATOR        '/'
#define DEFAULT_PACKAGE_NAME     "<default_package>"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class ClassLoader;
class Package
{
	friend class ClassLoader;

protected:
	Package *parentPackage_;
	std::vector<Package *> childPackages_;
	/**
	 * these objects should be deleted by ClassLoader.
	 */
	std::map<std::string, Class *> classMap_;
	ClassLoader *classLoader_;

public:
	Package();
	virtual ~Package();

	const Package *getParentPackage() const;
	const std::vector<Package*> &getChildPackages() const;
	const std::map<std::string, Class*> &getClassMap() const;
	const ClassLoader &getClassLoader() const;

	const Class *findClass(const char *className) const;
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_PACKAGE_H_ */
