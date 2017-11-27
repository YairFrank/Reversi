################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AIplayer.cpp \
../Board.cpp \
../ConsoleDisplayer.cpp \
../Displayer.cpp \
../GameLogic.cpp \
../Main.cpp \
../Player.cpp \
../ReversieGame.cpp 

OBJS += \
./AIplayer.o \
./Board.o \
./ConsoleDisplayer.o \
./Displayer.o \
./GameLogic.o \
./Main.o \
./Player.o \
./ReversieGame.o 

CPP_DEPS += \
./AIplayer.d \
./Board.d \
./ConsoleDisplayer.d \
./Displayer.d \
./GameLogic.d \
./Main.d \
./Player.d \
./ReversieGame.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


