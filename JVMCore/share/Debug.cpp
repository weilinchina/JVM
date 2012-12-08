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
 **	File Name        : Common.cpp $
 **	Created on       : Nov 26, 2012 $
 **	Time             : 5:09:59 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "Debug.h"

#include <memory.h>
#include <exception>
#include <iostream>


namespace diamon_jvm
{

void assert(bool expr)
{
#ifdef _DEBUG
	if(expr == false)
		throw std::exception();
#endif
}

std::string vformat(const char *format, va_list args)
{
	size_t size = 1024;
	char *buffer = new char[size + 1];
	memset(buffer, 0, size + 1);
	while(true)
	{
		int n = vsnprintf(buffer, size, format, args);
		if((n > -1) && (static_cast<size_t>(n) < size))
		{
			std::string s(buffer);
			delete[] buffer;
			return s;
		}
		size = (n > -1) ? n + 1 : size * 2;
		delete[] buffer;
		buffer = new char[size + 1];
		memset(buffer, 0, size + 1);
	}
	return "";
}

void trace(const char *format, ...)
{
#ifdef _DEBUG
	va_list argptr;
	va_start(argptr, format);
	std::string s = vformat(format, argptr);
	va_end(argptr);
	std::cout << "[" << __TIME__ << "] : TRACE : " << s << std::endl;
#endif
}

void error(const char *format, ...)
{
	va_list argptr;
	va_start(argptr, format);
	std::string s = vformat(format, argptr);
	va_end(argptr);
	std::cout << "[" << __TIME__ << "] : ERROR : " << s << std::endl;
}

} /* namespace diamon_jvm */
