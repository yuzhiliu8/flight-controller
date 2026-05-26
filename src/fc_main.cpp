/*
 * Main entrypoint for the FC. This fc_main function gets called in the main.c entrypoint
 */

#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"


extern "C"
void fc_main(void) {

    while(1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(1000);
    }
}
