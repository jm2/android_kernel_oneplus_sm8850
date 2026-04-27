# SPDX-License-Identifier: GPL-2.0
CFLAGS_rpmh-rsc.o := -I$(src)
CFLAGS_qcom_aoss.o := -I$(src)
obj-$(CONFIG_QCOM_AOSS_QMP) +=	qcom_aoss.o
obj-$(CONFIG_QCOM_GENI_SE) +=	qcom-geni-se.o
obj-$(CONFIG_QCOM_COMMAND_DB) += cmd-db.o
obj-$(CONFIG_QCOM_GSBI)	+=	qcom_gsbi.o
obj-$(CONFIG_QCOM_MDT_LOADER)	+= mdt_loader.o
obj-$(CONFIG_QCOM_OCMEM)	+= ocmem.o
obj-$(CONFIG_QCOM_PD_MAPPER)	+= qcom_pd_mapper.o
obj-$(CONFIG_QCOM_PDR_HELPERS)	+= pdr_interface.o
obj-$(CONFIG_QCOM_PDR_MSG)	+= qcom_pdr_msg.o
obj-$(CONFIG_QCOM_PMIC_GLINK)	+= pmic_glink.o
obj-$(CONFIG_QCOM_PMIC_GLINK)	+= pmic_glink_altmode.o
obj-$(CONFIG_QCOM_PMIC_PDCHARGER_ULOG)	+= pmic_pdcharger_ulog.o
CFLAGS_pmic_pdcharger_ulog.o	:=  -I$(src)
obj-$(CONFIG_QCOM_QMI_HELPERS)	+= qmi_helpers.o
qmi_helpers-y	+= qmi_encdec.o qmi_interface.o
obj-$(CONFIG_QCOM_RAMP_CTRL)	+= ramp_controller.o
obj-$(CONFIG_QCOM_RMTFS_MEM)	+= rmtfs_mem.o
obj-$(CONFIG_QCOM_RPM_MASTER_STATS)	+= rpm_master_stats.o
obj-$(CONFIG_QCOM_RPMH)		+= qcom_rpmh.o
qcom_rpmh-y			+= rpmh-rsc.o
qcom_rpmh-y			+= rpmh.o
# Vendor-added CRM/CRM-V2 sources missing from this Makefile.
obj-$(CONFIG_QCOM_CRM)		+= crm.o
obj-$(CONFIG_QCOM_CRM_V2)	+= crm-v2.o
# Bundle the minidump main + helper TUs as one module. minidump_log.c /
# minidump_memory.c are referenced by name from msm_minidump.c but were
# never wired into the Makefile, and only msm_minidump.c has MODULE_LICENSE.
# Module name is qcom_minidump.ko to avoid colliding with msm_minidump.o
# (which is the standalone .o that we now want as a member of the bundle).
obj-$(CONFIG_QCOM_MINIDUMP)	+= qcom_minidump.o
qcom_minidump-y			:= msm_minidump.o minidump_log.o minidump_memory.o
# minidump_smem.c is bool=y in Kconfig (always vmlinux when set), but it
# calls msm_minidump_clear_headers / md_num_regions / set_section_name
# from msm_minidump.c which lives in the qcom_minidump.ko bundle when
# QCOM_MINIDUMP=m. Bundling minidump_smem.o into the same .ko resolves
# the symbols internally.
qcom_minidump-$(CONFIG_QCOM_MINIDUMP_SMEM)	+= minidump_smem.o
obj-$(CONFIG_QCOM_VA_MINIDUMP)		+= qcom_va_minidump.o
obj-$(CONFIG_QCOM_MINIDUMP_VIRTIO)	+= minidump_virtio.o
obj-$(CONFIG_QCOM_DEBUG_SYMBOL)		+= debug_symbol.o
# Vendor-added in-tree files missing from this Makefile.
obj-$(CONFIG_QCOM_SECURE_BUFFER)	+= secure_buffer.o
obj-y					+= mem_buf/
obj-$(CONFIG_QCOM_SMD_RPM)	+= rpm-proc.o smd-rpm.o
obj-$(CONFIG_QCOM_SMEM) +=	smem.o
obj-$(CONFIG_QCOM_SMEM_STATE) += smem_state.o
CFLAGS_smp2p.o := -I$(src)
obj-$(CONFIG_QCOM_SMP2P)	+= smp2p.o
obj-$(CONFIG_QCOM_SMSM)	+= smsm.o
obj-$(CONFIG_QCOM_SOCINFO)	+= socinfo.o
obj-$(CONFIG_QCOM_SPM)		+= spm.o
obj-$(CONFIG_QCOM_STATS)	+= qcom_stats.o
obj-$(CONFIG_QCOM_WCNSS_CTRL) += wcnss_ctrl.o
obj-$(CONFIG_QCOM_APR) += apr.o
obj-$(CONFIG_QCOM_LLCC) += llcc-qcom.o
obj-$(CONFIG_QCOM_KRYO_L2_ACCESSORS) +=	kryo-l2-accessors.o
obj-$(CONFIG_QCOM_ICC_BWMON)	+= icc-bwmon.o
qcom_ice-objs			+= ice.o
obj-$(CONFIG_QCOM_INLINE_CRYPTO_ENGINE)	+= qcom_ice.o
obj-$(CONFIG_QCOM_PBS) +=	qcom-pbs.o
