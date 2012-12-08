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
 **	File Name        : Method.h $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 5:53:48 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_METHOD_H_
#define _JVM_METHOD_H_


#include "GlobalDefinition.h"
#include "Marshal.h"
#include "Constant.h"
#include "AttributeCode.h"
#include "AttributeExceptions.h"
#include "AttributeSignature.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Method : public Marshal
{
	friend class Class;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 access_flags_;
	JVM_U2 name_index_;
	JVM_U2 descriptor_index_;

	/**
	 * self-defined
	 */
	std::string methodName_;
	std::string methodDescriptor_;
	AttributeCode *attributeCode_;
	AttributeExceptions *attributeExceptions_;
	AttributeSignature *attributeSignature_;
	bool deprecated_;

	/**
	 * for internal usage only.
	 */
	JVM_U2 constant_count_;
	Constant **constants_;

public:
	Method();
	virtual ~Method();

    JVM_U2 getAccessFlags() const;
    JVM_U2 getNameIndex() const;
    JVM_U2 getDescriptorIndex() const;

    const std::string &getMethodName() const;
    const std::string &getMethodDescriptor() const;
    const AttributeCode *getAttributeCode() const;
    const AttributeExceptions *getAttributeExceptions() const;
    const AttributeSignature *getAttributeSignature() const;
    bool isDeprecated();

    bool marshal(Stream &stream);

	INLINE
    static const Method *getMethod(JVM_U2 at, JVM_U2 methods_count, Method **methods);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_METHOD_H_ */
