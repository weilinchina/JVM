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
 **	File Name        : AttributeCode.h $
 **	Created on       : Nov 17, 2012 $
 **	Time             : 9:02:57 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTECODE_H_
#define _JVM_ATTRIBUTECODE_H_


#include "GlobalDefinition.h"
#include "AttributeLineNumberTable.h"
#include "AttributeLocalVariableTable.h"
#include "AttributeLocalVariableTypeTable.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

typedef struct _EXCEPTION_TABLE
{
	/**
	 * from JVM specification.
	 */
	JVM_U2 start_pc_;
	JVM_U2 end_pc_;
	JVM_U2 handler_pc_;
	JVM_U2 catch_type_;

	/**
	 * self-defined
	 */
	std::string exceptionClassName_;
}EXCEPTION_TABLE;

class AttributeCode : public Attribute
{
	friend class Method;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U4 code_length_;
	JVM_BYTE *code_;
	JVM_U2 max_stack_;
	JVM_U2 max_locals_;
	JVM_U2 exception_table_length_;
	EXCEPTION_TABLE *exception_table_;

	/**
	 * self-defined
	 */
	AttributeLineNumberTable *javaAttributeLineNumberTable_;
	AttributeLocalVariableTable *javaAttributeLocalVariableTable_;
	AttributeLocalVariableTypeTable *javaAttributeLocalVariableTypeTable_;

public:
	AttributeCode();
	virtual ~AttributeCode();

    JVM_U4 getCodeLength() const;
    const JVM_BYTE *getCode() const;
    JVM_U2 getMaxStack() const;
    JVM_U2 getMaxLocals() const;
    JVM_U2 getExceptionTableLength() const;
    const EXCEPTION_TABLE *getExceptionTable(int at) const;

    const AttributeLineNumberTable *getJavaAttributeLineNumberTable() const;
    const AttributeLocalVariableTable *getJavaAttributeLocalVariableTable() const;
    const AttributeLocalVariableTypeTable *getJavaAttributeLocalVariableTypeTable() const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTECODE_H_ */
