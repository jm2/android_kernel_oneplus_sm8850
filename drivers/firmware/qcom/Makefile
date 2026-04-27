# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the linux kernel.
#

obj-$(CONFIG_QCOM_SCM)		+= qcom-scm.o
qcom-scm-objs += qcom_scm.o qcom_scm-smc.o qcom_scm-legacy.o
# Vendor's modules.bzl bundles qtee_shmbridge into qcom-scm.ko; its
# qtee_shmbridge_driver_init/exit aren't EXPORT_SYMBOL'd, so it can't be a
# separate module. Put it in qcom-scm-objs under the same gate.
qcom-scm-$(CONFIG_QTEE_SHM_BRIDGE) += qtee_shmbridge.o
obj-$(CONFIG_QCOM_TZMEM)	+= qcom_tzmem.o
obj-$(CONFIG_QCOM_QSEECOM)	+= qcom_qseecom.o
obj-$(CONFIG_QCOM_QSEECOM_UEFISECAPP) += qcom_qseecom_uefisecapp.o
