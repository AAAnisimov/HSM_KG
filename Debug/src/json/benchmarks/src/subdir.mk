################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/benchmarks/src/benchmarks.cpp 

OBJS += \
./src/json/benchmarks/src/benchmarks.o 

CPP_DEPS += \
./src/json/benchmarks/src/benchmarks.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/benchmarks/src/%.o: ../src/json/benchmarks/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


