/*
 * STM32F446RE_SPI_DRIVERS.h  // <-- FIX: Corrected typo F466 to F446
 *
 * Created on: Oct 21, 2025
 * Author: notty
 */

// <-- FIX: Corrected typo F466 to F446
#ifndef STM32F446RE_SPI_DRIVERS_H_
#define STM32F446RE_SPI_DRIVERS_H_

#include <stdint.h>
#include "stm32f446re.h" // Include the MCU-specific header

/**
 * @brief Configuration structure for an SPI peripheral
 */
typedef struct{
    // <-- FIX: Changed 'Spi_DeviceMode' to 'SPI_DeviceMode' for consistency
	uint8_t SPI_DeviceMode; /*!< Master or Slave mode. See @SPI_Device_Modes */
	uint8_t BusConfig;      /*!< Bus configuration (Full-duplex, Half-duplex, etc.). See @SPI_Bus_Configs */
	uint8_t SCLK_Speed;     /*!< SCLK speed (Baud rate). See @SPI_SCLK_Speeds */
	uint8_t DFF;            /*!< Data Frame Format (8-bit or 16-bit). See @SPI_DFF_Formats */
	uint8_t CPOL;           /*!< Clock Polarity. See @SPI_CPOL_Settings */
	uint8_t CPHA;           /*!< Clock Phase. See @SPI_CPHA_Settings */
	uint8_t SSM;            /*!< Software Slave Management. See @SPI_SSM_Settings */
}SPI_Config_t;

/**
 * @brief Handle structure for an SPI peripheral
 * Contains a pointer to the SPI registers and the configuration settings.
 */
typedef struct {
	SPI_RegDef_t *pSPIx;       /*!< Pointer to the base address of the SPI peripheral (SPI1, SPI2, etc.) */
	SPI_Config_t SPI_Config; /*!< SPI configuration structure */
}SPI_Handle_t;


/******************************************************************************/
/* */
/* DRIVER API PROTOTYPES                                                      */
/* */
/******************************************************************************/

/**
 * @brief Enables or disables the peripheral clock for a given SPI port.
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

/**
 * @brief Initializes a given SPI peripheral with the settings in the handle.
 */
void SPI_Init(SPI_Handle_t *pSPIHandle); // <-- NOTE: Changed variable name for clarity

/**
 * @brief De-initializes a given SPI peripheral, resetting it.
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx); // <-- NOTE: Renamed from SPI_Dinit

/**
 * @brief Sends data over SPI (blocking call).
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);

/**
 * @brief Receives data over SPI (blocking call).
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/**
 * @brief Gets the status of a specific flag in the SPI_SR register.
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FLAG_NAME);

/*
 * IRQ (Interrupt) Configuration and Handling
 */
void SPI_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle); // <-- NOTE: Changed variable name for clarity

/**
 * @defgroup SPI_Device_Modes SPI Device Modes
 * @{
 */
#define SPI_DEVICE_MODE_MASTER  1
#define SPI_DEVICE_MODE_SLAVE   0 // <-- NOTE: Conventionally, Slave is 0
/**
 * @}
 */

/**
 * @defgroup SPI_Bus_Configs SPI Bus Configurations
 * @{
 */
#define SPI_BUS_CONFIG_FD        1 /*!< Full-duplex */
#define SPI_BUS_CONFIG_HD        2 /*!< Half-duplex */
#define SPI_BUS_CONFIG_S_RXONLY  3 /*!< Simplex, RX-only */
/**
 * @}
 */

/**
 * @defgroup SPI_SCLK_Speeds SPI SCLK Speeds (Baud Rate)
 * @brief Values map to the BR[2:0] bits in SPI_CR1
 * @{
 */
#define SPI_SCLK_SPEED_DIV2    0
#define SPI_SCLK_SPEED_DIV4    1
#define SPI_SCLK_SPEED_DIV8    2
#define SPI_SCLK_SPEED_DIV16   3
#define SPI_SCLK_SPEED_DIV32   4
#define SPI_SCLK_SPEED_DIV64   5
#define SPI_SCLK_SPEED_DIV128  6
#define SPI_SCLK_SPEED_DIV256  7
/**
 * @}
 */

/**
 * @defgroup SPI_DFF_Formats SPI DFF (Data Frame Format)
 * @{
 */
#define SPI_DFF_8BITS  0
#define SPI_DFF_16BITS 1
/**
 * @}
 */

/**
 * @defgroup SPI_CPOL_Settings SPI CPOL (Clock Polarity)
 * @{
 */
#define SPI_CPOL_LOW  0
#define SPI_CPOL_HIGH 1
/**
 * @}
 */

/**
 * @defgroup SPI_CPHA_Settings SPI CPHA (Clock Phase)
 * @{
 */
#define SPI_CPHA_LOW  0
#define SPI_CPHA_HIGH 1
/**
 * @}
 */

/**
 * @defgroup SPI_SSM_Settings SPI SSM (Software Slave Management)
 * @{
 */
#define SPI_SSM_DI 0
#define SPI_SSM_EN 1 // <-- FIX: Corrected capitalization from "En" to "EN"
/**
 * @}
 */


#endif /* STM32F446RE_SPI_DRIVERS_H_ */ // <-- FIX: Corrected typo F466 to F446
