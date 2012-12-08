################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../share/Debug.cpp \
../share/FileStream.cpp \
../share/JVMUtility.cpp \
../share/MemoryStream.cpp 

OBJS += \
./share/Debug.o \
./share/FileStream.o \
./share/JVMUtility.o \
./share/MemoryStream.o 

CPP_DEPS += \
./share/Debug.d \
./share/FileStream.d \
./share/JVMUtility.d \
./share/MemoryStream.d 


# Each subdirectory must supply rules for building sources it contributes
share/%.o: ../share/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_DEBUG -I"/home/liwei/git/JVM/JVMCore/java" -I"/home/liwei/git/JVM/JVMCore/runtime" -I"/home/liwei/git/JVM/JVMCore/share" -I"/home/liwei/git/JVM/JVMCore/share/zlib" -I"/home/liwei/git/JVM/JVMCore/os" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


