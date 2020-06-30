################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/test/thirdparty/Fuzzer/test/AFLDriverTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/AbsNegAndConstant64Test.cpp \
../src/json/test/thirdparty/Fuzzer/test/AbsNegAndConstantTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/AccumulateAllocationsTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/BufferOverflowOnInput.cpp \
../src/json/test/thirdparty/Fuzzer/test/CallerCalleeTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/CounterTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/CustomCrossOverTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/CustomMutatorTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/DSO1.cpp \
../src/json/test/thirdparty/Fuzzer/test/DSO2.cpp \
../src/json/test/thirdparty/Fuzzer/test/DSOTestExtra.cpp \
../src/json/test/thirdparty/Fuzzer/test/DSOTestMain.cpp \
../src/json/test/thirdparty/Fuzzer/test/DivTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/EmptyTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/FourIndependentBranchesTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/FullCoverageSetTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/FuzzerUnittest.cpp \
../src/json/test/thirdparty/Fuzzer/test/InitializeTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/LeakTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/LeakTimeoutTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/LoadTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/MemcmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/NthRunCrashTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/NullDerefOnEmptyTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/NullDerefTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/OneHugeAllocTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/OutOfMemorySingleLargeMallocTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/OutOfMemoryTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/RepeatedBytesTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/RepeatedMemcmp.cpp \
../src/json/test/thirdparty/Fuzzer/test/ShrinkControlFlowTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/ShrinkValueProfileTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SignedIntOverflowTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SimpleCmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SimpleDictionaryTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SimpleHashTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SimpleTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SimpleThreadedTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SingleMemcmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SingleStrcmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SingleStrncmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SpamyTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/StrcmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/StrncmpOOBTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/StrncmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/StrstrTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/SwapCmpTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/Switch2Test.cpp \
../src/json/test/thirdparty/Fuzzer/test/SwitchTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/ThreadedLeakTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/ThreadedTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/TimeoutEmptyTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/TimeoutTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/TraceMallocTest.cpp \
../src/json/test/thirdparty/Fuzzer/test/UninstrumentedTest.cpp 

OBJS += \
./src/json/test/thirdparty/Fuzzer/test/AFLDriverTest.o \
./src/json/test/thirdparty/Fuzzer/test/AbsNegAndConstant64Test.o \
./src/json/test/thirdparty/Fuzzer/test/AbsNegAndConstantTest.o \
./src/json/test/thirdparty/Fuzzer/test/AccumulateAllocationsTest.o \
./src/json/test/thirdparty/Fuzzer/test/BufferOverflowOnInput.o \
./src/json/test/thirdparty/Fuzzer/test/CallerCalleeTest.o \
./src/json/test/thirdparty/Fuzzer/test/CounterTest.o \
./src/json/test/thirdparty/Fuzzer/test/CustomCrossOverTest.o \
./src/json/test/thirdparty/Fuzzer/test/CustomMutatorTest.o \
./src/json/test/thirdparty/Fuzzer/test/DSO1.o \
./src/json/test/thirdparty/Fuzzer/test/DSO2.o \
./src/json/test/thirdparty/Fuzzer/test/DSOTestExtra.o \
./src/json/test/thirdparty/Fuzzer/test/DSOTestMain.o \
./src/json/test/thirdparty/Fuzzer/test/DivTest.o \
./src/json/test/thirdparty/Fuzzer/test/EmptyTest.o \
./src/json/test/thirdparty/Fuzzer/test/FourIndependentBranchesTest.o \
./src/json/test/thirdparty/Fuzzer/test/FullCoverageSetTest.o \
./src/json/test/thirdparty/Fuzzer/test/FuzzerUnittest.o \
./src/json/test/thirdparty/Fuzzer/test/InitializeTest.o \
./src/json/test/thirdparty/Fuzzer/test/LeakTest.o \
./src/json/test/thirdparty/Fuzzer/test/LeakTimeoutTest.o \
./src/json/test/thirdparty/Fuzzer/test/LoadTest.o \
./src/json/test/thirdparty/Fuzzer/test/MemcmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/NthRunCrashTest.o \
./src/json/test/thirdparty/Fuzzer/test/NullDerefOnEmptyTest.o \
./src/json/test/thirdparty/Fuzzer/test/NullDerefTest.o \
./src/json/test/thirdparty/Fuzzer/test/OneHugeAllocTest.o \
./src/json/test/thirdparty/Fuzzer/test/OutOfMemorySingleLargeMallocTest.o \
./src/json/test/thirdparty/Fuzzer/test/OutOfMemoryTest.o \
./src/json/test/thirdparty/Fuzzer/test/RepeatedBytesTest.o \
./src/json/test/thirdparty/Fuzzer/test/RepeatedMemcmp.o \
./src/json/test/thirdparty/Fuzzer/test/ShrinkControlFlowTest.o \
./src/json/test/thirdparty/Fuzzer/test/ShrinkValueProfileTest.o \
./src/json/test/thirdparty/Fuzzer/test/SignedIntOverflowTest.o \
./src/json/test/thirdparty/Fuzzer/test/SimpleCmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/SimpleDictionaryTest.o \
./src/json/test/thirdparty/Fuzzer/test/SimpleHashTest.o \
./src/json/test/thirdparty/Fuzzer/test/SimpleTest.o \
./src/json/test/thirdparty/Fuzzer/test/SimpleThreadedTest.o \
./src/json/test/thirdparty/Fuzzer/test/SingleMemcmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/SingleStrcmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/SingleStrncmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/SpamyTest.o \
./src/json/test/thirdparty/Fuzzer/test/StrcmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/StrncmpOOBTest.o \
./src/json/test/thirdparty/Fuzzer/test/StrncmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/StrstrTest.o \
./src/json/test/thirdparty/Fuzzer/test/SwapCmpTest.o \
./src/json/test/thirdparty/Fuzzer/test/Switch2Test.o \
./src/json/test/thirdparty/Fuzzer/test/SwitchTest.o \
./src/json/test/thirdparty/Fuzzer/test/ThreadedLeakTest.o \
./src/json/test/thirdparty/Fuzzer/test/ThreadedTest.o \
./src/json/test/thirdparty/Fuzzer/test/TimeoutEmptyTest.o \
./src/json/test/thirdparty/Fuzzer/test/TimeoutTest.o \
./src/json/test/thirdparty/Fuzzer/test/TraceMallocTest.o \
./src/json/test/thirdparty/Fuzzer/test/UninstrumentedTest.o 

