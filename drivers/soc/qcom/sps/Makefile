# SPDX-License-Identifier: GPL-2.0
# Vendor module wired via Bazel `module_outs` (see modules.bzl) but never
# given a Makefile; restored to satisfy in-tree obj rules. Module name
# is sps_drv.ko per the kernel_module spec in modules.bzl.

obj-$(CONFIG_SPS) += sps_drv.o
sps_drv-y := sps.o sps_bam.o sps_dma.o sps_map.o sps_mem.o sps_rm.o bam.o
