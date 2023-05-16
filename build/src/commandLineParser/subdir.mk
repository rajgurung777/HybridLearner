################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/commandLineParser/commandLineParser.cpp \
../src/commandLineParser/parameters.cpp \
../src/commandLineParser/user_inputs.cpp \
../src/commandLineParser/user_inputs_helper.cpp 

OBJS += \
./src/commandLineParser/commandLineParser.o \
./src/commandLineParser/parameters.o \
./src/commandLineParser/user_inputs.o \
./src/commandLineParser/user_inputs_helper.o 

CPP_DEPS += \
./src/commandLineParser/commandLineParser.d \
./src/commandLineParser/parameters.d \
./src/commandLineParser/user_inputs.d \
./src/commandLineParser/user_inputs_helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/commandLineParser/%.o: ../src/commandLineParser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I$(MATLAB_INCLUDE_PATH) -O3 -Wall -Wextra -c -fmessage-length=0 -DMATLAB_DEFAULT_RELEASE=R2017b  -DUSE_MEX_CMD   -D_GNU_SOURCE -DMATLAB_MEX_FILE -fexceptions -fno-omit-frame-pointer  -std=c++11 -fwrapv -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


