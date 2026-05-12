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

// <-- FIX: Corrected typo in filename (was ..._DRIVERS.h)
#include "STM32F446RE_GPIO_DRIVER.h"
#include "STM32F446RE_SPI_DRIVERS.h"
#include <string.h> // <-- FIX: Added for strlen()

/**
 * @brief Initializes the GPIO pins required for SPI2.
 */
void SPI_GPIO_Init(void)
{  SPI2_PCLK_EN();
    // --- FIX: 'SPIPins' must be a local variable, NOT a pointer.
    //          Declaring 'GPIO_Handle_t *SPIPins' creates an
    //          uninitialized pointer, which will cause a crash.
	GPIO_Handle_t SPIPins;

    // --- FIX: Use . (dot) to access members of a struct variable ---
	SPIPins.pGPIOx = GPIOB; // All pins are on GPIOB

    // --- FIX: Use . (dot) to access members of an embedded struct ---
	// --- FIX: Mode must be Alternate Function (AF) for SPI, not Output (OUT) ---
	SPIPins.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODE_ALTFN; // Set mode to Alternate Function
	SPIPins.GPIO_Pin_Config.GPIO_PinAltFunMode = 5;       // Set Alternate Function to AF5 (for SPI2)
	SPIPins.GPIO_Pin_Config.GPIO_PinOpType = GPIO_OP_TYPE_PP;  // Output type Push-Pull
	SPIPins.GPIO_Pin_Config.GPIO_PinPupdControl = GPIO_NO_PUPD; // No pull-up or pull-down
	SPIPins.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_SPEED_FAST;  // Fast speed

	// Configure PB12 (SPI2_NSS)
    // NOTE: In SSM=1 mode, NSS is not strictly needed, but good to configure.
	SPIPins.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins); // --- FIX: Pass a pointer to the handle struct ---

	// Configure PB13 (SPI2_SCLK)
	SPIPins.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	// Configure PB14 (SPI2_MISO)
    // NOTE: Not used in TX-only, but good practice to configure.
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
    // This must be done *after* init, just before transmission.
    // <-- FIX: Pass SPI2 (the register pointer) not the handle
    SPI_PeripheralControl(SPI2, ENABLE);
    SPI_SSIControl(SPI2, ENABLE);

    // 4. Send data
    // <-- FIX: Pass SPI2 (the register pointer) not the handle
    SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

    // 5. Wait until SPI is not busy before disabling
    while(SPI_GetFlagStatus(SPI2, SPI_SR_BSY) == FLAG_SET);

    // 6. Disable the SPI peripheral
    SPI_PeripheralControl(SPI2, DISABLE);



	while(1); // Infinite loop
}
