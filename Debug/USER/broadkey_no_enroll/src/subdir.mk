################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/broadkey_no_enroll/src/broadkey_demo_app.c \
../USER/broadkey_no_enroll/src/iid_print.c \
../USER/broadkey_no_enroll/src/iid_usart.c 

OBJS += \
./USER/broadkey_no_enroll/src/broadkey_demo_app.o \
./USER/broadkey_no_enroll/src/iid_print.o \
./USER/broadkey_no_enroll/src/iid_usart.o 

C_DEPS += \
./USER/broadkey_no_enroll/src/broadkey_demo_app.d \
./USER/broadkey_no_enroll/src/iid_print.d \
./USER/broadkey_no_enroll/src/iid_usart.d 


# Each subdirectory must supply rules for building sources it contributes
USER/broadkey_no_enroll/src/%.o: ../USER/broadkey_no_enroll/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DUSE_STDPERIPH_DRIVER -I"C:\broadkey_auth\CORE" -I"C:\broadkey_auth\PERIPHER\Includes" -I"C:\broadkey_auth\SYSTEM" -I"C:\broadkey_auth\USER" -I"C:\broadkey_auth\USER\broadkey_no_enroll\src" -I"C:\broadkey_auth\USER\broadkey_no_enroll\include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


