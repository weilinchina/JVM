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
 **	File Name        : AttributeLocalVariableTable.h $
 **	Created on       : Nov 23, 2012 $
 **	Time             : 4:22:04 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTELOCALVARIABLETABLE_H_
#define _JVM_ATTRIBUTELOCALVARIABLETABLE_H_


#include "GlobalDefinition.h"
#include "Attribute.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

typedef struct _LOCAL_VARIABLE
{
	/**
	 * from JVM specification.
	 */
	JVM_U2 start_pc_;
	JVM_U2 length_;
	JVM_U2 name_index_;
	JVM_U2 descriptor_index_;
	JVM_U2 index_;

	/**
	 * self-defined
	 */
	std::string name_;
	std::string descriptor_;
}LOCAL_VARIABLE;

class AttributeLocalVariableTable : public Attribute
{
	friend class AttributeCode;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 local_variable_table_length_;
	LOCAL_VARIABLE *local_variable_table_;

public:
	AttributeLocalVariableTable();
	virtual ~AttributeLocalVariableTable();

    JVM_U2 getLocalVariableTableLength() const;
    const LOCAL_VARIABLE *getLocalVariableTable(int at) const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTELOCALVARIABLETABLE_H_ */
