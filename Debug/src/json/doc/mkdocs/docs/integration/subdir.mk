################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/doc/mkdocs/docs/integration/example.cpp 

OBJS += \
./src/json/doc/mkdocs/docs/integration/example.o 

CPP_DEPS += \
./src/json/doc/mkdocs/docs/integration/example.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/doc/mkdocs/docs/integration/%.o: ../src/json/doc/mkdocs/docs/integration/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


