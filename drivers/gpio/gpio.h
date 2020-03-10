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
 
#ifndef _DRIVERS_GPIO_H_
#define _DRIVERS_GPIO_H_

#ifndef __ASSEMBLER__

#include <stdint.h>

#define GPIO_PIN_0    ((uint32_t) (1 << 0))
#define GPIO_PIN_1    ((uint32_t) (1 << 1))
#define GPIO_PIN_2    ((uint32_t) (1 << 2))
#define GPIO_PIN_3    ((uint32_t) (1 << 3))
#define GPIO_PIN_4    ((uint32_t) (1 << 4))
#define GPIO_PIN_5    ((uint32_t) (1 << 5))
#define GPIO_PIN_6    ((uint32_t) (1 << 6))
#define GPIO_PIN_7    ((uint32_t) (1 << 7))
#define GPIO_PIN_8    ((uint32_t) (1 << 8))
#define GPIO_PIN_9    ((uint32_t) (1 << 9))
#define GPIO_PIN_10   ((uint32_t) (1 << 10))
#define GPIO_PIN_11   ((uint32_t) (1 << 11))
#define GPIO_PIN_12   ((uint32_t) (1 << 12))
#define GPIO_PIN_13   ((uint32_t) (1 << 13))
#define GPIO_PIN_14   ((uint32_t) (1 << 14))
#define GPIO_PIN_15   ((uint32_t) (1 << 15))

typedef enum {
  GPIO_MODE_INPUT,
  GPIO_MODE_OUTPUT,
}
gpio_mode_t;

enum {
  GPIO_PIN_RESET = 0x00,
  GPIO_PIN_SET = 0x01,
};

typedef uint32_t gpio_pin_t;

typedef volatile struct {
  uint32_t input_val;
  uint32_t input_en;
  uint32_t output_en;
  uint32_t output_val;
  uint32_t pue;
  uint32_t ds;
  uint32_t rise_ie;
  uint32_t rise_ip;
  uint32_t fall_ie;
  uint32_t fall_ip;
  uint32_t high_ie;
  uint32_t high_ip;
  uint32_t low_ie;
  uint32_t low_ip;
  uint32_t out_xor;
}
gpio_ctrl;

void gpio_pin_mode(gpio_ctrl *gpio, gpio_pin_t pin, gpio_mode_t mode);
void gpio_pin_setval(gpio_ctrl *gpio, gpio_pin_t pin, int value);
int gpio_pin_getval(gpio_ctrl *gpio, gpio_pin_t pin);

#endif  // __ASSEMBLER__

#endif  // _DRIVERS_GPIO_H_
