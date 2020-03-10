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
#include <spi/spi.h>
#include <gpio/gpio.h>
#include <sifive/platform.h>

static spi_ctrl* const ether_spi = (spi_ctrl*) SPI1_CTRL_ADDR;
static gpio_ctrl* const ether_spi_ss_gpio = (gpio_ctrl*) GPIO_CTRL_ADDR;
static gpio_pin_t ether_spi_ss_pin = GPIO_PIN_1;

static uint8_t  sock = 0;
static uint16_t port = 8080;
static uint8_t  serverip[] = {10,10,10,225};

static const uint8_t clientip[4] = {10,10,10,2};
static const uint8_t mac_addr[6] = {0xEA,0x11,0x22,0x33,0x44,0xEA};
static const uint8_t default_gateway[4] = {10,10,10,225};
static const uint8_t subnet_mask[4] = {255,255,255,0};

