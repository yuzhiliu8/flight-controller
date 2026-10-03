#ifndef GPIO_PIN_HPP
#define GPIO_PIN_HPP

#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"


class GpioPin {
    public:
        GpioPin(GPIO_TypeDef* gpio_typedef, uint16_t gpio_pin)
            : gpio_typedef_(gpio_typedef), gpio_pin_(gpio_pin) {}
        bool read();
        void set();
        void reset();
        void toggle();


    private:
        GPIO_TypeDef* gpio_typedef_;
        uint16_t gpio_pin_;

};

#endif
