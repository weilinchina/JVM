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
 **	File Name        : Package.cpp $
 **	Created on       : Nov 28, 2012 $
 **	Time             : 9:20:41 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "Package.h"

#include <exception>


namespace diamon_jvm
{

Package::Package()
{
	this->parentPackage_ = NULL;
	this->childPackages_.clear();
	this->classMap_.clear();
	this->classLoader_ = NULL;
}

Package::~Package()
{
	// TODO Auto-generated destructor stub
}

const Package *Package::getParentPackage() const
{
	return parentPackage_;
}

const std::vector<Package *> &Package::getChildPackages() const
{
	return childPackages_;
}

const std::map<std::string, Class *> &Package::getClassMap() const
{
	return classMap_;
}

const ClassLoader &Package::getClassLoader() const
{
	ASSERT(this->classLoader_ != NULL);

	return *classLoader_;
}

const Class *Package::findClass(const char *className) const
{
	std::map<std::string, Class *>::const_iterator itr = this->classMap_.find(className);
	if(itr == this->classMap_.end())
	{
		TRACE("no class found from me!");
		return NULL;
	}
	return itr->second;
}

} /* namespace diamon_jvm */
