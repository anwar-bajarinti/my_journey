/*
 * STM32F446RE_GPIO_DRIVER.h
 *
 * Created on: Oct 14, 2025
 * Author: notty
 */

#ifndef INC_STM32F446RE_GPIO_DRIVER_H_
#define INC_STM32F446RE_GPIO_DRIVER_H_

// <-- NOTE: This include is correct. The driver header includes the MCU header.
#include "STM32F446RE.h"


// Configuration structure for a GPIO pin
typedef struct
{
    uint8_t GPIO_PinNumber;
    // <-- FIX: Renamed 'GPIO_PiMode' to 'GPIO_PinMode' to fix the typo.
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPupdControl;
    uint8_t GPIO_PinOpType;
    uint8_t GPIO_PinAltFunMode;
} GPIO_Pin_Config_t;

// Handle structure for a GPIO pin
typedef struct
{
    // <-- FIX: Changed 'pGPIOX' to 'pGPIOx' (lowercase 'x') for consistency.
    //          This now matches your peripheral access macros (GPIOA, GPIOB, etc.)
    GPIO_RegDef *pGPIOx;               // Pointer to base address of the GPIO port
    GPIO_Pin_Config_t GPIO_Pin_Config; // Holds the pin configuration settings
} GPIO_Handle_t;


// @GPIO_MODES: GPIO pin possible modes
#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_ALTFN     2
#define GPIO_MODE_ANALOG    3
#define GPIO_MODE_IT_FT     4  // Interrupt Falling edge
#define GPIO_MODE_IT_RT     5  // Interrupt Rising edge
#define GPIO_MODE_IT_RFT    6  // Interrupt Rising-Falling edge

// @GPIO_OUTPUT_TYPE: GPIO pin possible output types
#define GPIO_OP_TYPE_PP     0  // Push-Pull
#define GPIO_OP_TYPE_OD     1  // Open Drain

// @GPIO_SPEED: GPIO pin possible output speeds
#define GPIO_SPEED_LOW      0
#define GPIO_SPEED_MEDIUM   1
#define GPIO_SPEED_FAST     2
#define GPIO_SPEED_HIGH     3

// @GPIO_PUPD: GPIO pin pull-up and pull-down configurations
#define GPIO_NO_PUPD        0
#define GPIO_PIN_PU         1
#define GPIO_PIN_PD         2

// @GPIO_PIN_NUMBERS: GPIO pin numbers
#define GPIO_PIN_NO_0       0
#define GPIO_PIN_NO_1       1
#define GPIO_PIN_NO_2       2
#define GPIO_PIN_NO_3       3
#define GPIO_PIN_NO_4       4
#define GPIO_PIN_NO_5       5
#define GPIO_PIN_NO_6       6
#define GPIO_PIN_NO_7       7
#define GPIO_PIN_NO_8       8
#define GPIO_PIN_NO_9       9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15


//=========================== API Function Prototypes ===========================

// Peripheral Clock Setup
void GPIO_PeriClockControl(GPIO_RegDef *pGPIOx, uint8_t EnOrDi);

// Init and De-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef *pGPIOx); // Note: DeInit resets the whole port

// Data Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef *pGPIOx, uint8_t PinNumber);

// IRQ Configuration and Handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

// <-- FIX: Changed parameter from 'IRQNumber' to 'PinNumber'.
//          This function is called inside the ISR to check and clear
//          the EXTI pending bit, which is mapped by *pin number*.
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32F446RE_GPIO_DRIVER_H_ */
