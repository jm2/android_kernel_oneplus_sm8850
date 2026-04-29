// SPDX-License-Identifier: GPL-2.0-only
/*
 * Phase F minimum-viable stub for free_zram_is_ok consumed by the
 * oplus_bsp_zram_opt.ko OEM prebuilt. The real implementation in
 * vendor/oplus/kernel/mm/hybridswap_zram/hybridswap/hybridswapd.c is
 * tied into a much larger hybridswap subsystem that needs ~12
 * android_vh_* vendor hook declarations not present in our trace
 * headers. Returning true here keeps the zram_opt optimizer in a
 * "no memory pressure" state — equivalent to a healthy boot.
 *
 * If you ever wire up the full hybridswap source, drop this stub and
 * replace with: zram-$(CONFIG_HYBRIDSWAP_CORE) += hybridswap/...
 */
#include <linux/module.h>
#include <linux/types.h>

bool free_zram_is_ok(void)
{
	return true;
}
EXPORT_SYMBOL_GPL(free_zram_is_ok);
