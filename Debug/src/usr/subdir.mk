################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/usr/configure.cpp \
../src/usr/main.cpp \
../src/usr/my_log.cpp 

OBJS += \
./src/usr/configure.o \
./src/usr/main.o \
./src/usr/my_log.o 

CPP_DEPS += \
./src/usr/configure.d \
./src/usr/main.d \
./src/usr/my_log.d 


# Each subdirectory must supply rules for building sources it contributes
src/usr/%.o: ../src/usr/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/hiredis" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/lib60870" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/log4cplus" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/rapidjson" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/sqlite3" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/tinyxml2" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/uuid" -I"/home/mr/workspace/IEC104Slave@EPC-6Y2C-L/inc/usr" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


