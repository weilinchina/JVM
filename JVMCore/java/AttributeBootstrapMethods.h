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
 **	File Name        : AttributeBootstrapMethods.h $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 10:12:53 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTEBOOTSTRAPMETHODS_H_
#define _JVM_ATTRIBUTEBOOTSTRAPMETHODS_H_


#include "GlobalDefinition.h"
#include "Attribute.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

typedef struct _BOOTSTRAP_METHOD
{
	/**
	 * from JVM specification.
	 */
	JVM_U2 bootstrap_method_ref_;
	JVM_U2 num_bootstrap_arguments_;
	JVM_U2 *bootstrap_arguments_;

	/**
	 * self-defined
	 */
}BOOTSTRAP_METHOD;

class AttributeBootstrapMethods : public Attribute
{
	friend class Class;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 num_bootstrap_methods_;
	BOOTSTRAP_METHOD *bootstrap_methods_;

public:
	AttributeBootstrapMethods();
	virtual ~AttributeBootstrapMethods();

	JVM_U2 getNumBootstrapMethods() const;
	const BOOTSTRAP_METHOD *getBootstrapMethod(int at) const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTEBOOTSTRAPMETHODS_H_ */
