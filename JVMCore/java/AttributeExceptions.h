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
 **	File Name        : AttributeExceptions.h $
 **	Created on       : Nov 18, 2012 $
 **	Time             : 8:24:37 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_ATTRIBUTEEXCEPTIONS_H_
#define _JVM_ATTRIBUTEEXCEPTIONS_H_


#include "GlobalDefinition.h"
#include "Attribute.h"

#include <vector>
#include <string>


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class AttributeExceptions : public Attribute
{
	friend class Method;

protected:
	/**
	 * from JVM specification.
	 */
	JVM_U2 number_of_exceptions_;
	JVM_U2 *exception_index_table_;

	/**
	 * self-defined
	 */
	std::vector<std::string> exceptionNames_;

public:
	AttributeExceptions();
	virtual ~AttributeExceptions();

	JVM_U2 getNumberOfExceptions() const;
	const JVM_U2 getExceptionIndexTable(int at) const;

	const std::vector<std::string> &getExceptionNames() const;

	bool marshal(Stream &stream);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ATTRIBUTEEXCEPTIONS_H_ */
