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
 **	File Name        : AttributeSourceDebugExtension.h $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 9:51:17 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTESOURCEDEBUGEXTENSION_H_
#define _JVM_ATTRIBUTESOURCEDEBUGEXTENSION_H_


#include "GlobalDefinition.h"
#include "Attribute.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class AttributeSourceDebugExtension : public Attribute
{
	friend class Class;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U1 *debug_extension_;

public:
	AttributeSourceDebugExtension();
	virtual ~AttributeSourceDebugExtension();

	const JVM_U1 *getDebugExtension() const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTESOURCEDEBUGEXTENSION_H_ */
