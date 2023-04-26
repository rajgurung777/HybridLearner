################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tester/UnitTesting_application/test_application_engine_equivalenceTesting.cpp \
../src/tester/UnitTesting_application/test_application_engine_learnHA.cpp \
../src/tester/UnitTesting_application/test_application_engine_learnHALoop.cpp \
../src/tester/UnitTesting_application/test_application_engine_simulation.cpp \
../src/tester/UnitTesting_application/test_application_engine_txt2slx.cpp 

OBJS += \
./src/tester/UnitTesting_application/test_application_engine_equivalenceTesting.o \
./src/tester/UnitTesting_application/test_application_engine_learnHA.o \
./src/tester/UnitTesting_application/test_application_engine_learnHALoop.o \
./src/tester/UnitTesting_application/test_application_engine_simulation.o \
./src/tester/UnitTesting_application/test_application_engine_txt2slx.o 

CPP_DEPS += \
./src/tester/UnitTesting_application/test_application_engine_equivalenceTesting.d \
./src/tester/UnitTesting_application/test_application_engine_learnHA.d \
./src/tester/UnitTesting_application/test_application_engine_learnHALoop.d \
./src/tester/UnitTesting_application/test_application_engine_simulation.d \
./src/tester/UnitTesting_application/test_application_engine_txt2slx.d 


# Each subdirectory must supply rules for building sources it contributes
src/tester/UnitTesting_application/%.o: ../src/tester/UnitTesting_application/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/amit/eclipse-workspace/HybridLearner/src" -I/usr/local/MATLAB/R2021a/extern/include -I/usr/local/include -O3 -Wall -Wextra -c -fmessage-length=0 -DMATLAB_DEFAULT_RELEASE=R2017b  -DUSE_MEX_CMD   -D_GNU_SOURCE -DMATLAB_MEX_FILE -fexceptions -fno-omit-frame-pointer  -std=c++11 -fwrapv -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


