################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/utilities/file_operations.cpp \
../src/utilities/intermediateResult.cpp \
../src/utilities/linux_utilities.cpp \
../src/utilities/myRandomNumberGenerator.cpp \
../src/utilities/string_operations.cpp \
../src/utilities/vector_operations.cpp 

OBJS += \
./src/utilities/file_operations.o \
./src/utilities/intermediateResult.o \
./src/utilities/linux_utilities.o \
./src/utilities/myRandomNumberGenerator.o \
./src/utilities/string_operations.o \
./src/utilities/vector_operations.o 

CPP_DEPS += \
./src/utilities/file_operations.d \
./src/utilities/intermediateResult.d \
./src/utilities/linux_utilities.d \
./src/utilities/myRandomNumberGenerator.d \
./src/utilities/string_operations.d \
./src/utilities/vector_operations.d 


# Each subdirectory must supply rules for building sources it contributes
src/utilities/%.o: ../src/utilities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/amit/eclipse-workspace/HybridLearner/src" -I/usr/local/MATLAB/R2021a/extern/include -I/usr/local/include -O3 -Wall -Wextra -c -fmessage-length=0 -DMATLAB_DEFAULT_RELEASE=R2017b  -DUSE_MEX_CMD   -D_GNU_SOURCE -DMATLAB_MEX_FILE -fexceptions -fno-omit-frame-pointer  -std=c++11 -fwrapv -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


