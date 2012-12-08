################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../JavaClassFileTest.cpp 

OBJS += \
./JavaClassFileTest.o 

CPP_DEPS += \
./JavaClassFileTest.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_DEBUG -I"/home/liwei/works/jvm/dev/JVMCore" -I"/home/liwei/works/jvm/dev/JVMCore/java" -I"/home/liwei/works/jvm/dev/JVMCore/runtime" -I"/home/liwei/works/jvm/dev/JVMCore/share" -I"/home/liwei/works/jvm/dev/JVMCore/share/zlib" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


