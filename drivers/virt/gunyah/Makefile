# SPDX-License-Identifier: GPL-2.0

# Vendor source uses two include patterns the default kbuild flags
# don't handle:
#   #include "drivers/virt/gunyah/rsc_mgr.h"  → -I$(srctree)
#   #include "mem-prot.h"                      → -I$(srctree)/include/linux
ccflags-y += -I$(srctree) -I$(srctree)/include/linux

obj-$(CONFIG_GUNYAH_HYPERCALLS)		+= gunyah.o

gunyah_rsc_mgr-y += rsc_mgr.o rsc_mgr_rpc.o vm_mgr.o vm_mgr_mem.o
gunyah_rsc_mgr-$(CONFIG_DMA_CMA) += vm_mgr_cma_mem.o
obj-$(CONFIG_GUNYAH) += gunyah_rsc_mgr.o gunyah_vcpu.o
obj-$(CONFIG_GUNYAH_QCOM_TRUSTED_VM) += gunyah_qtvm.o
obj-$(CONFIG_GUNYAH_PLATFORM_HOOKS) += gunyah_platform_hooks.o
obj-$(CONFIG_GUNYAH_QCOM_PLATFORM) += gunyah_qcom.o
obj-$(CONFIG_GUNYAH_IRQFD) += gunyah_irqfd.o
obj-$(CONFIG_GUNYAH_IOEVENTFD) += gunyah_ioeventfd.o

# Vendor-stripped Makefile entries restored from drivers/virt/gunyah/modules.bzl.
# Each registry.register() entry there describes one .ko bundle gated on
# one CONFIG. Without these obj-$(CONFIG_*) lines, the source files are
# never compiled even when the configs are =m, leading to undefined symbols
# in modules that consume the gunyah RM/notifier APIs (mem_buf_dev.ko etc.).

obj-$(CONFIG_GH_CTRL)             += gh_ctrl.o
obj-$(CONFIG_GH_DBL)              += gh_dbl.o
obj-$(CONFIG_GH_IRQ_LEND)         += gh_irq_lend.o
obj-$(CONFIG_GH_MEM_NOTIFIER)     += gh_mem_notifier.o
obj-$(CONFIG_GH_RM_HEAP_MANAGER)  += gh_rm_heap_manager.o
obj-$(CONFIG_GH_MSGQ)             += gh_msgq.o
obj-$(CONFIG_GH_PANIC_NOTIFIER)   += gh_panic_notifier.o
obj-$(CONFIG_GH_RM_BOOSTER)       += gh_rm_booster.o

gh_rm_drv-y                       := gh_rm_core.o gh_rm_iface.o
obj-$(CONFIG_GH_RM_DRV)           += gh_rm_drv.o

obj-$(CONFIG_GH_VIRT_WATCHDOG)    += gh_virt_wdt.o
obj-$(CONFIG_GH_GUEST_POPS)       += gh_guest_pops.o
obj-$(CONFIG_GH_VIRTIO_PCI_EDGE)  += gh_virtio_pci_edge.o

gunyah_loader-y                   := gh_main.o gh_secure_vm_loader.o \
                                     gh_secure_vm_virtio_backend.o gh_proxy_sched.o
obj-$(CONFIG_GH_SECURE_VM_LOADER) += gunyah_loader.o

obj-$(CONFIG_GH_VCPU_MGR)         += gh_vcpu_mgr.o
obj-$(CONFIG_GUNYAH_TRACE)        += gunyah_trace.o
