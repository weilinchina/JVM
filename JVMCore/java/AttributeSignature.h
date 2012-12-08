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
 **	File Name        : AttributeSignature.h $
 **	Created on       : Nov 18, 2012 $
 **	Time             : 9:08:29 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTESIGNATURE_H_
#define _JVM_ATTRIBUTESIGNATURE_H_


#include "GlobalDefinition.h"
#include "Attribute.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class AttributeSignature : public Attribute
{
	friend class Method;
	friend class Class;
	friend class Field;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 signature_index_;

	/**
	 * self-defined
	 */
	std::string signature_;

public:
	AttributeSignature();
	virtual ~AttributeSignature();

	JVM_U2 getSignatureIndex() const;

	const std::string &getSignature() const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTESIGNATURE_H_ */
