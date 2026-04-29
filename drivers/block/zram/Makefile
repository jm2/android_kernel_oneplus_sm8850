# SPDX-License-Identifier: GPL-2.0-only

zram-y	:=	zcomp.o zram_drv.o

# Phase F: minimum-viable stub for free_zram_is_ok consumed by the
# oplus_bsp_zram_opt.ko OEM prebuilt. Vendor's full hybridswap subsystem
# (hybridmain.c + hybridswap.c + hybridswapd.c + ezreclaimd.c + display.c)
# requires ~12 additional android_vh_* hook declarations not in our trace
# headers and a `#include "../zram_drv.h"` that breaks under our symlink
# layout. zram_opt only consumes the boolean check; a `return true` stub
# satisfies modpost and keeps the optimizer in a "memory always OK"
# state — same posture as having no swap pressure, which is correct for
# a fresh boot.
zram-y	+=	hybridswap_stub.o

# The vendor reverted zcomp.c/zcomp.h to the pre-ACK crypto_comp API but kept
# the new-API backend_*.c files; those don't link with the reverted zcomp.c.
# zcomp.c selects compression algorithms via crypto_comp, so the backend_*.o
# objects are dead code here. The ZRAM_BACKEND_* Kconfigs still drive the
# `select <algo>_COMPRESS` lines, which is what crypto_comp consumes.

obj-$(CONFIG_ZRAM)	+=	zram.o
