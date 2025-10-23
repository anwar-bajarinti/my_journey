/*
 * 005SPI_TX_Testing.c
 *
 * Created on: Oct 23, 2025
 * Author: notty
 */

/*
 * Pinout for this test (SPI2 on AF5):
 *
 * PB12 - SPI2_NSS
 * PB13 - SPI2_SCLK
 * PB14 - SPI2_MISO
 * PB15 - SPI2_MOSI
 *
 * Alternate Function Mode: AF5
 */


// <-- FIX: Removed redundant include. "STM32F446RE_SPI_DRIVERS.h" already includes "stm32f446re.h"
// #include "stm32f446re.h"
// <-- NOTE: Assuming your GPIO driver header is named this.
//          This file is required for GPIO_Handle_t and GPIO_Init.
#include "STM32F446RE_GPIO_DRIVERS.h" // You will need to include your GPIO driver header
#include "STM32F446RE_SPI_DRIVERS.h"


/**
 * @brief Initializes the GPIO pins required for SPI2.
 */
void SPI_GPIO_Init(void)
{
    // NOTE: 'GPIO_Handle_t' is a struct, not a pointer.
    // We create an instance of it on the stack.
	GPIO_Handle_t SPIPins;

    // --- FIX: Use . (dot) to access members of a struct variable ---
	SPIPins.pGPIOx = GPIOB; // All pins are on GPIOB

    // --- FIX: Use . (dot) to access members of an embedded struct ---
	// --- FIX: Mode must be Alternate Function (AF) for SPI, not Output (OUT) ---
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_AF; // Set mode to Alternate Function
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;      // Set Alternate Function to AF5 (for SPI2)
	SPIPins.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP; // Output type Push-Pull
	SPIPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NO_PUPD; // No pull-up or pull-down
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST; // Fast speed

	// Configure PB12 (SPI2_NSS)
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins); // Pass a pointer to the handle struct

	// Configure PB13 (SPI2_SCLK)
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	// Configure PB14 (SPI2_MISO)
    // NOTE: Even for TX-only, MISO should be configured.
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	// Configure PB15 (SPI2_MOSI)
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);
}

/**
 * @brief Initializes the SPI2 peripheral.
 */
void SPI2_Init(void)
{
    SPI_Handle_t SPI2Handle;

    SPI2Handle.pSPIx = SPI2; // Set the peripheral to SPI2
    SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2Handle.SPI_Config.BusConfig = SPI_BUS_CONFIG_FD; // Full Duplex
    SPI2Handle.SPI_Config.SCLK_Speed = SPI_SCLK_SPEED_DIV2; // SCLK = PCLK / 2
    SPI2Handle.SPI_Config.DFF = SPI_DFF_8BITS;
    SPI2Handle.SPI_Config.CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPI_Config.CPHA = SPI_CPHA_LOW;
    SPI2Handle.SPI_Config.SSM = SPI_SSM_EN; // Software Slave Management enabled

    SPI_Init(&SPI2Handle);
}

int main(void)
{
    char user_data[] = "Hello world";

	// 1. Initialize GPIO pins for SPI
	SPI_GPIO_Init();

    // 2. Initialize SPI2 peripheral configuration
    SPI2_Init();

    // 3. Enable the SPI peripheral (Set SPE bit in CR1)
    // This is often done *after* init, just before transmission.
    SPI_PeripheralControl(SPI2, ENABLE); // <-- NOTE: You'll need to create this function

    // 4. Send data
    SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

    // 5. Wait until SPI is not busy before disabling
    while(SPI_GetFlagStatus(SPI2, SPI_SR_BSY));

    // 6. Disable the SPI peripheral
    SPI_PeripheralControl(SPI2, DISABLE);


	while(1); // Infinite loop
}
