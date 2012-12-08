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
 **	File Name        : ConstantInvokeDynamic.h $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 5:05:16 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_CONSTANTINVOKEDYNAMIC_H_
#define _JVM_CONSTANTINVOKEDYNAMIC_H_


#include "Constant.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class ConstantInvokeDynamic : public Constant
{
protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 bootstrap_method_attr_index_;
	JVM_U2 name_and_type_index_;

public:
	ConstantInvokeDynamic();
	virtual ~ConstantInvokeDynamic();

	JVM_U2 getBootstrapMethodAttrIndex() const;
	JVM_U2 getNameAndTypeIndex() const;

    bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_CONSTANTINVOKEDYNAMIC_H_ */