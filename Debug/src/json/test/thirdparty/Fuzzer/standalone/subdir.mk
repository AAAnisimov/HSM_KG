################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/json/test/thirdparty/Fuzzer/standalone/StandaloneFuzzTargetMain.c 

OBJS += \
./src/json/test/thirdparty/Fuzzer/standalone/StandaloneFuzzTargetMain.o 

C_DEPS += \
./src/json/test/thirdparty/Fuzzer/standalone/StandaloneFuzzTargetMain.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/test/thirdparty/Fuzzer/standalone/%.o: ../src/json/test/thirdparty/Fuzzer/standalone/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


