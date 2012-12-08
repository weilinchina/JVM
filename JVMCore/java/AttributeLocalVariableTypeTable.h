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
 **	File Name        : AttributeLocalVariableTypeTable.h $
 **	Created on       : Nov 23, 2012 $
 **	Time             : 5:21:41 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTELOCALVARIABLETYPETABLE_H_
#define _JVM_ATTRIBUTELOCALVARIABLETYPETABLE_H_


#include "Attribute.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

typedef struct _LOCAL_VARIABLE_TYPE
{
	/**
	 * from JVM specification.
	 */
	JVM_U2 start_pc_;
	JVM_U2 length_;
	JVM_U2 name_index_;
	JVM_U2 signature_index_;
	JVM_U2 index_;

	/**
	 * self-defined
	 */
	std::string name_;
	std::string signature_;
}LOCAL_VARIABLE_TYPE;

class AttributeLocalVariableTypeTable : public Attribute
{
	friend class AttributeCode;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 local_variable_type_table_length_;
	LOCAL_VARIABLE_TYPE *local_variable_type_table_;

public:
	AttributeLocalVariableTypeTable();
	virtual ~AttributeLocalVariableTypeTable();

    JVM_U2 getLocalVariableTypeTableLength() const;
    const LOCAL_VARIABLE_TYPE *getLocalVariableTypeTable(int at) const;

    bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTELOCALVARIABLETYPETABLE_H_ */
