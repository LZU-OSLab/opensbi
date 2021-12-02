/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2021 MaPl <mapl@york.moe>.
 *
 * Authors:
 *   MaPl <mapl@york.moe>
 */

#include <sbi/riscv_io.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi_utils/sys/d1_wdog.h>

#define D1_WDOG_ADDR      0x06011000
#define WDOG_SOFT_RST_REG 0x14
#define WDOG_SOFT_EN_REG  0x18

#define WDOG_RST_REQ      0x16aa0001

static void *d1_wdog_base = (void *)D1_WDOG_ADDR;

int d1_wdog_system_reset_check(u32 type, u32 reason)
{
	switch (type) {
	case SBI_SRST_RESET_TYPE_SHUTDOWN:
	case SBI_SRST_RESET_TYPE_COLD_REBOOT:
	case SBI_SRST_RESET_TYPE_WARM_REBOOT:
		return 1;
	}

	return 0;
}

void d1_wdog_system_reset(u32 type, u32 reason)
{
	switch (type) {
	case SBI_SRST_RESET_TYPE_SHUTDOWN:
		while (1);
		break;
	case SBI_SRST_RESET_TYPE_COLD_REBOOT:
	case SBI_SRST_RESET_TYPE_WARM_REBOOT:
		writel(WDOG_RST_REQ, d1_wdog_base + WDOG_SOFT_RST_REG);
		writel(WDOG_RST_REQ, d1_wdog_base + WDOG_SOFT_EN_REG);
		break;
	}
}
