#pragma once

#include "gpio.hpp"




class BMI160
{
public:
  BMI160();

  uint8_t read_id();

private:
  GpioPin cs_;


};
