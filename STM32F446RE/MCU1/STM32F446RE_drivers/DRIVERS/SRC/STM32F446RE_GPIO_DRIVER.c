/*
 * STM32F446RE_GPIO_DRIVER.c
 *
 * Created on: Oct 14, 2025
 * Author: notty
 */

#include "STM32F446RE_GPIO_DRIVER.h"

// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_Reg_Def *pGPIOX, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (pGPIOX == GPIOA) { GPIOA_PCLK_EN(); }
        else if (pGPIOX == GPIOB) { GPIOB_PCLK_EN(); }
        else if (pGPIOX == GPIOC) { GPIOC_PCLK_EN(); }
        else if (pGPIOX == GPIOD) { GPIOD_PCLK_EN(); }
        else if (pGPIOX == GPIOE) { GPIOE_PCLK_EN(); }
        else if (pGPIOX == GPIOF) { GPIOF_PCLK_EN(); }
        else if (pGPIOX == GPIOG) { GPIOG_PCLK_EN(); }
        else if (pGPIOX == GPIOH) { GPIOH_PCLK_EN(); }
    }
    else
    {
        if (pGPIOX == GPIOA) { GPIOA_PCLK_DI(); }
        // Add other disable cases if needed
    }
}

// Init and De-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    // 1. Configure the mode of the pin
    if (pGPIOHandle->GPIO_Pin_Config.GPIO_PiMode <= GPIO_MODE_ANALOG)
    {
        temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PiMode << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
        pGPIOHandle->pGPIOX->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber)); // Clear bits
        pGPIOHandle->pGPIOX->MODER |= temp; // Set bits
    }
    else
    {
        // Interrupt mode configuration would go here
    }

    // 2. Configure the speed
    temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    pGPIOHandle->pGPIOX->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    pGPIOHandle->pGPIOX->OSPEEDR |= temp;

    // 3. Configure the pupd settings
    temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinPupdControl << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    pGPIOHandle->pGPIOX->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber));
    pGPIOHandle->pGPIOX->PUPDR |= temp;

    // 4. Configure the output type
    temp = (pGPIOHandle->GPIO_Pin_Config.GPIO_PinOpType << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
    pGPIOHandle->pGPIOX->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber);
    pGPIOHandle->pGPIOX->OTYPER |= temp;

    // 5. Configure the alternate functionality
    if (pGPIOHandle->GPIO_Pin_Config.GPIO_PiMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1, temp2;
        temp1 = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_Pin_Config.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOX->AFR[temp1] &= ~(0xF << (4 * temp2));
        pGPIOHandle->pGPIOX->AFR[temp1] |= (pGPIOHandle->GPIO_Pin_Config.GPIO_PinAltFunMode << (4 * temp2));
    }
}

void GPIO_DeInit(GPIO_Reg_Def *pGPIOX)
{
    if (pGPIOX == GPIOA) { GPIOA_REG_RESET(); }
    else if (pGPIOX == GPIOB) { GPIOB_REG_RESET(); }
    else if (pGPIOX == GPIOC) { GPIOC_REG_RESET(); }
    else if (pGPIOX == GPIOD) { GPIOD_REG_RESET(); }
    else if (pGPIOX == GPIOE) { GPIOE_REG_RESET(); }
    else if (pGPIOX == GPIOF) { GPIOF_REG_RESET(); }
    else if (pGPIOX == GPIOG) { GPIOG_REG_RESET(); }
    else if (pGPIOX == GPIOH) { GPIOH_REG_RESET(); }
}

// Data Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_Reg_Def *pGPIOX, uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t)((pGPIOX->IDR >> PinNumber) & 0x00000001);
    return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_Reg_Def *pGPIOX)
{
    return (uint16_t)pGPIOX->IDR;
}

void GPIO_WriteToOutputPin(GPIO_Reg_Def *pGPIOX, uint8_t PinNumber, uint8_t Value)
{
    if (Value == GPIO_PIN_SET)
    {
        pGPIOX->ODR |= (1 << PinNumber);
    }
    else
    {
        pGPIOX->ODR &= ~(1 << PinNumber);
    }
}

void GPIO_WriteToOutputPort(GPIO_Reg_Def *pGPIOX, uint16_t Value)
{
    pGPIOX->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_Reg_Def *pGPIOX, uint8_t PinNumber)
{
    pGPIOX->ODR ^= (1 << PinNumber);
}
