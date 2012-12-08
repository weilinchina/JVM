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
 **	File Name        : Attribute.h $
 **	Created on       : Nov 17, 2012 $
 **	Time             : 8:57:52 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTE_H_
#define _JVM_ATTRIBUTE_H_


#include "GlobalDefinition.h"
#include "Marshal.h"
#include "Constant.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Attribute : public Marshal
{
	friend class AttributeCode;
	friend class Class;
	friend class Field;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 attribute_name_index_;
	JVM_U4 attribute_length_;
	JVM_BYTE *info_;

	/**
	 * self-defined
	 */
	std::string attributeName_;

	/**
	 * for internal usage only.
	 */
	JVM_U2 constant_count_;
	Constant **constants_;

public:
	Attribute();
	virtual ~Attribute();

	JVM_U4 getAttributeLength() const;
	JVM_U2 getAttributeNameIndex() const;
	const JVM_BYTE *getInfo() const;

	const std::string &getAttributeName() const;

	/**
	 * !!!do not invoke this method in marshal of derived classes.
	 */
	virtual bool marshal(Stream &stream);
	/**
	 * !!!this method used for some attributes which not implemented read.
	 */
	static bool marshal(Stream &stream, JVM_U2 attribute_name_index, JVM_U4 attribute_length);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTE_H_ */
