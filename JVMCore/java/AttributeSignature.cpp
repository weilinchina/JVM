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
 **	File Name        : AttributeSignature.cpp $
 **	Created on       : Nov 18, 2012 $
 **	Time             : 9:08:30 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */

#include "AttributeSignature.h"

#include "JVMUtility.h"
#include "Constant.h"
#include "ConstantUtf8.h"


namespace diamon_jvm
{

AttributeSignature::AttributeSignature() : Attribute()
{
	this->signature_index_ = 0;

	this->signature_ = "";
}

AttributeSignature::~AttributeSignature()
{
	// TODO Auto-generated destructor stub
}

JVM_U2 AttributeSignature::getSignatureIndex() const
{
	return signature_index_;
}

const std::string &AttributeSignature::getSignature() const
{
	return signature_;
}

bool AttributeSignature::marshal(Stream &stream)
{
	// read @signature_index_
	size_t size = stream.readBytes((JVM_BYTE *)&this->signature_index_, sizeof(this->signature_index_));
	if(size != sizeof(this->signature_index_))
	{
		ERROR("read signature_index of AttributeSignature failed!");
		return false;
	}
	this->signature_index_ = swap_JVM_U2(this->signature_index_);
	ConstantUtf8 *javaCPUtf8_signature = (ConstantUtf8 *)(Constant::getConstant(this->signature_index_, this->constant_count_, this->constants_));
	if(javaCPUtf8_signature != NULL)
	{
		this->signature_.assign((char*)(javaCPUtf8_signature->getBytes()), javaCPUtf8_signature->getLength());
		TRACE("method signature is: %s", this->signature_.c_str());
	}

	return true;
}

} /* namespace diamon_jvm */
