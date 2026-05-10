# SPDX-License-Identifier: GPL-2.0-only

zram-y	:=	zcomp.o zram_drv.o

zram-$(CONFIG_ZRAM_BACKEND_LZO)		+= backend_lzorle.o backend_lzo.o
zram-$(CONFIG_ZRAM_BACKEND_LZ4)		+= backend_lz4.o
zram-$(CONFIG_ZRAM_BACKEND_LZ4HC)	+= backend_lz4hc.o
zram-$(CONFIG_ZRAM_BACKEND_ZSTD)	+= backend_zstd.o
zram-$(CONFIG_ZRAM_BACKEND_DEFLATE)	+= backend_deflate.o
zram-$(CONFIG_ZRAM_BACKEND_842)		+= backend_842.o

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
obj-$(CONFIG_ZRAM)	+=	zram.o
