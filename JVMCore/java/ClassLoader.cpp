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
 **	File Name        : ClassLoader.cpp $
 **	Created on       : Nov 27, 2012 $
 **	Time             : 10:13:58 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "ClassLoader.h"

#include "OsFile.h"
#include "Stream.h"
#include "MemoryStream.h"


namespace diamon_jvm
{

ClassLoader::ClassLoader()
{
	this->parent_ = NULL;
	this->packageMap_.clear();
	this->classMap_.clear();
	this->classPaths_.clear();
}

ClassLoader::ClassLoader(const char *classPaths[])
{
	ASSERT(classPaths != NULL);

	this->parent_ = NULL;
	this->packageMap_.clear();
	this->classMap_.clear();
	this->classPaths_.clear();
	int index = 0;
	while(true)
	{
		const char *classPath = classPaths[index ++];
		if(classPath == NULL)
			break;
		this->classPaths_.push_back(classPath);
	}
}

ClassLoader::ClassLoader(const char *classPaths[], const ClassLoader &parent)
{
	ASSERT(classPaths != NULL);

	this->parent_ = (ClassLoader *)&parent;
	this->packageMap_.clear();
	this->classMap_.clear();
	this->classPaths_.clear();
	int index = 0;
	while(true)
	{
		const char *classPath = classPaths[index ++];
		if(classPath == NULL)
			break;
		this->classPaths_.push_back(classPath);
	}
}

ClassLoader::~ClassLoader()
{
	if(this->packageMap_.empty() == false)
	{
		for(std::map<std::string, Package *>::iterator itr = this->packageMap_.begin(); itr != this->packageMap_.end(); ++ itr)
		{
			Package *package = itr->second;
			delete package;
		}
		this->packageMap_.clear();
	}

	if(this->classMap_.empty() == false)
	{
		for(std::map<std::string, Class *>::iterator itr = this->classMap_.begin(); itr != this->classMap_.end(); ++ itr)
		{
			Class *clz = itr->second;
			delete clz;
		}
		this->classMap_.clear();
	}

	this->classPaths_.clear();

	if(this->classPathHandles_.empty() == false)
	{
		for(std::map<std::string, unzFile>::iterator itr = this->classPathHandles_.begin(); itr != this->classPathHandles_.end(); ++ itr)
		{
			unzFile handle = itr->second;
			unzClose(handle);
		}
		this->classPathHandles_.clear();
	}
}

const ClassLoader *ClassLoader::getParent() const
{
	if(parent_ == NULL)
		throw std::exception(/*"no delegated ClassLoader exist!"*/);

	return parent_;
}

const std::map<std::string, Package *> &ClassLoader::getPackageMap() const
{
	return packageMap_;
}

const std::map<std::string, Class *> &ClassLoader::getClassMap() const
{
	return classMap_;
}

const Class *ClassLoader::findClass(const char *className) const
{
	ASSERT(className != NULL);

	/**
	 * parent ClassLoader is delegate ClassLoader, so it should first find class from it.
	 */
	if(this->parent_ != NULL)
	{
		TRACE("parent ClassLoader exists, try to find class from it ...");
		const Class *clz = this->parent_->findClass(className);
		if(clz != NULL)
			return clz;
	}
	/**
	 * if class not found in delegate ClassLoader, then try to find it in self class map.
	 */
	std::map<std::string, Class *>::const_iterator itr = this->classMap_.find(className);
	if(itr == this->classMap_.end())
	{
		TRACE("no class found from me!");
		return NULL;
	}
	return itr->second;
}

const Class *ClassLoader::loadClass(const char *className, bool resolve)
{
	ASSERT(className != NULL);

	const Class *clz = findClass(className);
	if(clz == NULL)
	{
		for(size_t i = 0; i < this->classPaths_.size(); i ++)
		{
			const std::string &classPath = this->classPaths_[i];
			if(OsFile_isFile(classPath.c_str()))
			{
				clz = getClassFromLibrary(className, classPath.c_str());
				if(clz != NULL)
					break;
			}
			else if(OsFile_isFolder(classPath.c_str()))
			{
				clz = getClassFromFolder(className, classPath.c_str());
				if(clz != NULL)
					break;
			}
			else
			{
				// nothing to do at this moment.
			}
		}

		if(clz != NULL)
			storeClass(clz);
	}

	if(clz != NULL && resolve)
	{
		// TODO: resolve the class ...


	}
	return clz;
}

const Class *ClassLoader::loadClass(const char *className)
{
	return loadClass(className, true);
}

const Class *ClassLoader::getClassFromLibrary(const char *className, const char *libFilePath)
{
	ASSERT(className != NULL);
	ASSERT(libFilePath != NULL);

	unzFile handle = NULL;
	std::map<std::string, unzFile>::iterator itr = this->classPathHandles_.find(libFilePath);
	if(itr == this->classPathHandles_.end())
	{
		handle = unzOpen(libFilePath);
		if(handle == NULL)
		{
			ERROR("open lib file %s failed", libFilePath);
			return false;
		}
		TRACE("lib file %s opened.", libFilePath);
		this->classPathHandles_[libFilePath] = handle;
	}
	else
	{
		handle = itr->second;
	}

	std::string strClassName(className);
	strClassName.append(".class");

	int ret = unzLocateFile(handle, strClassName.c_str(), 1);
	if(ret != UNZ_OK)
	{
		TRACE("locate class file for class %s failed!", className);
		return false;
	}
	TRACE("class file for class %s located.", className);

	unz_file_info fileInfo = {0};
	ret = unzGetCurrentFileInfo(handle, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
	if(ret != UNZ_OK)
	{
		ERROR("get file information for class %s failed!", className);
		return false;
	}
	TRACE("file information for class %s got.", className);

	ret = unzOpenCurrentFile(handle);
	if(ret != UNZ_OK)
	{
		ERROR("open file for class %s failed!", className);
		return false;
	}
	TRACE("file for class %s opened.", className);

	JVM_BYTE *buf = new JVM_BYTE[fileInfo.uncompressed_size];
	if(buf == NULL)
	{
		ERROR("allocate memory for reading file content for class %s failed!", className);
		unzCloseCurrentFile(handle);
		return false;
	}
	TRACE("memory for reading file content for class %s allocated.", className);

	ret = unzReadCurrentFile(handle, buf, fileInfo.uncompressed_size);
	if(ret <= 0)
	{
		if(ret == UNZ_ERRNO)
		{
			ERROR("I/O error while reading file content for class %s!", className);
		}
		ERROR("read file content for class %s failed!", className);
		delete[] buf;
		unzCloseCurrentFile(handle);
		return false;
	}
	TRACE("file content for class %s read.", className);

	ret = unzCloseCurrentFile(handle);
	if(ret != UNZ_OK)
	{
		ERROR("close file for class %s failed!", className);
		delete[] buf;
		return false;
	}
	TRACE("file for class %s closed.", className);

	const Class *clz = createClassFromMemory(buf, fileInfo.uncompressed_size);
	if(clz == NULL)
	{
		ERROR("create class %s from memory failed!", className);
		delete[] buf;
		return NULL;
	}
	TRACE("class %s from memory failed created.", className);

	delete[] buf;
	return clz;
}

int ClassLoader::scanDirFilter(const struct dirent *d)
{
	if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
		return 0;

	bool isClassFile = false;
	char *pEnd = strstr((char *)d->d_name, ".class");
	if(pEnd != NULL)
	{
		if(d->d_name + strlen(d->d_name) - pEnd == 6)
			isClassFile = true;
	}

	return isClassFile ? 1 : 0;
}

const Class *ClassLoader::getClassFromFolder(const char *className, const char *libFolderPath)
{
	ASSERT(className != NULL);
	ASSERT(libFolderPath != NULL);

	struct dirent **namelist = NULL;
	int count = scandir(libFolderPath, &namelist, scanDirFilter, alphasort);
	if(count <= 0)
	{
		if(count < 0)
		{
			ERROR("error happened while scanning folder %s for class %s!", libFolderPath, className);
		}
		TRACE("no entry found in folder %s.", libFolderPath);
		return NULL;
	}

	std::string classFileName(className);
	classFileName.append(".class");

	std::string classFilePath = "";
	for(int i = 0; i < count; i ++)
	{
		if(strcmp(classFileName.c_str(), namelist[i]->d_name) != 0)
		{
			TRACE("%s is not the one required for class %s.", namelist[i]->d_name, className);
			continue;
		}

		classFilePath.assign(libFolderPath);
		classFilePath.append("/");
		classFilePath.append(namelist[i]->d_name);
		if(OsFile_isFile(classFilePath.c_str()) == false)
		{
			TRACE("%s is a folder, not a file for class %s.", classFilePath.c_str(), className);
			classFilePath = "";
			continue;
		}

		break;
	}
	delete[] namelist;

	if(classFilePath.empty())
	{
		ERROR("file for class %s not found!", className);
		return NULL;
	}

	TRACE("file for class %s located, it is %s, start to read it and marshal it.", className, classFilePath.c_str());

	int fileSize = OsFile_getFileSize(classFilePath.c_str());
	if(fileSize == -1)
	{
		ERROR("get file size for %s failed!", classFilePath.c_str());
		return NULL;
	}

	JVM_BYTE *buf = new JVM_BYTE[fileSize];
	if(buf == NULL)
	{
		ERROR("allocate memory for reading file content for class %s failed!", className);
		return NULL;
	}
	TRACE("memory for reading file content for class %s allocated.", className);

	if(OsFile_readFile(classFilePath.c_str(), buf, fileSize) == false)
	{
		ERROR("reading file content for class %s failed!", className);
		delete[] buf;
		return NULL;
	}
	TRACE("file content for class %s read.", className);

	const Class *clz = createClassFromMemory(buf, fileSize);
	if(clz == NULL)
	{
		ERROR("create class %s from memory failed!", className);
		delete[] buf;
		return NULL;
	}
	TRACE("class %s from memory failed created.", className);

	delete[] buf;

	TRACE("finished reading file and parse it.");
	return clz;
}

bool ClassLoader::parseLibraryFile(const char *libFilePath)
{
	ASSERT(libFilePath != NULL);

	unzFile handle = unzOpen(libFilePath);
	if(handle == NULL)
	{
		ERROR("open lib file %s failed", libFilePath);
		return false;
	}
	TRACE("lib file %s opened.", libFilePath);

	int ret = unzGoToFirstFile(handle);
	if(ret != UNZ_OK)
	{
		ERROR("locate the 1st file failed!");
		unzClose(handle);
		return false;
	}
	TRACE("the 1st file located.");

	while(true)
	{
		unz_file_info fileInfo = {0};
		ret = unzGetCurrentFileInfo(handle, &fileInfo, NULL, 0, NULL, 0, NULL, 0);
		if(ret != UNZ_OK)
		{
			ERROR("get current file information failed!");
			unzClose(handle);
			return false;
		}
		TRACE("current file information got.");

		char *currentFileName = new char[fileInfo.size_filename + 1];
		if(currentFileName == NULL)
		{
			ERROR("allocate memory for retrieving current file name failed!");
			unzClose(handle);
			return false;
		}
		TRACE("memory for retrieving current file name allocated.");
		memset(currentFileName, 0, fileInfo.size_filename + 1);

		ret = unzGetCurrentFileInfo(handle, NULL, currentFileName, fileInfo.size_filename, NULL, 0, NULL, 0);
		if(ret != UNZ_OK)
		{
			ERROR("get current file name failed!");
			delete[] currentFileName;
			unzClose(handle);
			return false;
		}
		TRACE("current file name got, it is %s.", currentFileName);

		bool isClassFile = false;
		char *pEnd = strstr(currentFileName, ".class");
		if(pEnd != NULL)
		{
			if(currentFileName + strlen(currentFileName) - pEnd == 6)
				isClassFile = true;
		}
		delete[] currentFileName;

		if(isClassFile)
		{
			TRACE("start to read current file and parse it.");

			ret = unzOpenCurrentFile(handle);
			if(ret != UNZ_OK)
			{
				ERROR("open current file failed!");
				unzClose(handle);
				return false;
			}
			TRACE("current file opened.");

			JVM_BYTE *buf = new JVM_BYTE[fileInfo.uncompressed_size];
			if(buf == NULL)
			{
				ERROR("allocate memory for reading current file content failed!");
				unzCloseCurrentFile(handle);
				unzClose(handle);
				return false;
			}
			TRACE("memory for reading current file content allocated.");

			ret = unzReadCurrentFile(handle, buf, fileInfo.uncompressed_size);
			if(ret <= 0)
			{
				if(ret == UNZ_ERRNO)
				{
					ERROR("I/O error while reading current file content!");
				}
				ERROR("read current file content failed!");
				delete[] buf;
				unzCloseCurrentFile(handle);
				unzClose(handle);
				return false;
			}
			TRACE("current file content read.");

			ret = unzCloseCurrentFile(handle);
			if(ret != UNZ_OK)
			{
				ERROR("close current file failed!");
				delete[] buf;
				unzClose(handle);
				return false;
			}
			TRACE("current file closed.");

			const Class *clz = createClassFromMemory(buf, fileInfo.uncompressed_size);
			if(clz == NULL)
			{
				ERROR("create class from memory failed!");
				delete[] buf;
				unzClose(handle);
				return false;
			}
			TRACE("class from memory failed created.");

			delete[] buf;

			storeClass(clz);

			TRACE("finished reading current file and parse it.");
		}

		ret = unzGoToNextFile(handle);
		if(ret != UNZ_OK)
		{
			if(ret == UNZ_END_OF_LIST_OF_FILE)
			{
				TRACE("the while lib file read & parsed.");
				break;
			}
			ERROR("locate the next file failed!");
			unzClose(handle);
			return false;
		}
		TRACE("the next file located as current file.");
	}

	unzClose(handle);
	return true;
}

void ClassLoader::storeClass(const Class *clz)
{
	std::string packageName;
	size_t pos = clz->getName().find_last_of(PACKAGE_SEPARATOR);
	if(pos != std::string::npos)
		packageName = clz->getName().substr(0, pos);
	else
		packageName = DEFAULT_PACKAGE_NAME;
	TRACE("package name is: %s", packageName.c_str());

	Package *package = NULL;
	std::map<std::string, Package *>::iterator itrPackage = this->packageMap_.find(packageName);
	if(itrPackage != this->packageMap_.end())
	{
		package = itrPackage->second;
	}
	else
	{
		package = new Package();
		package->classLoader_ = this;
		this->packageMap_[packageName] = package;
	}

	std::map<std::string, Class *>::iterator itrClass = package->classMap_.find(clz->getName());
	if(itrClass == package->classMap_.end())
		package->classMap_[clz->getName()] = (Class *)clz;

	itrClass = this->classMap_.find(clz->getName());
	if(itrClass == this->classMap_.end())
		this->classMap_[clz->getName()] = (Class *)clz;
}

const Class *ClassLoader::createClassFromMemory(const JVM_BYTE *buf, int size) const
{
	Stream *stream = new MemoryStream(buf, size, true);
	if(stream == NULL)
	{
		ERROR("create stream object for class marshal failed!");
		return NULL;
	}
	TRACE("stream object for class marshal created.");

	Class *clz = new Class();
	if(clz == NULL)
	{
		ERROR("create class object for class failed!");
		delete stream;
		return NULL;
	}
	TRACE("class object for class created.");

	if(clz->marshal(*stream) == false)
	{
		ERROR("marshal class object for class failed!");
		delete clz;
		delete stream;
		return NULL;
	}
	TRACE("class object marshal for class finished.");

	delete stream;
	return clz;
}

void ClassLoader::formatClassName(char *className)
{
	ASSERT(className != NULL);

	for(int i = 0; className[i] != '\0'; i ++)
	{
		if(className[i] == '.')
			className[i] = '/';
	}
}

} /* namespace diamon_jvm */
