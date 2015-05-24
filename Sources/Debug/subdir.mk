################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board.c \
../button.c \
../collisiondetection.c \
../graphiccomponent.c \
../main.c \
../menu.c \
../pinguin.c \
../render.c 

O_SRCS += \
../board.o \
../button.o \
../collisiondetection.o \
../graphiccomponent.o \
../main.o \
../pinguin.o \
../render.o 

OBJS += \
./board.o \
./button.o \
./collisiondetection.o \
./graphiccomponent.o \
./main.o \
./menu.o \
./pinguin.o \
./render.o 

C_DEPS += \
./board.d \
./button.d \
./collisiondetection.d \
./graphiccomponent.d \
./main.d \
./menu.d \
./pinguin.d \
./render.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


