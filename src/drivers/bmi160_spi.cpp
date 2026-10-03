#include "bmi160_spi.hpp"
#include "gpio.hpp"
#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_gpio.h"
// PIN DEFINITIONS

static GPIO_TypeDef* CS_PIN_TYPE = GPIOA;
static constexpr uint16_t CS_PIN = GPIO_PIN_4;

static GPIO_TypeDef* SCL_PIN_TYPE = GPIOA;
static constexpr uint16_t SCL_PIN = GPIO_PIN_5;

static GPIO_TypeDef* SDA_PIN_TYPE = GPIOA;
static constexpr uint16_t SDA_PIN = GPIO_PIN_7;

static GPIO_TypeDef* SAO_PIN_TYPE = GPIOA;
static constexpr uint16_t SAO_PIN = GPIO_PIN_6;

// SPI 1 handle that this BMI160 owns
extern "C" {
    extern SPI_HandleTypeDef hspi1;
}

BMI160::BMI160() : cs_(GpioPin(CS_PIN_TYPE, CS_PIN))
{
}

uint8_t BMI160::read_id()
{
  uint8_t tx[2] = {
    static_cast<uint8_t>(0x00 | 0x80), // | 0x80 puts a "read" bit to the beginning of the byte
    0x00 // dummy byte
  };
  uint8_t rx[2] = {}; // rx[0] is a dummy byte, rx[1] gets the useful data

  cs_.reset(); // low: start transaction
  auto result = HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, HAL_MAX_DELAY);
  cs_.set(); // high: finish transaction

  if (result != HAL_OK) {
    return 0;
  }

  return rx[1];
}
