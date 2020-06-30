################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/json/benchmarks/thirdparty/benchmark/src/benchmark.cc \
../src/json/benchmarks/thirdparty/benchmark/src/benchmark_main.cc \
../src/json/benchmarks/thirdparty/benchmark/src/benchmark_register.cc \
../src/json/benchmarks/thirdparty/benchmark/src/colorprint.cc \
../src/json/benchmarks/thirdparty/benchmark/src/commandlineflags.cc \
../src/json/benchmarks/thirdparty/benchmark/src/complexity.cc \
../src/json/benchmarks/thirdparty/benchmark/src/console_reporter.cc \
../src/json/benchmarks/thirdparty/benchmark/src/counter.cc \
../src/json/benchmarks/thirdparty/benchmark/src/csv_reporter.cc \
../src/json/benchmarks/thirdparty/benchmark/src/json_reporter.cc \
../src/json/benchmarks/thirdparty/benchmark/src/reporter.cc \
../src/json/benchmarks/thirdparty/benchmark/src/sleep.cc \
../src/json/benchmarks/thirdparty/benchmark/src/statistics.cc \
../src/json/benchmarks/thirdparty/benchmark/src/string_util.cc \
../src/json/benchmarks/thirdparty/benchmark/src/sysinfo.cc \
../src/json/benchmarks/thirdparty/benchmark/src/timers.cc 

CC_DEPS += \
./src/json/benchmarks/thirdparty/benchmark/src/benchmark.d \
./src/json/benchmarks/thirdparty/benchmark/src/benchmark_main.d \
./src/json/benchmarks/thirdparty/benchmark/src/benchmark_register.d \
./src/json/benchmarks/thirdparty/benchmark/src/colorprint.d \
./src/json/benchmarks/thirdparty/benchmark/src/commandlineflags.d \
./src/json/benchmarks/thirdparty/benchmark/src/complexity.d \
./src/json/benchmarks/thirdparty/benchmark/src/console_reporter.d \
./src/json/benchmarks/thirdparty/benchmark/src/counter.d \
./src/json/benchmarks/thirdparty/benchmark/src/csv_reporter.d \
./src/json/benchmarks/thirdparty/benchmark/src/json_reporter.d \
./src/json/benchmarks/thirdparty/benchmark/src/reporter.d \
./src/json/benchmarks/thirdparty/benchmark/src/sleep.d \
./src/json/benchmarks/thirdparty/benchmark/src/statistics.d \
./src/json/benchmarks/thirdparty/benchmark/src/string_util.d \
./src/json/benchmarks/thirdparty/benchmark/src/sysinfo.d \
./src/json/benchmarks/thirdparty/benchmark/src/timers.d 

OBJS += \
./src/json/benchmarks/thirdparty/benchmark/src/benchmark.o \
./src/json/benchmarks/thirdparty/benchmark/src/benchmark_main.o \
./src/json/benchmarks/thirdparty/benchmark/src/benchmark_register.o \
./src/json/benchmarks/thirdparty/benchmark/src/colorprint.o \
./src/json/benchmarks/thirdparty/benchmark/src/commandlineflags.o \
./src/json/benchmarks/thirdparty/benchmark/src/complexity.o \
./src/json/benchmarks/thirdparty/benchmark/src/console_reporter.o \
./src/json/benchmarks/thirdparty/benchmark/src/counter.o \
./src/json/benchmarks/thirdparty/benchmark/src/csv_reporter.o \
./src/json/benchmarks/thirdparty/benchmark/src/json_reporter.o \
./src/json/benchmarks/thirdparty/benchmark/src/reporter.o \
./src/json/benchmarks/thirdparty/benchmark/src/sleep.o \
./src/json/benchmarks/thirdparty/benchmark/src/statistics.o \
./src/json/benchmarks/thirdparty/benchmark/src/string_util.o \
./src/json/benchmarks/thirdparty/benchmark/src/sysinfo.o \
./src/json/benchmarks/thirdparty/benchmark/src/timers.o 


# Each subdirectory must supply rules for building sources it contributes
src/json/benchmarks/thirdparty/benchmark/src/%.o: ../src/json/benchmarks/thirdparty/benchmark/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


