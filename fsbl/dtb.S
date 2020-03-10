/* Copyright (c) 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* SPDX-License-Identifier: GPL-2.0-or-later */
/* See the file LICENSE for further information */

  .section .data
  .globl own_dtb
own_dtb:
  .incbin "/home/bored/Desktop/fu540-immutable_bootloader/build/ux00_fsbl.dtb"
