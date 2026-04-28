# SPDX-License-Identifier: GPL-2.0

obj-$(CONFIG_GUNYAH_HYPERCALLS) += gunyah_hypercall.o

# Vendor-stripped: gh_arm_drv.ko bundles arch-specific gunyah pieces.
# Per arch/arm64/gunyah/modules.bzl: gh_arm.c + irq.c + reset.c.
gh_arm_drv-y := gh_arm.o irq.o reset.o
obj-$(CONFIG_GH_ARM64_DRV) += gh_arm_drv.o
