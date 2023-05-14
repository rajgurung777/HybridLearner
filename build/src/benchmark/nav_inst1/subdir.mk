################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/benchmark/nav_inst1/runNav_inst1.cpp 

OBJS += \
./src/benchmark/nav_inst1/runNav_inst1.o 

CPP_DEPS += \
./src/benchmark/nav_inst1/runNav_inst1.d 


# Each subdirectory must supply rules for building sources it contributes
src/benchmark/nav_inst1/%.o: ../src/benchmark/nav_inst1/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/amit/eclipse-workspace/HybridLearner/src" -I/usr/local/include -I$(MATLAB_INCLUDE_PATH) -O3 -Wall -Wextra -c -fmessage-length=0 -DMATLAB_DEFAULT_RELEASE=R2017b  -DUSE_MEX_CMD   -D_GNU_SOURCE -DMATLAB_MEX_FILE -fexceptions -fno-omit-frame-pointer  -std=c++11 -fwrapv -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


