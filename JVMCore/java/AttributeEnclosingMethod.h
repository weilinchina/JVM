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
 **	File Name        : AttributeEnclosingMethod.h $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 1:06:18 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTEENCLOSINGMETHOD_H_
#define _JVM_ATTRIBUTEENCLOSINGMETHOD_H_


#include "GlobalDefinition.h"
#include "Attribute.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif

namespace diamon_jvm
{

class AttributeEnclosingMethod : public Attribute
{
	friend class Class;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 class_index_;
	JVM_U2 method_index_;

	/**
	 * self-defined
	 */
	std::string className_;
	std::string methodName_;
	std::string methodDescriptor_;

public:
	AttributeEnclosingMethod();
	virtual ~AttributeEnclosingMethod();

	JVM_U2 getClassIndex() const;
	JVM_U2 getMethodIndex() const;

	const std::string &getClassName() const;
	const std::string &getMethodName() const;
	const std::string &getMethodDescriptor() const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTEENCLOSINGMETHOD_H_ */
