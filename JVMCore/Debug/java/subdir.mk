################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../java/Attribute.cpp \
../java/AttributeBootstrapMethods.cpp \
../java/AttributeCode.cpp \
../java/AttributeConstantValue.cpp \
../java/AttributeEnclosingMethod.cpp \
../java/AttributeExceptions.cpp \
../java/AttributeInnerClasses.cpp \
../java/AttributeLineNumberTable.cpp \
../java/AttributeLocalVariableTable.cpp \
../java/AttributeLocalVariableTypeTable.cpp \
../java/AttributeSignature.cpp \
../java/AttributeSourceDebugExtension.cpp \
../java/AttributeSourceFile.cpp \
../java/Class.cpp \
../java/ClassLoader.cpp \
../java/Constant.cpp \
../java/ConstantClass.cpp \
../java/ConstantDouble.cpp \
../java/ConstantFieldRef.cpp \
../java/ConstantFloat.cpp \
../java/ConstantInteger.cpp \
../java/ConstantInterfaceMethodRef.cpp \
../java/ConstantInvokeDynamic.cpp \
../java/ConstantLong.cpp \
../java/ConstantMethodHandle.cpp \
../java/ConstantMethodRef.cpp \
../java/ConstantMethodType.cpp \
../java/ConstantNameAndType.cpp \
../java/ConstantString.cpp \
../java/ConstantUtf8.cpp \
../java/ConstantValue.cpp \
../java/Field.cpp \
../java/Method.cpp \
../java/Package.cpp 

OBJS += \
./java/Attribute.o \
./java/AttributeBootstrapMethods.o \
./java/AttributeCode.o \
./java/AttributeConstantValue.o \
./java/AttributeEnclosingMethod.o \
./java/AttributeExceptions.o \
./java/AttributeInnerClasses.o \
./java/AttributeLineNumberTable.o \
./java/AttributeLocalVariableTable.o \
./java/AttributeLocalVariableTypeTable.o \
./java/AttributeSignature.o \
./java/AttributeSourceDebugExtension.o \
./java/AttributeSourceFile.o \
./java/Class.o \
./java/ClassLoader.o \
./java/Constant.o \
./java/ConstantClass.o \
./java/ConstantDouble.o \
./java/ConstantFieldRef.o \
./java/ConstantFloat.o \
./java/ConstantInteger.o \
./java/ConstantInterfaceMethodRef.o \
./java/ConstantInvokeDynamic.o \
./java/ConstantLong.o \
./java/ConstantMethodHandle.o \
./java/ConstantMethodRef.o \
./java/ConstantMethodType.o \
./java/ConstantNameAndType.o \
./java/ConstantString.o \
./java/ConstantUtf8.o \
./java/ConstantValue.o \
./java/Field.o \
./java/Method.o \
./java/Package.o 

CPP_DEPS += \
./java/Attribute.d \
./java/AttributeBootstrapMethods.d \
./java/AttributeCode.d \
./java/AttributeConstantValue.d \
./java/AttributeEnclosingMethod.d \
./java/AttributeExceptions.d \
./java/AttributeInnerClasses.d \
./java/AttributeLineNumberTable.d \
./java/AttributeLocalVariableTable.d \
./java/AttributeLocalVariableTypeTable.d \
./java/AttributeSignature.d \
./java/AttributeSourceDebugExtension.d \
./java/AttributeSourceFile.d \
./java/Class.d \
./java/ClassLoader.d \
./java/Constant.d \
./java/ConstantClass.d \
./java/ConstantDouble.d \
./java/ConstantFieldRef.d \
./java/ConstantFloat.d \
./java/ConstantInteger.d \
./java/ConstantInterfaceMethodRef.d \
./java/ConstantInvokeDynamic.d \
./java/ConstantLong.d \
./java/ConstantMethodHandle.d \
./java/ConstantMethodRef.d \
./java/ConstantMethodType.d \
./java/ConstantNameAndType.d \
./java/ConstantString.d \
./java/ConstantUtf8.d \
./java/ConstantValue.d \
./java/Field.d \
./java/Method.d \
./java/Package.d 


# Each subdirectory must supply rules for building sources it contributes
java/%.o: ../java/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_DEBUG -I"/home/liwei/git/JVM/JVMCore/java" -I"/home/liwei/git/JVM/JVMCore/runtime" -I"/home/liwei/git/JVM/JVMCore/share" -I"/home/liwei/git/JVM/JVMCore/share/zlib" -I"/home/liwei/git/JVM/JVMCore/os" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


