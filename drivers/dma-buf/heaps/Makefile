# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_DMABUF_HEAPS_SYSTEM)	+= system_heap.o
obj-$(CONFIG_DMABUF_HEAPS_CMA)		+= cma_heap.o

# Vendor-added QCOM dma-buf heap. Only qcom_dma_heap.c has module_init; the
# rest are helper TUs referenced by name. Bundle them into one module
# (qcom_heaps.ko) so inter-helper symbol references resolve internally; the
# bundle name differs from any member .c so kbuild builds qcom_dma_heap.o
# from qcom_dma_heap.c instead of expecting qcom_heaps-y to provide it.
# deferred-free-helper.c has its own module_init/exit — keep it as a separate
# .ko so we don't end up with two init_module symbols in the bundle. It
# EXPORT_SYMBOLs the helpers that qcom_heaps.ko consumes.
obj-$(CONFIG_QCOM_DMABUF_HEAPS)	+= deferred-free-helper.o
obj-$(CONFIG_QCOM_DMABUF_HEAPS)	+= qcom_heaps.o
qcom_heaps-y			:= qcom_dma_heap.o
qcom_heaps-y			+= qcom_dt_parser.o
qcom_heaps-y			+= qcom_sg_ops.o
qcom_heaps-y			+= qcom_dma_heap_secure_utils.o
qcom_heaps-$(CONFIG_QCOM_DMABUF_HEAPS_SYSTEM)	+= qcom_system_heap.o qcom_dynamic_page_pool.o
qcom_heaps-$(CONFIG_QCOM_DMABUF_HEAPS_SYSTEM_SECURE)	+= qcom_secure_system_heap.o
qcom_heaps-$(CONFIG_QCOM_DMABUF_HEAPS_SYSTEM_MOVABLE)	+= qcom_system_movable_heap.o
qcom_heaps-$(CONFIG_QCOM_DMABUF_HEAPS_CMA)		+= qcom_cma_heap.o
qcom_heaps-$(CONFIG_QCOM_DMABUF_HEAPS_CARVEOUT)		+= qcom_carveout_heap.o
qcom_heaps-$(CONFIG_QCOM_DMABUF_HEAPS_TVM_CARVEOUT)	+= qcom_tvm_carveout_heap.o
qcom_heaps-$(CONFIG_QCOM_DMABUF_HEAPS_UBWCP)		+= qcom_ubwcp_heap.o
