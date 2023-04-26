################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/utilities/polytope/subdir.mk
-include src/utilities/math/numeric/subdir.mk
-include src/utilities/math/subdir.mk
-include src/utilities/hyperbox/subdir.mk
-include src/utilities/subdir.mk
-include src/simulinkModelling/subdir.mk
-include src/simulation/subdir.mk
-include src/modelParser/subdir.mk
-include src/learningHA/subdir.mk
-include src/io_functions/matlab_util/subdir.mk
-include src/io_functions/subdir.mk
-include src/hybridautomata/subdir.mk
-include src/dReachModelling/subdir.mk
-include src/core_engine/simulation/subdir.mk
-include src/core_engine/model_translator/subdir.mk
-include src/core_engine/learn_ha/subdir.mk
-include src/core_engine/equivalence_testing/subdir.mk
-include src/commandLineParser/subdir.mk
-include src/benchmark/shared_gas_burner/subdir.mk
-include src/benchmark/oscillator/subdir.mk
-include src/benchmark/nav_inst1/subdir.mk
-include src/benchmark/circle/subdir.mk
-include src/benchmark/bball_with_input/subdir.mk
-include src/benchmark/AT/subdir.mk
-include src/benchmark/AFC/subdir.mk
-include src/benchmark/subdir.mk
-include src/application/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: HybridLearner

# Tool invocations
HybridLearner: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -Wl,--no-undefined "/usr/local/MATLAB/R2021a/sys/os/glnxa64/orig/libstdc++.so.6"   -Wl,--as-needed -Wl,-rpath-link,/usr/local/MATLAB/R2021a/extern/bin/glnxa64 -Wl,-rpath-link,/usr/local/MATLAB/R2021a/bin/glnxa64 -L/usr/local/MATLAB/R2021a/extern/bin/glnxa64 -L/usr/local/lib -L/usr/local/MATLAB/R2021a/bin/glnxa64 -L/usr/local/MATLAB/R2021a/extern/lib/glnxa64 -pthread -o "HybridLearner" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) HybridLearner
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
