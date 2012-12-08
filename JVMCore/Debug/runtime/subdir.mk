################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../runtime/BootstrapClassLoader.cpp \
../runtime/Frame.cpp \
../runtime/FrameStack.cpp \
../runtime/OperandStack.cpp \
../runtime/Thread.cpp 

OBJS += \
./runtime/BootstrapClassLoader.o \
./runtime/Frame.o \
./runtime/FrameStack.o \
./runtime/OperandStack.o \
./runtime/Thread.o 

CPP_DEPS += \
./runtime/BootstrapClassLoader.d \
./runtime/Frame.d \
./runtime/FrameStack.d \
./runtime/OperandStack.d \
./runtime/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
runtime/%.o: ../runtime/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_DEBUG -I"/home/liwei/works/jvm/dev/JVMCore/java" -I"/home/liwei/works/jvm/dev/JVMCore/runtime" -I"/home/liwei/works/jvm/dev/JVMCore/share" -I"/home/liwei/works/jvm/dev/JVMCore/share/zlib" -I"/home/liwei/works/jvm/dev/JVMCore/os" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


