################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/hybridautomata/hybridAutomata.cpp \
../src/hybridautomata/location.cpp \
../src/hybridautomata/transition.cpp \
../src/hybridautomata/variable_to_index_mapping.cpp 

OBJS += \
./src/hybridautomata/hybridAutomata.o \
./src/hybridautomata/location.o \
./src/hybridautomata/transition.o \
./src/hybridautomata/variable_to_index_mapping.o 

CPP_DEPS += \
./src/hybridautomata/hybridAutomata.d \
./src/hybridautomata/location.d \
./src/hybridautomata/transition.d \
./src/hybridautomata/variable_to_index_mapping.d 


# Each subdirectory must supply rules for building sources it contributes
src/hybridautomata/%.o: ../src/hybridautomata/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I$(MATLAB_INCLUDE_PATH) -O3 -Wall -Wextra -c -fmessage-length=0 -DMATLAB_DEFAULT_RELEASE=R2017b  -DUSE_MEX_CMD   -D_GNU_SOURCE -DMATLAB_MEX_FILE -fexceptions -fno-omit-frame-pointer  -std=c++11 -fwrapv -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


