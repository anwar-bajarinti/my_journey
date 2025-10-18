/*
 * 002button.c
 *
 *  Created on: Oct 18, 2025
 *  Author: notty
 *
 *  Description:
 *  -----------------
 *  This program demonstrates how to toggle an LED (PA5) on the
 *  STM32F446RE Nucleo board when the onboard user button (PC13)
 *  is pressed.
 *
 *  Hardware connections:
 *  - LED  : PA5 (connected to onboard LD2 on Nucleo-F446RE)
 *  - Button: PC13 (connected to the onboard user button)
 */

#include "stm32f446re.h"
#include "STM32F446RE_GPIO_DRIVER.h"

#define PRESSED 0   // On Nucleo boards, the button gives logic LOW (0) when pressed

// -------------------------------------------------------------------
// Simple software delay (not accurate, just for button debouncing)
// -------------------------------------------------------------------
void delay(void)
{
    for (uint32_t i = 0; i < 500000; i++);  // crude delay loop
}

int main(void)
{
    // Create handle structures for LED and Button
    GPIO_Handle_t GpioLed, GpioBtn;

    // ------------------ LED Configuration ------------------
    // PA5 → LED (LD2 on Nucleo)
    GpioLed.pGPIOX = GPIOA;                                 // Select GPIO Port A
    GpioLed.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_5;  // Pin 5 (PA5)
    GpioLed.GPIO_Pin_Config.GPIO_PiMode = GPIO_MODE_OUT;     // Output mode
    GpioLed.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_SPEED_FAST; // Fast speed
    GpioLed.GPIO_Pin_Config.GPIO_PinOpType = GPIO_OP_TYPE_OD;// Open-drain output
    GpioLed.GPIO_Pin_Config.GPIO_PinPupdControl = GPIO_PIN_PU; // Enable internal pull-up

    // ------------------ Button Configuration ------------------
    // PC13 → User Button (blue button on Nucleo)
    GpioBtn.pGPIOX = GPIOC;                                  // Select GPIO Port C
    GpioBtn.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NO_13;  // Pin 13 (PC13)
    GpioBtn.GPIO_Pin_Config.GPIO_PiMode = GPIO_MODE_IN;       // Input mode
    GpioBtn.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_SPEED_FAST;  // Fast input
    GpioBtn.GPIO_Pin_Config.GPIO_PinPupdControl = GPIO_NO_PUPD; // No pull-up/pull-down (external circuit handles it)

    // ------------------ Enable Peripheral Clocks ------------------
    GPIO_PeriClockControl(GPIOA, ENABLE);  // Enable clock for Port A (for LED)
    GPIO_PeriClockControl(GPIOC, ENABLE);  // Enable clock for Port C (for Button)

    // ------------------ Initialize GPIOs ------------------
    GPIO_Init(&GpioLed);
    GPIO_Init(&GpioBtn);

    // ------------------ Main Loop ------------------
    while (1)
    {
        // Read button state (returns 0 when pressed, 1 when released)
        if (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) == PRESSED)
        {
            delay(); // simple debounce delay

            // Toggle LED state (ON ↔ OFF)
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
        }
    }

    // Code never reaches here
    return 0;
}
