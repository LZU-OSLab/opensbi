#
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (c) 2019 Western Digital Corporation or its affiliates.
# Copyright (c) 2021 MaPl <mapl@york.moe>.
#

platform-cppflags-y =
platform-cflags-y =
platform-asflags-y =
platform-ldflags-y =

PLATFORM_RISCV_XLEN = 64
PLATFORM_RISCV_ABI = lp64
PLATFORM_RISCV_ISA = rv64imafdcv
PLATFORM_RISCV_CODE_MODEL = medany

FW_TEXT_START=0x80000000

# Optional parameter for path to external FDT
# FW_FDT_PATH="path to platform flattened device tree file"

FW_JUMP=y

FW_JUMP_ADDR=0x80200000