################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/005SPI_TX_Testing.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/005SPI_TX_Testing.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/005SPI_TX_Testing.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC/STM32F446RE_SPI_DRIVERS.h" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC/STM32F446RE_SPI_DRIVERS.h" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/SRC" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS" -I"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/Inc" -include"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC/STM32F446RE_SPI_DRIVERS.h" -include"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC/STM32F446RE_SPI_DRIVERS.h" -include"E:/all files/FUTURE/GIT HUB/my_journey/STM32F446RE/MCU1/STM32F446RE_drivers/DRIVERS/INC/STM32F446RE_GPIO_DRIVER.h" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/005SPI_TX_Testing.cyclo ./Src/005SPI_TX_Testing.d ./Src/005SPI_TX_Testing.o ./Src/005SPI_TX_Testing.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

