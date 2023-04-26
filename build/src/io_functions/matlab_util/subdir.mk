################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/io_functions/matlab_util/matlabPlotter.cpp 

OBJS += \
./src/io_functions/matlab_util/matlabPlotter.o 

CPP_DEPS += \
./src/io_functions/matlab_util/matlabPlotter.d 


# Each subdirectory must supply rules for building sources it contributes
src/io_functions/matlab_util/%.o: ../src/io_functions/matlab_util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/amit/eclipse-workspace/HybridLearner/src" -I/usr/local/MATLAB/R2021a/extern/include -I/usr/local/include -O3 -Wall -Wextra -c -fmessage-length=0 -DMATLAB_DEFAULT_RELEASE=R2017b  -DUSE_MEX_CMD   -D_GNU_SOURCE -DMATLAB_MEX_FILE -fexceptions -fno-omit-frame-pointer  -std=c++11 -fwrapv -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


