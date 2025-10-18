################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DRIVERS/SRC/STM32F446RE_GPIO_DRIVER.c 

OBJS += \
./DRIVERS/SRC/STM32F446RE_GPIO_DRIVER.o 

C_DEPS += \
./DRIVERS/SRC/STM32F446RE_GPIO_DRIVER.d 


# Each subdirectory must supply rules for building sources it contributes
DRIVERS/SRC/%.o DRIVERS/SRC/%.su DRIVERS/SRC/%.cyclo: ../DRIVERS/SRC/%.c DRIVERS/SRC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/SRC" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/Inc" -include"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC/STM32F446RE_GPIO_DRIVER.h" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DRIVERS-2f-SRC

clean-DRIVERS-2f-SRC:
	-$(RM) ./DRIVERS/SRC/STM32F446RE_GPIO_DRIVER.cyclo ./DRIVERS/SRC/STM32F446RE_GPIO_DRIVER.d ./DRIVERS/SRC/STM32F446RE_GPIO_DRIVER.o ./DRIVERS/SRC/STM32F446RE_GPIO_DRIVER.su

.PHONY: clean-DRIVERS-2f-SRC

