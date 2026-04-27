# SPDX-License-Identifier: GPL-2.0-only

zram-y	:=	zcomp.o zram_drv.o

# The vendor reverted zcomp.c/zcomp.h to the pre-ACK crypto_comp API but kept
# the new-API backend_*.c files; those don't link with the reverted zcomp.c.
# zcomp.c selects compression algorithms via crypto_comp, so the backend_*.o
# objects are dead code here. The ZRAM_BACKEND_* Kconfigs still drive the
# `select <algo>_COMPRESS` lines, which is what crypto_comp consumes.

obj-$(CONFIG_ZRAM)	+=	zram.o
