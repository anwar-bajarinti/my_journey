/*
 * 006SPI_TX_ARDUINO.c
 *
 * Created on: Oct 28, 2025
 * Author: notty
 */
#include "STM32F446RE_GPIO_DRIVER.h"
#include "STM32F446RE_SPI_DRIVERS.h"
#include <string.h>

void delay(void)
{
    // Simple delay for logic analyzer
    for(uint32_t i = 0; i < 500000; i++);
}

/**
 * @brief Initializes the GPIO pins required for SPI2.
 */
void SPI_GPIO_Init(void)
{
    // --- FIX: Enable the GPIOB clock ---
    GPIOB_PCLK_EN();

	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_Pin_Config.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_Pin_Config.GPIO_PinOpType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_Pin_Config.GPIO_PinPupdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Configure PB12 (SPI2_NSS)
	SPIPins.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);

	// Configure PB13 (SPI2_SCLK)
	SPIPins.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	// Configure PB14 (SPI2_MISO)
	SPIPins.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	// Configure PB15 (SPI2_MOSI)
	SPIPins.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);
}

/**
 * @brief Initializes the SPI2 peripheral.
 */
void SPI2_Init(void)
{
    // --- FIX: Enable the SPI2 clock ---
    SPI2_PCLK_EN();

    SPI_Handle_t SPI2Handle;

    SPI2Handle.pSPIx = SPI2;
    SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2Handle.SPI_Config.BusConfig = SPI_BUS_CONFIG_FD;
    SPI2Handle.SPI_Config.SCLK_Speed = SPI_SCLK_SPEED_DIV2;
    SPI2Handle.SPI_Config.DFF = SPI_DFF_8BITS;
    SPI2Handle.SPI_Config.CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPI_Config.CPHA = SPI_CPHA_LOW;
    SPI2Handle.SPI_Config.SSM = SPI_SSM_EN;

    SPI_Init(&SPI2Handle);
}

int main(void)
{
    char user_data[] = "Hello world";
    uint32_t data_len = strlen(user_data);

	// 1. Initialize GPIO pins for SPI
	SPI_GPIO_Init();

    // 2. Initialize SPI2 peripheral configuration
    SPI2_Init();

    // 3. Enable the SPI peripheral (Set SPE bit in CR1)
    SPI_SSIControl(SPI2, ENABLE);
    SPI_PeripheralControl(SPI2, ENABLE);


	while(1)
    {
        // 4. Send data
        SPI_SendData(SPI2, (uint8_t*)user_data, data_len);

        // 5. Add a delay so we can see the gaps in the logic analyzer
        delay();
    }
}
