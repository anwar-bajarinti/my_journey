/**
 ******************************************************************************
 * @file           : STM32F446RE_GPIO_DRIVER.c
 * @author         : notty
 * @brief          : GPIO Driver Implementation File
 * @date           : Created on: Oct 14, 2025
 ******************************************************************************
 */

#include "STM32F446RE_GPIO_DRIVER.h"

/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for a given GPIO port
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral (e.g., GPIOA, GPIOB)
 * @param[in]         - EnOrDi: ENABLE or DISABLE macros
 *
 * @return            - none
 */
void GPIO_PeriClockControl(GPIO_RegDef *pGPIOx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (pGPIOx == GPIOA) { GPIOA_PCLK_EN(); }
        else if (pGPIOx == GPIOB) { GPIOB_PCLK_EN(); }
        else if (pGPIOx == GPIOC) { GPIOC_PCLK_EN(); }
        else if (pGPIOx == GPIOD) { GPIOD_PCLK_EN(); }
        else if (pGPIOx == GPIOE) { GPIOE_PCLK_EN(); }
        else if (pGPIOx == GPIOF) { GPIOF_PCLK_EN(); }
        else if (pGPIOx == GPIOG) { GPIOG_PCLK_EN(); }
        else if (pGPIOx == GPIOH) { GPIOH_PCLK_EN(); }
    }
    else
    {
        if (pGPIOx == GPIOA) { GPIOA_PCLK_DI(); }
        else if (pGPIOx == GPIOB) { GPIOB_PCLK_DI(); }
        else if (pGPIOx == GPIOC) { GPIOC_PCLK_DI(); }
        else if (pGPIOx == GPIOD) { GPIOD_PCLK_DI(); }
        else if (pGPIOx == GPIOE) { GPIOE_PCLK_DI(); }
        else if (pGPIOx == GPIOF) { GPIOF_PCLK_DI(); }
        else if (pGPIOx == GPIOG) { GPIOG_PCLK_DI(); }
        else if (pGPIOx == GPIOH) { GPIOH_PCLK_DI(); }
    }
}

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function initializes a GPIO pin based on the settings
 * - in the GPIO_Handle_t structure.
 *
 * @param[in]         - pGPIOHandle: Pointer to a GPIO_Handle_t structure that
 * - contains the configuration information.
 *
 * @return            - none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0; // Temporary register variable

    // 0. Enable the peripheral clock before configuring registers
    // <-- NOTE: This is a good practice, though you might do it just once
    //          outside this function before initializing multiple pins.
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    // 1. Configure the mode of the pin
    // <-- FIX: Changed 'GPIO_PiMode' to 'GPIO_PinMode' to match corrected header.
    if (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        // Non-interrupt modes (Input, Output, Analog, AF)
        temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
        // <-- FIX: Changed 'pGPIOX' to 'pGPIOx' (lowercase) to match corrected header.
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber)); // Clear bits
        pGPIOHandle->pGPIOx->MODER |= temp; // Set bits
    }
    else
    {
        /*
         * This is an interrupt mode.
         * 1. Configure the edge trigger (FTSR, RTSR).
         * 2. Configure the GPIO port selection in SYSCFG_EXTICR (CRITICAL!).
         * 3. Enable the interrupt delivery from EXTI to NVIC (IMR).
         */

        // 1. Configure the edge trigger
        // <-- FIX: Changed 'GPIO_PiMode' to 'GPIO_PinMode'
        if (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
        	// Configure the FTSR (Falling Trigger Selection Register)
        	EXTI->FTSR |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
            // Clear the corresponding RTSR bit to be safe
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
        }
        // <-- FIX: Changed 'GPIO_PiMode' to 'GPIO_PinMode'
        else if (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
        	// Configure the RTSR (Rising Trigger Selection Register)
        	EXTI->RTSR |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
            // Clear the corresponding FTSR bit
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
        }
        // <-- FIX: Changed 'GPIO_PiMode' to 'GPIO_PinMode'
        else if (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
        	// Configure both FTSR and RTSR
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
        	EXTI->RTSR |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
        }

        // 2. Configure the GPIO port selection in SYSCFG_EXTICR
        // (1) Get the port code (A=0, B=1, etc.)
        // <-- FIX: Changed 'pGPIOX' to 'pGPIOx'
         uint8_t portCode = GPIO_BASEADDR_TO_PORTCODE(pGPIOHandle->pGPIOx);

        // (2) Enable SYSCFG clock
         SYSCFG_PCLK_EN();

        // (3) Configure the correct EXTICR register
         uint8_t reg_idx = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber / 4;
         uint8_t pin_idx = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber % 4;

         // <-- NOTE: This logic is correct, good job.
         SYSCFG->EXTICR[reg_idx] &= ~(0xF << (4 * pin_idx)); // Clear
         SYSCFG->EXTICR[reg_idx] |= (portCode << (4 * pin_idx)); // Set


        // 3. Enable the EXTI interrupt delivery using IMR (Interrupt Mask Register)
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
    }

    // 2. Configure the speed
    temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    // <-- FIX: Changed 'pGPIOX' to 'pGPIOx'
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    // 3. Configure the pupd settings
    temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinPupdControl << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    // <-- FIX: Changed 'pGPIOX' to 'pGPIOx'
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    // 4. Configure the output type
    temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinOpType << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
    // <-- FIX: Changed 'pGPIOX' to 'pGPIOx'
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    // 5. Configure the alternate functionality
    // <-- FIX: Changed 'GPIO_PiMode' to 'GPIO_PinMode'
    if (pGPIOHandle->GPIO_Pin_Config.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1, temp2;

        // <-- NOTE: This logic for AFR[0] vs AFR[1] is correct.
        temp1 = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber / 8; // Chooses AFR[0] or AFR[1]
        temp2 = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber % 8; // Chooses bit offset in that register

        // <-- FIX: Changed 'pGPIOX' to 'pGPIOx'
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); // Clear 4 bits
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_Pin_Config.GPIO_PinAltFunMode << (4 * temp2)); // Set 4 bits
    }
}

