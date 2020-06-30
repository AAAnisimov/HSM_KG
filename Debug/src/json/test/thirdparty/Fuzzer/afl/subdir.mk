################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/test/thirdparty/Fuzzer/afl/afl_driver.cpp 

OBJS += \
./src/json/test/thirdparty/Fuzzer/afl/afl_driver.o 

CPP_DEPS += \
./src/json/test/thirdparty/Fuzzer/afl/afl_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/test/thirdparty/Fuzzer/afl/%.o: ../src/json/test/thirdparty/Fuzzer/afl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


