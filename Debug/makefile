################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USER/broadkey_no_enroll/src/subdir.mk
-include USER/subdir.mk
-include SYSTEM/subdir.mk
-include STARTUP/subdir.mk
-include PERIPHER/Sources/subdir.mk
-include CORE/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
broadkey_authentication.bin \

SECONDARY_SIZE += \
broadkey_authentication.siz \


# All Target
all: broadkey_authentication.elf secondary-outputs

# Tool invocations
broadkey_authentication.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "C:\broadkey_auth\gw1ns2k_flash.ld" -Xlinker --gc-sections -L"C:\broadkey_auth\USER\broadkey_no_enroll\lib" -Wl,-Map,"broadkey_authentication.map" -o "broadkey_authentication.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

broadkey_authentication.bin: broadkey_authentication.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "broadkey_authentication.elf"  "broadkey_authentication.bin"
	@echo 'Finished building: $@'
	@echo ' '

broadkey_authentication.siz: broadkey_authentication.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "broadkey_authentication.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) broadkey_authentication.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
