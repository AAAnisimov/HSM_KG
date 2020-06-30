################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Base64.cpp \
../src/Crypt.cpp \
../src/HSM_KG.cpp 

OBJS += \
./src/Base64.o \
./src/Crypt.o \
./src/HSM_KG.o 

CPP_DEPS += \
./src/Base64.d \
./src/Crypt.d \
./src/HSM_KG.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


