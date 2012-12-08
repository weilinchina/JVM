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
 **	File Name        : ConstantValue.h $
 **	Created on       : Nov 24, 2012 $
 **	Time             : 5:30:13 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_CONSTANTVALUE_H_
#define _JVM_CONSTANTVALUE_H_


#include "Constant.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

typedef enum _CONSTANT_VALUE_TYPE
{
	CONSTANT_VALUE_TYPE_UNKNOWN = 0,
	CONSTANT_VALUE_TYPE_LONG,
	CONSTANT_VALUE_TYPE_FLOAT,
	CONSTANT_VALUE_TYPE_DOUBLE,
	CONSTANT_VALUE_TYPE_INTEGER,
	CONSTANT_VALUE_TYPE_STRING,
}CONSTANT_VALUE_TYPE;

class ConstantValue : public Constant
{
	friend class Field;

protected:
	CONSTANT_VALUE_TYPE constantValueType_;

public:
	ConstantValue();
	virtual ~ConstantValue();

	const CONSTANT_VALUE_TYPE getConstantValueType() const;
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_CONSTANTVALUE_H_ */
