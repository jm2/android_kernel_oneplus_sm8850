# SPDX-License-Identifier: GPL-2.0-only
# Module layout follows drivers/soc/qcom/mem_buf/modules.bzl which is the
# vendor's source-of-truth for how these TUs bundle into Bazel-built .ko's.

# mem_buf_dev.ko
obj-$(CONFIG_QCOM_MEM_BUF_DEV)	+= mem_buf_dev.o
mem_buf_dev-y			:= mem-buf-dev.o mem-buf-ids.o mem_buf_dma_buf.o
mem_buf_dev-$(CONFIG_QCOM_MEM_BUF_DEV_GH) += mem-buf-dev-gh.o

# mem_buf.ko
obj-$(CONFIG_QCOM_MEM_BUF)	+= mem_buf.o
mem_buf-y			:= mem-buf.o
mem_buf-$(CONFIG_QCOM_MEM_BUF_GH) += mem-buf-gh.o

# mem_buf_msgq.ko (separate module, CONFIG_QCOM_MEM_BUF_MSGQ tristate)
obj-$(CONFIG_QCOM_MEM_BUF_MSGQ) += mem_buf_msgq.o
mem_buf_msgq-y			:= mem-buf-msgq.o
