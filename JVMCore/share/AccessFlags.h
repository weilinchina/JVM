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
 **	File Name        : AccessFlags.h $
 **	Created on       : Nov 15, 2012 $
 **	Time             : 1:51:09 PM $
 ** Author           : liwei $
 ** ============================================================================
 ** Contents: This is a header/source file which includes all the functions prototypes
 **           and data types, implementations.
 **
 ** =========================================================================================== */


#ifndef _JVM_ACCESSFLAGS_H_
#define _JVM_ACCESSFLAGS_H_


#ifdef __cplusplus
extern "C"
{
#endif


#define ACC_PUBLIC                  0x0001
#define ACC_PRIVATE                 0x0002
#define ACC_PROTECTED               0x0004
#define ACC_STATIC                  0x0008
#define ACC_FINAL                   0x0010
#define ACC_SUPER                   0x0020
#define ACC_SYNCHRONIZED            0x0020
#define ACC_VOLATILE                0x0040
#define ACC_BRIDGE                  0x0040
#define ACC_TRANSIENT               0x0080
#define ACC_VARARGS                 0x0080
#define ACC_NATIVE                  0x0100
#define ACC_INTERFACE               0x0200
#define ACC_ABSTRACT                0x0400
#define ACC_STRICT                  0x0800
#define ACC_SYNTHETIC               0x1000
#define ACC_ANNOTATION              0x2000
#define ACC_ENUM                    0x4000


#define CLASS_ACC_FLAGS             ACC_PUBLIC | ACC_FINAL | ACC_SUPER | ACC_INTERFACE | ACC_ABSTRACT | ACC_SYNTHETIC | ACC_ANNOTATION | ACC_ENUM
#define FIELD_ACC_FLAGS             ACC_PUBLIC | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC | ACC_FINAL | ACC_VOLATILE | ACC_TRANSIENT | ACC_SYNTHETIC | ACC_ENUM
#define METHOD_ACC_FLAGS            ACC_PUBLIC | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC | ACC_FINAL | ACC_SYNCHRONIZED | ACC_BRIDGE | ACC_VARARGS | ACC_NATIVE | ACC_ABSTRACT | ACC_STRICT | ACC_SYNTHETIC
#define INNER_CLASS_ACC_FLAGS       ACC_PUBLIC | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC | ACC_FINAL | ACC_INTERFACE | ACC_ABSTRACT | ACC_SYNTHETIC | ACC_ANNOTATION | ACC_ENUM


#ifdef __cplusplus
}
#endif


#endif /* _JVM_ACCESSFLAGS_H_ */
