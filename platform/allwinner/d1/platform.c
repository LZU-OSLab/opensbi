/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 * Copyright (c) 2021 MaPl <mapl@york.moe>.
 */

#include <sbi/riscv_io.h>
#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_platform.h>

#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/uart8250.h>
#include <sbi_utils/sys/clint.h>
#include <sbi_utils/sys/d1_wdog.h>

#define D1_PLIC_ADDR		 0x10000000
#define D1_PLIC_NUM_SOURCES	 256
#define D1_PLIC_DELEG_OFFSET 0x101ffffc
#define D1_PLIC_DELEG_ENABLE 0x1

#define D1_HART_COUNT		 1
#define D1_CLINT_ADDR	     0x14000000

#define D1_UART_ADDR		 0x02500000
#define D1_UART_CLK_IN_HZ	 24000000
#define D1_UART_BAUDRATE 	 115200
#define D1_UART_REG_SHIFT	 2
#define D1_UART_REG_WIDTH	 2

static struct plic_data plic = {
	.addr = D1_PLIC_ADDR,
	.num_src = D1_PLIC_NUM_SOURCES,
};

static struct clint_data clint = {
	.addr = D1_CLINT_ADDR,
	.first_hartid = 0,
	.hart_count = D1_HART_COUNT,
	.has_64bit_mmio = FALSE,
};

static int d1_console_init(void)
{
	return uart8250_init(D1_UART_ADDR, D1_UART_CLK_IN_HZ,
			     D1_UART_BAUDRATE, D1_UART_REG_SHIFT,
			     D1_UART_REG_WIDTH);
}

static int d1_irqchip_init(bool cold_boot)
{
	u32 hartid = current_hartid();
	int ret;

	writel(D1_PLIC_DELEG_ENABLE, (void *)D1_PLIC_DELEG_OFFSET);
	if (cold_boot) {
		ret = plic_cold_irqchip_init(&plic);
		if (ret)
			return ret;
	}

	return plic_warm_irqchip_init(&plic, 2 * hartid, 2 * hartid + 1);
}

static int d1_ipi_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		ret = clint_cold_ipi_init(&clint);
		if (ret)
			return ret;
	}

	return clint_warm_ipi_init();
}

static int d1_timer_init(bool cold_boot)
{
	int ret;

	if (cold_boot) {
		ret = clint_cold_timer_init(&clint, NULL);
		if (ret)
			return ret;
	}

	return clint_warm_timer_init();
}

const struct sbi_platform_operations platform_ops = {
	.console_putc		= uart8250_putc,
	.console_getc		= uart8250_getc,
	.console_init		= d1_console_init,
	.irqchip_init		= d1_irqchip_init,
	.ipi_send		= clint_ipi_send,
	.ipi_clear		= clint_ipi_clear,
	.ipi_init		= d1_ipi_init,
	.timer_value		= clint_timer_value,
	.timer_event_stop	= clint_timer_event_stop,
	.timer_event_start	= clint_timer_event_start,
	.timer_init		= d1_timer_init,
	.system_reset_check	= d1_wdog_system_reset_check,
	.system_reset		= d1_wdog_system_reset
};
const struct sbi_platform platform = {
	.opensbi_version	= OPENSBI_VERSION,
	.platform_version	= SBI_PLATFORM_VERSION(0x0, 0x01),
	.name			= "Allwinnner D1",
	.features		= SBI_PLATFORM_DEFAULT_FEATURES,
	.hart_count		= D1_HART_COUNT,
	.hart_stack_size	= SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr	= (unsigned long)&platform_ops
};
