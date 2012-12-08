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
 **	File Name        : Constant.cpp $
 **	Created on       : Nov 13, 2012 $
 **	Time             : 6:03:09 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "Constant.h"

#include "ConstantClass.h"
#include "ConstantFieldRef.h"
#include "ConstantMethodRef.h"
#include "ConstantInterfaceMethodRef.h"
#include "ConstantString.h"
#include "ConstantInteger.h"
#include "ConstantFloat.h"
#include "ConstantLong.h"
#include "ConstantDouble.h"
#include "ConstantNameAndType.h"
#include "ConstantUtf8.h"
#include "ConstantMethodHandle.h"
#include "ConstantMethodType.h"
#include "ConstantInvokeDynamic.h"


namespace diamon_jvm
{

Constant::Constant()
{
	this->tag_ = 0;
}

Constant::~Constant()
{
	// TODO Auto-generated destructor stub
}

JVM_U1 Constant::getTag() const
{
	return tag_;
}

INLINE
Constant *Constant::dispatchMarshal(Stream &stream, JVM_U1 tag)
{
	Constant *constant = NULL;

	switch(tag)
	{
	case 7:
		constant = new ConstantClass();
		break;
	case 9:
		constant = new ConstantFieldRef();
		break;
	case 10:
		constant = new ConstantMethodRef();
		break;
	case 11:
		constant = new ConstantInterfaceMethodRef();
		break;
	case 8:
		constant = new ConstantString();
		break;
	case 3:
		constant = new ConstantInteger();
		break;
	case 4:
		constant = new ConstantFloat();
		break;
	case 5:
		constant = new ConstantLong();
		break;
	case 6:
		constant = new ConstantDouble();
		break;
	case 12:
		constant = new ConstantNameAndType();
		break;
	case 1:
		constant = new ConstantUtf8();
		break;
	case 15:
		constant = new ConstantMethodHandle();
		break;
	case 16:
		constant = new ConstantMethodType();
		break;
	case 18:
		constant = new ConstantInvokeDynamic();
		break;
	default:
		ERROR("tag is %d, this should not happened!", tag);
		break;
	}

	if(constant != NULL)
	{
		constant->tag_ = tag;
		if(constant->marshal(stream) == false)
		{
			ERROR("constant %d marshal failed! this constant object will be removed.", tag);
			delete constant;
			return NULL;
		}
	}
	return constant;
}

INLINE
const Constant *Constant::getConstant(JVM_U2 at, JVM_U2 constant_count, Constant **constants)
{
	if(at < 1 || at > constant_count)
	{
		ERROR("invalid index to locate constant from constant pool!, should be between %d and %d", 1, constant_count);
		return NULL;
	}
	if(constants == NULL)
	{
		ERROR("no constant defined in class!");
		return NULL;
	}
	return constants[at - 1];
}

} /* namespace diamon_jvm */
