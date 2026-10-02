################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LED_Blink.c \
../Src/stm32f407_gpio.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/LED_Blink.o \
./Src/stm32f407_gpio.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/LED_Blink.d \
./Src/stm32f407_gpio.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/LED_Blink.cyclo ./Src/LED_Blink.d ./Src/LED_Blink.o ./Src/LED_Blink.su ./Src/stm32f407_gpio.cyclo ./Src/stm32f407_gpio.d ./Src/stm32f407_gpio.o ./Src/stm32f407_gpio.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

