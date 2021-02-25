################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tinyxml2/tinyxml2.cpp 

OBJS += \
./src/tinyxml2/tinyxml2.o 

CPP_DEPS += \
./src/tinyxml2/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/tinyxml2/%.o: ../src/tinyxml2/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/hiredis" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/lib60870" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/log4cplus" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/rapidjson" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/sqlite3" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/tinyxml2" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/uuid" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/usr" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


