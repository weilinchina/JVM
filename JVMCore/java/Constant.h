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
 **	File Name        : Constant.h $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 6:03:09 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#ifndef _JVM_CONSTANT_H_
#define _JVM_CONSTANT_H_


#include "GlobalDefinition.h"
#include "Marshal.h"


#ifdef __cplusplus
extern "C"
{
#endif


namespace diamon_jvm
{

class Constant : public Marshal
{
protected:
	/**
	 * from JVM specification.
	 */
	JVM_U1 tag_;

public:
	Constant();
	virtual ~Constant();

    JVM_U1 getTag() const;

    INLINE
    static Constant *dispatchMarshal(Stream &stream, JVM_U1 tag);
    INLINE
    static const Constant *getConstant(JVM_U2 at, JVM_U2 constant_count, Constant **constants);
};

} /* namespace diamon_jvm */


#ifdef __cplusplus
}
#endif


#endif /* _JVM_CONSTANT_H_ */
