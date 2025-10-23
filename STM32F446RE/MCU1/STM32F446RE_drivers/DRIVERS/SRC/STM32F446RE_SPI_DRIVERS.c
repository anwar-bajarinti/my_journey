/*
 * STM32F446RE_SPI_DRIVERS.c
 *
 * Created on: Oct 21, 2025
 * Author: notty
 */

// <-- FIX: Corrected include to match the corrected header file name
#include "STM32F446RE_SPI_DRIVERS.h"
// <-- NOTE: "stm32f446re.h" is included via "STM32F446RE_SPI_DRIVERS.h"
//          so it's not strictly needed here, but it doesn't hurt.


/**
 * @brief Enables or disables the peripheral clock for a given SPI port.
 * @param pSPIx: Base address of the SPI peripheral
 * @param EnOrDi: ENABLE or DISABLE macro
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (pSPIx == SPI1)      { SPI1_PCLK_EN(); }
        else if (pSPIx == SPI2) { SPI2_PCLK_EN(); }
        // --- FIX: Corrected typo SPI13 to SPI3 ---
        else if (pSPIx == SPI3) { SPI3_PCLK_EN(); }
        else if (pSPIx == SPI4) { SPI4_PCLK_EN(); }
    }
    else // (EnOrDi == DISABLE)
    {
        // --- FIX: Corrected copy-paste error, was _EN() instead of _DI() ---
        if (pSPIx == SPI1)      { SPI1_PCLK_DI(); }
        else if (pSPIx == SPI2) { SPI2_PCLK_DI(); }
        // --- FIX: Corrected typo SPI13 to SPI3 ---
        else if (pSPIx == SPI3) { SPI3_PCLK_DI(); }
        else if (pSPIx == SPI4) { SPI4_PCLK_DI(); }
    }
}

/**
 * @brief Initializes a given SPI peripheral with the settings in the handle.
 * @param pSPIHandle: Pointer to the SPI Handle structure
 */
// --- FIX: Changed parameter to a pointer (*) to match .h file ---
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
   // --- FIX: Initialize TEMP to 0 to avoid OR-ing with garbage data ---
   uint32_t temp_cr1 = 0; // Temporary register for SPI_CR1

   // 1. Configure Device Mode (Master/Slave)
   // --- FIX: Use variable name 'pSPIHandle' not type 'SPI_Handle_t' ---
   // --- FIX: Use . notation for struct member 'SPI_Config', not -> ---
   temp_cr1 |= pSPIHandle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR;

   // 2. Configure Bus Config (FD, HD, Simplex)
   if(pSPIHandle->SPI_Config.BusConfig == SPI_BUS_CONFIG_FD)
   {
	   // Full-duplex: Clear BIDIMODE bit
	   temp_cr1 &= ~(1 << SPI_CR1_BIDIMODE);
   }
   else if(pSPIHandle->SPI_Config.BusConfig == SPI_BUS_CONFIG_HD)
   {
	   // Half-duplex: Set BIDIMODE bit
	   temp_cr1 |= (1 << SPI_CR1_BIDIMODE);
   }
   else if(pSPIHandle->SPI_Config.BusConfig == SPI_BUS_CONFIG_S_RXONLY)
   {
	   // Simplex RX-Only: Set BIDIMODE and RXONLY bits
	   temp_cr1 |= (1 << SPI_CR1_BIDIMODE);
	   temp_cr1 |= (1 << SPI_CR1_RXONLY);
   }

   // 3. Configure SCLK Speed (Baud Rate)
   temp_cr1 |= (pSPIHandle->SPI_Config.SCLK_Speed << SPI_CR1_BR);

   // 4. Configure DFF (Data Frame Format)
   // --- FIX: Added missing closing parenthesis ')' ---
   temp_cr1 |= (pSPIHandle->SPI_Config.DFF << SPI_CR1_DFF);

   // 5. Configure CPOL
   // --- FIX: Added missing closing parenthesis ')' ---
   temp_cr1 |= (pSPIHandle->SPI_Config.CPOL << SPI_CR1_CPOL);

   // 6. Configure CPHA
   temp_cr1 |= (pSPIHandle->SPI_Config.CPHA << SPI_CR1_CPHA);

   // 7. Configure SSM (Software Slave Management)
   temp_cr1 |= (pSPIHandle->SPI_Config.SSM << SPI_CR1_SSM);

   // 8. Write the final configuration value to the SPI_CR1 register
   // --- FIX: Use variable name 'pSPIHandle' not type 'SPI_Handle_t' ---
   pSPIHandle->pSPIx->SPI_CR1 = temp_cr1;
}

/**
 * @brief De-initializes a given SPI peripheral (not yet implemented).
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx) // <-- NOTE: Renamed from SPI_Dinit
{
    // TODO: Implement this function
    // (Hint: You can use the RCC Reset registers, e.g., SPI1_REG_RESET())
}

/**
 * @brief Gets the status of a specific flag in the SPI_SR register.
 * @param pSPIx: Base address of the SPI peripheral
 * @param FLAG_NAME: The bit position of the flag to check (e.g., SPI_SR_TXE)
 * @return FLAG_SET (1) or FLAG_RESET (0)
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FLAG_NAME)
{
    // --- FIX: Rewrote function to check the specific flag passed in ---
    if (pSPIx->SPI_SR & (1 << FLAG_NAME))
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}

/**
 * @brief Sends data over SPI (blocking call).
 * @param pSPIx: Base address of the SPI peripheral
 * @param pTxBuffer: Pointer to the data buffer to send
 * @param Len: Number of bytes to send
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
   while(Len > 0)
   {
       // 1. Wait until the TXE (Transmit buffer empty) flag is set
	   // --- FIX: Used '==' instead of '===' ---
	   // --- FIX: Used defined bit position 'SPI_SR_TXE' instead of 'TX' ---
	   while(SPI_GetFlagStatus(pSPIx, SPI_SR_TXE) == FLAG_RESET);

	   // 2. Check the DFF bit in SPI_CR1
	   if(pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF))
	   {
		   // 16-bit DFF
		   // Load the 16-bit data into the Data Register
		   pSPIx->SPI_DR = *((uint16_t*)pTxBuffer);
		   // Decrement length by 2 bytes
		   Len -= 2;
		   // Increment the buffer pointer by 2 bytes
		   // --- FIX: Increment pointer by 2 bytes correctly ---
		   pTxBuffer += 2;
	   }
	   else
	   {
		   // 8-bit DFF
		   // Load the 8-bit data into the Data Register
           // --- FIX: Removed extra closing parenthesis ')' ---
		   pSPIx->SPI_DR = *pTxBuffer;
		   // Decrement length by 1 byte
   	   	   Len--;
   	   	   // Increment the buffer pointer by 1 byte
		   pTxBuffer++;
	   }
   }
}

/**
 * @brief Receives data over SPI (blocking call).
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    // TODO: Implement this function
    // (Hint: Similar to SendData, but wait for RXNE flag instead of TXE)
}

/*
 * IRQ (Interrupt) Configuration and Handling
 */
void SPI_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
    // TODO: Implement this function
    // (Hint: Use the NVIC_ISERx and NVIC_ICERx registers)
}
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    // TODO: Implement this function
    // (Hint: Use the NVIC_PR_BASEADDR registers)
}
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
    // TODO: Implement this function
    // (Hint: Check which interrupt flags are set and call user callbacks)
}
