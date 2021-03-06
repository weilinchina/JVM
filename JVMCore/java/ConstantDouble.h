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
 **	File Name        : ConstantDouble.h $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_CONSTANTDOUBLE_H_
#define _JVM_CONSTANTDOUBLE_H_


#include "ConstantValue.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class ConstantDouble : public ConstantValue
{
protected:
	/**
	 * from JVM specification.
	 */
	JVM_U4 high_bytes_;
	JVM_U4 low_bytes_;

public:
	ConstantDouble();
	virtual ~ConstantDouble();

	JVM_U4 getHighBytes() const;
	JVM_U4 getLowBytes() const;

    bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_CONSTANTDOUBLE_H_ */
