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
 **	File Name        : Class.h $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 5:51:21 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_CLASS_H_
#define _JVM_CLASS_H_


#include "GlobalDefinition.h"
#include "Marshal.h"
#include "Field.h"
#include "Method.h"
#include "Constant.h"
#include "AttributeInnerClasses.h"
#include "AttributeEnclosingMethod.h"
#include "AttributeSignature.h"
#include "AttributeSourceFile.h"
#include "AttributeSourceDebugExtension.h"
#include "AttributeBootstrapMethods.h"

#include <string>
#include <vector>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Package;
class ClassLoader;
class Class : public Marshal
{
	friend class Package;
	friend class ClassLoader;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U4 magic_;
	JVM_U2 minor_version_;
	JVM_U2 major_version_;
	JVM_U2 constant_count_;
	Constant **constants_;
	JVM_U2 access_flags_;
	JVM_U2 this_class_;
	JVM_U2 super_class_;
	JVM_U2 interfaces_count_;
	JVM_U2 *interfaces_;
	JVM_U2 fields_count_;
	Field **fields_;
	JVM_U2 methods_count_;
	Method **methods_;

	/**
	 * self-defined
	 */
	JVM_DOUBLE version_;
	std::string name_;
	std::string pureName_;
	std::string superClassName_;
	std::vector<std::string> interfaceNames_;
	AttributeInnerClasses *attributeInnerClasses_;
	AttributeEnclosingMethod *attributeEnclosingMethod_;
	AttributeSignature *attributeSignature_;
	AttributeSourceFile *attributeSourceFile_;
	AttributeSourceDebugExtension *attributeSourceDebugExtension_;
	bool deprecated_;
	AttributeBootstrapMethods *attributeBootstrapMethods_;

	/**
	 * external relationships
	 */
	Package *package_;
	ClassLoader *classLoader_;

public:
	Class();
	virtual ~Class();

    JVM_U4 getMagic() const;
    JVM_U2 getMinorVersion() const;
    JVM_U2 getMajorVersion() const;
    JVM_U2 getConstantCount() const;
    const Constant *getConstant(JVM_U2 at) const;
    JVM_U2 getAccessFlags() const;
    JVM_U2 getThisClass() const;
    JVM_U2 getSuperClass() const;
    JVM_U2 getInterfacesCount() const;
    JVM_U2 getInterface(JVM_U2 at) const;
    JVM_U2 getFieldsCount() const;
    const Field *getField(JVM_U2 at) const;
    JVM_U2 getMethodsCount() const;
    const Method *getMethod(JVM_U2 at) const;

    JVM_DOUBLE getVersion() const;
    const std::string &getName() const;
    const std::string &getPureName() const;
    const std::string &getSuperClassName() const;
    const std::vector<std::string> &getInterfaceNames() const;
    const AttributeInnerClasses *getAttributeInnerClasses() const;
    const AttributeEnclosingMethod *getAttributeEnclosingMethod() const;
    const AttributeSignature *getAttributeSignature() const;
    const AttributeSourceFile *getAttributeSourceFile() const;
    const AttributeSourceDebugExtension *getAttributeSourceDebugExtension() const;
    bool isDeprecated();
    const AttributeBootstrapMethods *getAttributeBootstrapMethods() const;

    const Package &getPackage() const;
    const ClassLoader &getClassLoader() const;

    bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_CLASS_H_ */
