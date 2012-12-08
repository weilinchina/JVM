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
 **	File Name        : AttributeLineNumberTable.h $
 **	Created on       : Nov 23, 2012 $
 **	Time             : 4:04:42 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTELINENUMBERTABLE_H_
#define _JVM_ATTRIBUTELINENUMBERTABLE_H_


#include "GlobalDefinition.h"
#include "Attribute.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

typedef struct _LINE_NUMBER
{
	/**
	 * from JVM specification.
	 */
	JVM_U2 start_pc_;
	JVM_U2 line_number_;
}LINE_NUMBER;

class AttributeLineNumberTable : public Attribute
{
	friend class AttributeCode;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 line_number_table_length_;
	LINE_NUMBER *line_number_table_;

public:
	AttributeLineNumberTable();
	virtual ~AttributeLineNumberTable();

    JVM_U2 getLineNumberTableLength() const;
    const LINE_NUMBER *getLineNumberTable(int at) const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTELINENUMBERTABLE_H_ */
