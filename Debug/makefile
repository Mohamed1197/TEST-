################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/MWDT/subdir.mk
-include MCAL/MTimers/subdir.mk
-include MCAL/MGI/subdir.mk
-include MCAL/MEXTI/subdir.mk
-include MCAL/MDIO/subdir.mk
-include MCAL/MADC/subdir.mk
-include HAL/HTMP/subdir.mk
-include HAL/HSTP/subdir.mk
-include HAL/HSRV/subdir.mk
-include HAL/HLED/subdir.mk
-include HAL/HLDR/subdir.mk
-include HAL/HLCD/subdir.mk
-include HAL/HKPD/subdir.mk
-include HAL/H7SEG/subdir.mk
-include HAL/DCMTR/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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
LSS += \
TTTTTEEESSSSSTTTTT.lss \

FLASH_IMAGE += \
TTTTTEEESSSSSTTTTT.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: TTTTTEEESSSSSTTTTT.elf secondary-outputs

# Tool invocations
TTTTTEEESSSSSTTTTT.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,TTTTTEEESSSSSTTTTT.map -mmcu=atmega32 -o "TTTTTEEESSSSSTTTTT.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TTTTTEEESSSSSTTTTT.lss: TTTTTEEESSSSSTTTTT.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TTTTTEEESSSSSTTTTT.elf  >"TTTTTEEESSSSSTTTTT.lss"
	@echo 'Finished building: $@'
	@echo ' '

TTTTTEEESSSSSTTTTT.hex: TTTTTEEESSSSSTTTTT.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex TTTTTEEESSSSSTTTTT.elf  "TTTTTEEESSSSSTTTTT.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TTTTTEEESSSSSTTTTT.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t TTTTTEEESSSSSTTTTT.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) TTTTTEEESSSSSTTTTT.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
