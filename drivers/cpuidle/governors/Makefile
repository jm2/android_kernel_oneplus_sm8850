# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for cpuidle governors.
#

obj-$(CONFIG_CPU_IDLE_GOV_LADDER) += ladder.o
obj-$(CONFIG_CPU_IDLE_GOV_MENU) += menu.o
obj-$(CONFIG_CPU_IDLE_GOV_TEO) += teo.o
obj-$(CONFIG_CPU_IDLE_GOV_HALTPOLL) += haltpoll.o

# Qualcomm cpuidle LPM governor — qcom_lpm.ko bundles 3 sources
qcom_lpm-y := qcom-lpm.o qcom-cluster-lpm.o qcom-lpm-sysfs.o
obj-$(CONFIG_CPU_IDLE_GOV_QCOM_LPM) += qcom_lpm.o
