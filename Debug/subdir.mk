################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AIPlayer.cpp \
../Board.cpp \
../ConsoleDisplayer.cpp \
../Displayer.cpp \
../GameLogic.cpp \
../Main.cpp \
../HumanPlayer.cpp \
../ReversieGame.cpp 

OBJS += \
./AIPlayer.o \
./Board.o \
./ConsoleDisplayer.o \
./Displayer.o \
./GameLogic.o \
./Main.o \
./HumanPlayer.o \
./ReversieGame.o 

CPP_DEPS += \
./AIPlayer.d \
./Board.d \
./ConsoleDisplayer.d \
./Displayer.d \
./GameLogic.d \
./Main.d \
./HumanPlayer.d \
./ReversieGame.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


