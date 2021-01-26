################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/gw1ns2c_it.c \
../USER/led.c \
../USER/main.c \
../USER/printf.c \
../USER/uart_test.c 

OBJS += \
./USER/gw1ns2c_it.o \
./USER/led.o \
./USER/main.o \
./USER/printf.o \
./USER/uart_test.o 

C_DEPS += \
./USER/gw1ns2c_it.d \
./USER/led.d \
./USER/main.d \
./USER/printf.d \
./USER/uart_test.d 


# Each subdirectory must supply rules for building sources it contributes
USER/%.o: ../USER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DUSE_STDPERIPH_DRIVER -I"C:\broadkey_auth\CORE" -I"C:\broadkey_auth\PERIPHER\Includes" -I"C:\broadkey_auth\SYSTEM" -I"C:\broadkey_auth\USER" -I"C:\broadkey_auth\USER\broadkey_no_enroll\src" -I"C:\broadkey_auth\USER\broadkey_no_enroll\include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


