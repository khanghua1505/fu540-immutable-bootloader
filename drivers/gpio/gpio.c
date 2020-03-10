/* Copyright (c) 2019 - 2020, Khang Hua, email: khanghua1505@gmail.com
 * All right reserved.
 *
 * This file is written and modified by Khang Hua.
 *
 * This model is free software; you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License; either version 2.1 of the License, or (at your option)
 * any later version. See the GNU Lesser General Public License for more details,
 *
 * This model is distributed in the hope that it will be useful.
 */
 
#include <stdint.h>
#include "gpio.h"

void gpio_pin_mode(gpio_ctrl *gpio, gpio_pin_t pin, gpio_mode_t mode)
{
  switch (mode) {
    default:
    case GPIO_MODE_INPUT:
      gpio->input_en |= pin;
      gpio->output_en &= (~pin);
      break;
    case GPIO_MODE_OUTPUT:
      gpio->output_en |= pin;
      gpio->input_en &= pin;
      gpio->pue |= pin;
      break;
  }
}

void gpio_pin_setval(gpio_ctrl *gpio, gpio_pin_t pin, int value)
{
  if (value == GPIO_PIN_RESET) {
    gpio->output_val &= (~pin);
  } else {
    gpio->output_val |= pin;
  }
}

int gpio_pin_getval(gpio_ctrl *gpio, gpio_pin_t pin)
{
  if (gpio->input_val | pin) {
    return GPIO_PIN_SET;
  } else {
    return GPIO_PIN_RESET;
  }
}


