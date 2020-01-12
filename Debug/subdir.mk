################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../AST.cc \
../ContextInfo.cc \
../generateHERA.cc \
../main.cc \
../parser.cc \
../scanner-regexp.cc \
../scanner.cc \
../scannerDemo.cc 

CC_DEPS += \
./AST.d \
./ContextInfo.d \
./generateHERA.d \
./main.d \
./parser.d \
./scanner-regexp.d \
./scanner.d \
./scannerDemo.d 

OBJS += \
./AST.o \
./ContextInfo.o \
./generateHERA.o \
./main.o \
./parser.o \
./scanner-regexp.o \
./scanner.o \
./scannerDemo.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/home/courses/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


