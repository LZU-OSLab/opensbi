#
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (c) 2019 Western Digital Corporation or its affiliates.
# Copyright (c) 2021 MaPl <mapl@york.moe>
#
# Authors:
#   Anup Patel <anup.patel@wdc.com>
#   MaPl <mapl@york.moe>
#

libsbiutils-objs-y += serial/fdt_serial.o
libsbiutils-objs-y += serial/fdt_serial_htif.o
libsbiutils-objs-y += serial/fdt_serial_shakti.o
libsbiutils-objs-y += serial/fdt_serial_sifive.o
libsbiutils-objs-y += serial/fdt_serial_uart8250.o
libsbiutils-objs-y += serial/shakti-uart.o
libsbiutils-objs-y += serial/sifive-uart.o
libsbiutils-objs-y += serial/uart8250.o
libsbiutils-objs-y += serial/sunxi-uart.o
