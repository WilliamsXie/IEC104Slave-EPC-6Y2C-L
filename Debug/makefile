################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/usr/subdir.mk
-include src/tinyxml2/subdir.mk
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
all: IEC104Slave-EPC-6Y2C-L

# Tool invocations
IEC104Slave-EPC-6Y2C-L: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"/home/xie/workspace/IEC104Slave-EPC-6Y2C-L/lib/linux/hiredis" -L"/home/xie/workspace/IEC104Slave-EPC-6Y2C-L/lib/linux/lib60870" -L"/home/xie/workspace/IEC104Slave-EPC-6Y2C-L/lib/linux/log4cplus" -L"/home/xie/workspace/IEC104Slave-EPC-6Y2C-L/lib/linux/sqlite3" -L"/home/xie/workspace/IEC104Slave-EPC-6Y2C-L/lib/linux/uuid" -Lcrypto -o "IEC104Slave-EPC-6Y2C-L" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) IEC104Slave-EPC-6Y2C-L
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