/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             - This function resets all registers for a given GPIO port
 * - back to their default values using the RCC reset register.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral
 *
 * @return            - none
 */
void GPIO_DeInit(GPIO_RegDef *pGPIOx)
{
    if (pGPIOx == GPIOA) { GPIOA_REG_RESET(); }
    else if (pGPIOx == GPIOB) { GPIOB_REG_RESET(); }
    else if (pGPIOx == GPIOC) { GPIOC_REG_RESET(); }
    else if (pGPIOx == GPIOD) { GPIOD_REG_RESET(); }
    else if (pGPIOx == GPIOE) { GPIOE_REG_RESET(); }
    else if (pGPIOx == GPIOF) { GPIOF_REG_RESET(); }
    else if (pGPIOx == GPIOG) { GPIOG_REG_RESET(); }
    else if (pGPIOx == GPIOH) { GPIOH_REG_RESET(); }
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             - Reads the logical state of a single input pin
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral
 * @param[in]         - PinNumber: The pin number to read (0-15)
 *
 * @return            - 0 or 1 (uint8_t)
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    // Shift the bit to the 0th position and mask it
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
    return value;
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             - Reads the 16-bit value from the entire port's Input Data Register
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral
 *
 * @return            - 16-bit value of the IDR (uint16_t)
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef *pGPIOx)
{
    // The IDR is 32-bits, but only the lower 16 are used for pins.
    return (uint16_t)pGPIOx->IDR;
}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             - Writes a logical state (SET or RESET) to a single output pin
 * @note              - This function uses the BSRR for atomic bit-setting/resetting.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral
 * @param[in]         - PinNumber: The pin number to write to (0-15)
 * @param[in]         - Value: GPIO_PIN_SET or GPIO_PIN_RESET
 *
 * @return            - none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if (Value == GPIO_PIN_SET)
    {
        // Set the pin: Write to the lower 16 bits of BSRR
        pGPIOx->BSRR = (1 << PinNumber);
    }
    else
    {
        // Reset the pin: Write to the upper 16 bits of BSRR
        pGPIOx->BSRR = (1 << (PinNumber + 16));
    }
}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPort
 *
 * @brief             - Writes a 16-bit value to the entire port's Output Data Register
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral
 * @param[in]         - Value: The 16-bit value to write to the port
 *
 * @return            - none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef *pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value;
}

