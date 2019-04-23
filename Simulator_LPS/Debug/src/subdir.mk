################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/capacity.cpp \
../src/index.cpp \
../src/main.cpp \
../src/mydb.cpp \
../src/request.cpp \
../src/response.cpp \
../src/track.cpp 

OBJS += \
./src/capacity.o \
./src/index.o \
./src/main.o \
./src/mydb.o \
./src/request.o \
./src/response.o \
./src/track.o 

CPP_DEPS += \
./src/capacity.d \
./src/index.d \
./src/main.d \
./src/mydb.d \
./src/request.d \
./src/response.d \
./src/track.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