CPP_DEPS += \
./src/json/test/thirdparty/Fuzzer/test/AFLDriverTest.d \
./src/json/test/thirdparty/Fuzzer/test/AbsNegAndConstant64Test.d \
./src/json/test/thirdparty/Fuzzer/test/AbsNegAndConstantTest.d \
./src/json/test/thirdparty/Fuzzer/test/AccumulateAllocationsTest.d \
./src/json/test/thirdparty/Fuzzer/test/BufferOverflowOnInput.d \
./src/json/test/thirdparty/Fuzzer/test/CallerCalleeTest.d \
./src/json/test/thirdparty/Fuzzer/test/CounterTest.d \
./src/json/test/thirdparty/Fuzzer/test/CustomCrossOverTest.d \
./src/json/test/thirdparty/Fuzzer/test/CustomMutatorTest.d \
./src/json/test/thirdparty/Fuzzer/test/DSO1.d \
./src/json/test/thirdparty/Fuzzer/test/DSO2.d \
./src/json/test/thirdparty/Fuzzer/test/DSOTestExtra.d \
./src/json/test/thirdparty/Fuzzer/test/DSOTestMain.d \
./src/json/test/thirdparty/Fuzzer/test/DivTest.d \
./src/json/test/thirdparty/Fuzzer/test/EmptyTest.d \
./src/json/test/thirdparty/Fuzzer/test/FourIndependentBranchesTest.d \
./src/json/test/thirdparty/Fuzzer/test/FullCoverageSetTest.d \
./src/json/test/thirdparty/Fuzzer/test/FuzzerUnittest.d \
./src/json/test/thirdparty/Fuzzer/test/InitializeTest.d \
./src/json/test/thirdparty/Fuzzer/test/LeakTest.d \
./src/json/test/thirdparty/Fuzzer/test/LeakTimeoutTest.d \
./src/json/test/thirdparty/Fuzzer/test/LoadTest.d \
./src/json/test/thirdparty/Fuzzer/test/MemcmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/NthRunCrashTest.d \
./src/json/test/thirdparty/Fuzzer/test/NullDerefOnEmptyTest.d \
./src/json/test/thirdparty/Fuzzer/test/NullDerefTest.d \
./src/json/test/thirdparty/Fuzzer/test/OneHugeAllocTest.d \
./src/json/test/thirdparty/Fuzzer/test/OutOfMemorySingleLargeMallocTest.d \
./src/json/test/thirdparty/Fuzzer/test/OutOfMemoryTest.d \
./src/json/test/thirdparty/Fuzzer/test/RepeatedBytesTest.d \
./src/json/test/thirdparty/Fuzzer/test/RepeatedMemcmp.d \
./src/json/test/thirdparty/Fuzzer/test/ShrinkControlFlowTest.d \
./src/json/test/thirdparty/Fuzzer/test/ShrinkValueProfileTest.d \
./src/json/test/thirdparty/Fuzzer/test/SignedIntOverflowTest.d \
./src/json/test/thirdparty/Fuzzer/test/SimpleCmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/SimpleDictionaryTest.d \
./src/json/test/thirdparty/Fuzzer/test/SimpleHashTest.d \
./src/json/test/thirdparty/Fuzzer/test/SimpleTest.d \
./src/json/test/thirdparty/Fuzzer/test/SimpleThreadedTest.d \
./src/json/test/thirdparty/Fuzzer/test/SingleMemcmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/SingleStrcmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/SingleStrncmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/SpamyTest.d \
./src/json/test/thirdparty/Fuzzer/test/StrcmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/StrncmpOOBTest.d \
./src/json/test/thirdparty/Fuzzer/test/StrncmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/StrstrTest.d \
./src/json/test/thirdparty/Fuzzer/test/SwapCmpTest.d \
./src/json/test/thirdparty/Fuzzer/test/Switch2Test.d \
./src/json/test/thirdparty/Fuzzer/test/SwitchTest.d \
./src/json/test/thirdparty/Fuzzer/test/ThreadedLeakTest.d \
./src/json/test/thirdparty/Fuzzer/test/ThreadedTest.d \
./src/json/test/thirdparty/Fuzzer/test/TimeoutEmptyTest.d \
./src/json/test/thirdparty/Fuzzer/test/TimeoutTest.d \
./src/json/test/thirdparty/Fuzzer/test/TraceMallocTest.d \
./src/json/test/thirdparty/Fuzzer/test/UninstrumentedTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/test/thirdparty/Fuzzer/test/%.o: ../src/json/test/thirdparty/Fuzzer/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