/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             - Toggles the current state of a single output pin
 * @note              - This uses the ODR, as BSRR cannot toggle.
 *
 * @param[in]         - pGPIOx: Base address of the GPIO peripheral
 * @param[in]         - PinNumber: The pin number to toggle (0-15)
 *
 * @return            - none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef *pGPIOx, uint8_t PinNumber)
{
    // The XOR (^) operator is perfect for toggling a bit
    pGPIOx->ODR ^= (1 << PinNumber);
}

/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             - Enables or Disables a given IRQ number in the NVIC
 *
 * @param[in]         - IRQNumber: The IRQ number (e.g., 6 for EXTI0)
 * @param[in]         - EnOrDi: ENABLE or DISABLE
 *
 * @return            - none
 */
// <-- FIX: Removed IRQPriority, it doesn't belong in this function.
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// Program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );
		}
		// <-- FIX: Corrected syntax error (removed duplicate 'else if')
		// <-- FIX: Added correct logic for ISER1
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// Program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		// <-- FIX: Fixed typo 'RQNumber' to 'IRQNumber'
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			// Program ISER2 register
			*NVIC_ISER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
	else // (EnOrDi == DISABLE)
	{
		if(IRQNumber <= 31)
		{
			// <-- FIX: Use ICER (Interrupt Clear-Enable Register) to disable
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// <-- FIX: Use ICER1
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			// <-- FIX: Use ICER2
			// <-- FIX: Fixed typo 'RQNumber' to 'IRQNumber' (in my head, you didn't have it here)
			*NVIC_ICER2 |= ( 1 << (IRQNumber % 64) );
		}
	}
}

/*********************************************************************
 * @fn      		  - GPIO_IRQPriorityConfig
 *
 * @brief             - Configures the priority of a given IRQ number
 *
 * @param[in]         - IRQNumber: The IRQ number (e.g., 6 for EXTI0)
 * @param[in]         - IRQPriority: The priority value (0-15 for STM32F4)
 *
 * @return            - none
 */
// <-- FIX: Swapped IRQPriority and IRQNumber to be more logical
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    // <-- FIX: Logic was incorrect. We find the register and section
    //          using the IRQNumber, not the IRQPriority.
	// 1. Find the IPR register (IPR0, IPR1, etc.)
	uint8_t IPR_reg_idx = IRQNumber / 4;
    // 2. Find the 8-bit section within that register
	uint8_t IPR_section_idx = IRQNumber % 4;

    // <-- FIX: Priority bits are in the *upper* 4 bits of the 8-bit field.
    //          We need to shift the priority value left.
	uint8_t shift_amount = ( 8 * IPR_section_idx ) + ( 8 - NO_OF_PR_BITS_IMPLEMENTED );

    // <-- FIX: Pointer arithmetic syntax was wrong (IPR_reg*).
    //          Also, we must clear the old priority first.
    // (NVIC_PR_BASEADDR) points to the start of IPR0.
    // (NVIC_PR_BASEADDR + IPR_reg_idx) moves the pointer to the correct IPR register.
    volatile uint32_t* priority_reg = (NVIC_PR_BASEADDR + IPR_reg_idx);

    // Clear the 8-bit priority field first
    *priority_reg &= ~( 0xFF << shift_amount );

    // Set the new priority
    // We shift the 4-bit priority value to align it to the left
    // of the 8-bit field.
	*priority_reg |= ( (uint32_t)IRQPriority << shift_amount );
}

/*********************************************************************
 * @fn      		  - GPIO_IRQHandling
 *
 * @brief             - Clears the EXTI pending bit for a given pin.
 * @note              - This should be called inside your ISR.
 *
 * @param[in]         - PinNumber: The pin number (0-15) that triggered
 *
 * @return            - none
 */
// <-- FIX: Changed signature to use 'PinNumber'
void GPIO_IRQHandling(uint8_t PinNumber)
{
    // <-- FIX: Check the pending register (PR) for the correct pin
	if(EXTI->PR & (1 << PinNumber))
	{
        // <-- FIX: Clear the pending bit by *writing 1* to it.
        //          Using '|= 1' will not work and is a common bug.
        //          You must write the bit to 1 to clear it.
		EXTI->PR = (1 << PinNumber);
	}
}
