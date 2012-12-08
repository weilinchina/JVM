################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../os/OsFile.cpp \
../os/OsThread.cpp 

OBJS += \
./os/OsFile.o \
./os/OsThread.o 

CPP_DEPS += \
./os/OsFile.d \
./os/OsThread.d 


# Each subdirectory must supply rules for building sources it contributes
os/%.o: ../os/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_DEBUG -I"/home/liwei/git/JVM/JVMCore/java" -I"/home/liwei/git/JVM/JVMCore/runtime" -I"/home/liwei/git/JVM/JVMCore/share" -I"/home/liwei/git/JVM/JVMCore/share/zlib" -I"/home/liwei/git/JVM/JVMCore/os" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


