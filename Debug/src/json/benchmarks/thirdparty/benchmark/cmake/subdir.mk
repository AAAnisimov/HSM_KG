################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/benchmarks/thirdparty/benchmark/cmake/gnu_posix_regex.cpp \
../src/json/benchmarks/thirdparty/benchmark/cmake/posix_regex.cpp \
../src/json/benchmarks/thirdparty/benchmark/cmake/std_regex.cpp \
../src/json/benchmarks/thirdparty/benchmark/cmake/steady_clock.cpp \
../src/json/benchmarks/thirdparty/benchmark/cmake/thread_safety_attributes.cpp 

OBJS += \
./src/json/benchmarks/thirdparty/benchmark/cmake/gnu_posix_regex.o \
./src/json/benchmarks/thirdparty/benchmark/cmake/posix_regex.o \
./src/json/benchmarks/thirdparty/benchmark/cmake/std_regex.o \
./src/json/benchmarks/thirdparty/benchmark/cmake/steady_clock.o \
./src/json/benchmarks/thirdparty/benchmark/cmake/thread_safety_attributes.o 

CPP_DEPS += \
./src/json/benchmarks/thirdparty/benchmark/cmake/gnu_posix_regex.d \
./src/json/benchmarks/thirdparty/benchmark/cmake/posix_regex.d \
./src/json/benchmarks/thirdparty/benchmark/cmake/std_regex.d \
./src/json/benchmarks/thirdparty/benchmark/cmake/steady_clock.d \
./src/json/benchmarks/thirdparty/benchmark/cmake/thread_safety_attributes.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/benchmarks/thirdparty/benchmark/cmake/%.o: ../src/json/benchmarks/thirdparty/benchmark/cmake/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


