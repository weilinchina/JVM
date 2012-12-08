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
 **	File Name        : AttributeInnerClasses.h $
 **	Created on       : Nov 19, 2012 $
 **	Time             : 10:45:21 AM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTEINNERCLASSES_H_
#define _JVM_ATTRIBUTEINNERCLASSES_H_


#include "GlobalDefinition.h"
#include "Attribute.h"

#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

typedef struct _INNER_CLASS
{
	/**
	 * from JVM specification.
	 */
	JVM_U2 inner_class_info_index_;
	JVM_U2 outer_class_info_index_;
	JVM_U2 inner_name_index_;
	JVM_U2 inner_class_access_flags_;

	/**
	 * self-defined
	 */
	std::string innerClassName_;
	std::string outerClassName_;
	std::string innerName_;
}INNER_CLASS;

class AttributeInnerClasses : public Attribute
{
	friend class Class;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 number_of_classes_;
	INNER_CLASS *classes_;

public:
	AttributeInnerClasses();
	virtual ~AttributeInnerClasses();

    JVM_U2 getNumberOfClasses() const;
    const INNER_CLASS *getClass(int at) const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTEINNERCLASSES_H_ */
