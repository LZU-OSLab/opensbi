/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2021 MaPl <mapl@york.moe>.
 *
 * Authors:
 *   MaPl <mapl@york.moe>
 */

#ifndef __SYS_D1_WDOG_H__
#define __SYS_D1_WDOG_H__

#include <sbi/sbi_types.h>

int d1_wdog_system_reset_check(u32 type, u32 reason);

void d1_wdog_system_reset(u32 type, u32 reason);

#endif
