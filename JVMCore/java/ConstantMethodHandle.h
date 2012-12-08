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
 **	File Name        : ConstantMethodHandle.h $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_CONSTANTMETHODHANDLE_H_
#define _JVM_CONSTANTMETHODHANDLE_H_


#include "Constant.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class ConstantMethodHandle : public Constant
{
protected:
	/**
	 * from JVM specification.
	 */
	JVM_U1 reference_kind_;
	JVM_U2 reference_index_;

public:
	ConstantMethodHandle();
	virtual ~ConstantMethodHandle();

    JVM_U1 getReferenceKind() const;
    JVM_U2 getReferenceIndex() const;

    bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_CONSTANTMETHODHANDLE_H_ */
