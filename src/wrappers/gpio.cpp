#include "gpio.hpp"
#include "stm32f4xx_hal_gpio.h"


bool GpioPin::read() {
    //PIN_RESET is 0 --> false
    //PIN_SET is 1 --> true
    return HAL_GPIO_ReadPin(gpio_typedef_, gpio_pin_);
}

void GpioPin::set() {
    HAL_GPIO_WritePin(gpio_typedef_, gpio_pin_, GPIO_PIN_SET);
}

void GpioPin::reset() {
    HAL_GPIO_WritePin(gpio_typedef_, gpio_pin_, GPIO_PIN_RESET);
}
void GpioPin::toggle() {
    HAL_GPIO_TogglePin(gpio_typedef_, gpio_pin_);
}


/*
GPIO_TypeDef gpio_typedef_;
uint16_t gpio_pin_;
*/
