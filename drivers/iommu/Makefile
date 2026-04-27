# SPDX-License-Identifier: GPL-2.0
obj-y += amd/ intel/ arm/ iommufd/
obj-$(CONFIG_IOMMU_API) += iommu.o
obj-$(CONFIG_IOMMU_API) += iommu-traces.o
obj-$(CONFIG_IOMMU_API) += iommu-sysfs.o
obj-$(CONFIG_IOMMU_DEBUGFS) += iommu-debugfs.o
obj-$(CONFIG_IOMMU_DMA) += dma-iommu.o
obj-$(CONFIG_IOMMU_IO_PGTABLE) += io-pgtable.o
obj-$(CONFIG_IOMMU_IO_PGTABLE_ARMV7S) += io-pgtable-arm-v7s.o
obj-$(CONFIG_IOMMU_IO_PGTABLE_LPAE) += io-pgtable-arm.o io-pgtable-arm-common.o
obj-$(CONFIG_IOMMU_IO_PGTABLE_DART) += io-pgtable-dart.o
obj-$(CONFIG_IOMMU_IOVA) += iova.o
obj-$(CONFIG_OF_IOMMU)	+= of_iommu.o
obj-$(CONFIG_MSM_IOMMU) += msm_iommu.o
obj-$(CONFIG_IPMMU_VMSA) += ipmmu-vmsa.o
obj-$(CONFIG_IRQ_REMAP) += irq_remapping.o
obj-$(CONFIG_MTK_IOMMU) += mtk_iommu.o
obj-$(CONFIG_MTK_IOMMU_V1) += mtk_iommu_v1.o
obj-$(CONFIG_OMAP_IOMMU) += omap-iommu.o
obj-$(CONFIG_OMAP_IOMMU_DEBUG) += omap-iommu-debug.o
obj-$(CONFIG_ROCKCHIP_IOMMU) += rockchip-iommu.o
obj-$(CONFIG_SUN50I_IOMMU) += sun50i-iommu.o
obj-$(CONFIG_TEGRA_IOMMU_SMMU) += tegra-smmu.o
obj-$(CONFIG_EXYNOS_IOMMU) += exynos-iommu.o
obj-$(CONFIG_FSL_PAMU) += fsl_pamu.o fsl_pamu_domain.o
obj-$(CONFIG_S390_IOMMU) += s390-iommu.o
obj-$(CONFIG_HYPERV_IOMMU) += hyperv-iommu.o
obj-$(CONFIG_VIRTIO_IOMMU) += virtio-iommu.o
obj-$(CONFIG_IOMMU_SVA) += iommu-sva.o
obj-$(CONFIG_IOMMU_IOPF) += io-pgfault.o
obj-$(CONFIG_SPRD_IOMMU) += sprd-iommu.o
obj-$(CONFIG_APPLE_DART) += apple-dart.o
obj-$(CONFIG_PKVM_PVIOMMU) += pkvm-pviommu.o

# QCOM IOMMU helper sources added by the vendor overlay but never wired into
# this Makefile. Each header gates its real declarations behind a specific
# CONFIG_*; bundle all of them into a single module (qcom-iommu-helpers.ko)
# so inter-helper symbol references resolve internally without needing
# EXPORT_SYMBOL on every cross-call. ARM_SMMU_QCOM selects each gate in
# drivers/iommu/Kconfig and provides the only module_init() in the bundle.
obj-$(CONFIG_ARM_SMMU_QCOM) += qcom-iommu-helpers.o
qcom-iommu-helpers-$(CONFIG_ARM_SMMU_QCOM)         += qcom-iommu-util.o
qcom-iommu-helpers-$(CONFIG_QCOM_DMA_IOMMU_GENERIC) += qcom-dma-iommu-generic.o
qcom-iommu-helpers-$(CONFIG_IOMMU_IO_PGTABLE_FAST)  += qcom-io-pgtable-alloc.o
qcom-iommu-helpers-$(CONFIG_IOMMU_IO_PGTABLE_FAST)  += qcom-io-pgtable-arm.o
qcom-iommu-helpers-$(CONFIG_IOMMU_IO_PGTABLE_FAST)  += io-pgtable-fast.o
qcom-iommu-helpers-$(CONFIG_DMA_MAPPING_FAST)       += dma-mapping-fast.o
qcom-iommu-helpers-$(CONFIG_QTI_IOMMU_SUPPORT)      += iommu-logger.o
qcom-iommu-helpers-$(CONFIG_QCOM_LAZY_MAPPING)      += msm_dma_iommu_mapping.o
