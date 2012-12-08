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
 **	File Name        : AttributeConstantValue.h $
 **	Created on       : Nov 18, 2012 $
 **	Time             : 10:29:06 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTECONSTANTVALUE_H_
#define _JVM_ATTRIBUTECONSTANTVALUE_H_


#include "Attribute.h"
#include "ConstantValue.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class AttributeConstantValue : public Attribute
{
	friend class Field;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 constantvalue_index_;

	/**
	 * self-defined
	 */
	/**
	 * this pointer can't be deleted, because it's just a reference to the constant value inside constant pool.
	 */
	ConstantValue *javaConstantValue_;
public:
	AttributeConstantValue();
	virtual ~AttributeConstantValue();

	JVM_U2 getConstantvalueIndex() const;

	const ConstantValue *getJavaConstantValue() const;
	const CONSTANT_VALUE_TYPE getValueType() const;
	const std::string getValue() const;
	const std::string getStringValue() const;
	JVM_INT getIntValue() const;
	JVM_DOUBLE getDoubleValue() const;
	JVM_FLOAT getFloatValue() const;
	JVM_LONG getLongValue() const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTECONSTANTVALUE_H_ */
