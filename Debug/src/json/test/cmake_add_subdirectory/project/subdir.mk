################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/test/cmake_add_subdirectory/project/main.cpp 

OBJS += \
./src/json/test/cmake_add_subdirectory/project/main.o 

CPP_DEPS += \
./src/json/test/cmake_add_subdirectory/project/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/test/cmake_add_subdirectory/project/%.o: ../src/json/test/cmake_add_subdirectory/project/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


