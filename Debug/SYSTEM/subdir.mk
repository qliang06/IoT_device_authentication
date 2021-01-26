################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SYSTEM/system_gw1ns2c.c 

OBJS += \
./SYSTEM/system_gw1ns2c.o 

C_DEPS += \
./SYSTEM/system_gw1ns2c.d 


# Each subdirectory must supply rules for building sources it contributes
SYSTEM/%.o: ../SYSTEM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DUSE_STDPERIPH_DRIVER -I"C:\broadkey_auth\CORE" -I"C:\broadkey_auth\PERIPHER\Includes" -I"C:\broadkey_auth\SYSTEM" -I"C:\broadkey_auth\USER" -I"C:\broadkey_auth\USER\broadkey_no_enroll\src" -I"C:\broadkey_auth\USER\broadkey_no_enroll\include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


