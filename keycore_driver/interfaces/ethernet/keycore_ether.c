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
#include <stdbool.h>
#include <string.h>
#include "socket.h"
#include "gpio/gpio.h"
#include "ether_info.c"

#include "keycore.h"

static wiz_NetInfo net_info;
static uint8_t chip_txrx_buffsize[] = {2, 2, 2, 2, 2, 2, 2, 2};

static void spi_select(void);
static void spi_deselect(void);
static void spi_read(uint8_t *buffer, uint16_t len);
static void spi_write(uint8_t *buffer, uint16_t len);
static uint8_t spi_read_byte(void);
static void spi_write_byte(uint8_t byte);

static void 
spi_select(void)
{
  gpio_pin_setval(ether_spi_ss_gpio, ether_spi_ss_pin, GPIO_PIN_RESET);
}

static void
spi_deselect(void)
{
  gpio_pin_setval(ether_spi_ss_gpio, ether_spi_ss_pin, GPIO_PIN_SET);
}

static void 
spi_read(uint8_t *buffer, uint16_t len)
{
  uint16_t index;
  for (index = 0; index < len; index++) {
    buffer[index] = spi_read_byte();
  }
}

static void 
spi_write(uint8_t *buffer, uint16_t len)
{
  uint16_t index;
  for (index = 0; index < len; index++) {
    spi_write_byte(buffer[index]);
  }
}

static uint8_t 
spi_read_byte(void)
{
  uint8_t dummy;
  return spi_txrx(ether_spi, dummy);
}

static void
spi_write_byte(uint8_t byte)
{
  (void)spi_txrx(ether_spi, byte);
}

static void 
gpio_config(void)
{
  unsigned int keycore_spi_target_khz;
  unsigned int keycore_spi_div;
  extern unsigned long peripheral_input_khz;
  
  gpio_pin_mode(ether_spi_ss_gpio, ether_spi_ss_pin, 
      GPIO_MODE_OUTPUT);
  gpio_pin_setval(ether_spi_ss_gpio, ether_spi_ss_pin, 
      GPIO_PIN_SET);
      
  keycore_spi_target_khz = 4000;
  keycore_spi_div = spi_min_clk_divisor(peripheral_input_khz, 
      keycore_spi_target_khz);
  
  ether_spi->sckdiv = keycore_spi_div;
  ether_spi->csmode.raw_bits = 3;
  ether_spi->fctrl.raw_bits = 0;
  ether_spi->fmt.raw_bits = 0;
  ether_spi->fmt.len = 8;
}

static int
chip_init(void)
{
  int8_t status;
  
  memcpy(net_info.ip, clientip, 4);
  memcpy(net_info.mac, mac_addr, 6);
  memcpy(net_info.gw, default_gateway, 4);
  memcpy(net_info.sn, subnet_mask, 4);
  
  reg_wizchip_cs_cbfunc(spi_select, spi_deselect);
  reg_wizchip_spi_cbfunc(spi_read_byte, spi_write_byte);
  reg_wizchip_spiburst_cbfunc(spi_read, spi_write);
  
  status = wizchip_init(chip_txrx_buffsize, chip_txrx_buffsize);
  if (status != 0) {
    return -1;
  }
  
  setSHAR(net_info.mac);
  wizchip_setnetinfo(&net_info);
  
  return 0;
}

int
ethernet_init(void)
{
  uint8_t status;
  
  gpio_config();
  
  if (chip_init() != 0) {
    return -1;
  }
  
  status = socket(sock, Sn_MR_TCP, port, 0);
  if (status != sock) {
    return -1;
  }
  
  status = connect(sock, serverip, port);
  if (status != SOCK_OK) {
    close(sock);
    return -1;
  }
  
  return 0;
}

ssize_t
ethernet_write(uint8_t *buffer, uint16_t len)
{
  ssize_t byte_transferred;
  
  byte_transferred = send(sock, buffer, len);
  if (byte_transferred <= 0) {
    close(sock);
    return -1;
  }
  
  return byte_transferred;
}

ssize_t
ethernet_read(uint8_t *buffer, uint16_t len)
{
  return recv(sock, &buffer[0], len);
}

keycore_handle_t keycore = {
  .initfn = ethernet_init,
  .readfn = ethernet_read,
  .writefn = ethernet_write,
};





