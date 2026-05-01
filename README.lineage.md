# jm2/android_kernel_oneplus_sm8850 — Lineage source-build notes

This is the OnePlus / OplusOSS SM8850 kernel tree (canoe / OnePlus 15 /
infiniti) carrying patches needed to build under LineageOS 23.2 (Android
16, bp4a) via `mka kernel`. Vendor's upstream flow is Kleaf/Bazel; this
fork makes the same source build through plain kbuild + mka kernel.

## Quick start

```bash
# From the LineageOS root (not this repo)
source build/envsetup.sh
lunch lineage_infiniti-bp4a-userdebug
mka kernel
```

That produces `out/target/product/infiniti/obj/KERNEL_OBJ/{vmlinux,arch/arm64/boot/Image}`
plus `Module.symvers` (MODVERSIONS=y) and ~190 in-tree `.ko` files
under `lib/modules/<release>/kernel/`. Combined with the 30 source-built
externals from `kernel/oneplus/sm8850-modules/` and the 568 OEM
prebuilts in `device/oneplus/infiniti-kernel/`, the build lands at
**0 depmod symbol errors** (down from 110 before Phase A).

For `make modules Image` outside `mka kernel` (faster iteration cycle),
use the same env (clang/lld from `/usr`, the genksyms prebuilt below)
with `KCPPFLAGS=-I$(BUILD_TOP)/$(TARGET_KERNEL_SOURCE)` and
`CONFIG_OPLUS_DEVICE_DTBS=y`.

## What this fork carries on top of upstream

In commit order on `lineage-23.2`:

- **`kernel: enable LineageOS standalone source build`** — restores the
  Makefile `obj-$(CONFIG_*)` lines and Kconfig stanzas that vendor's
  Kleaf flow makes redundant via `kernel_build.module_outs` in
  `BUILD.bazel`. Categories covered: `drivers/soc/qcom/` (CRM, secure
  buffer, mem_buf, debug_symbol), `drivers/iommu/` (QCOM helpers
  bundled into `qcom-iommu-helpers.ko`), `drivers/hwtracing/coresight/`
  (csr, tmc-sec, byte-cntr, tmc-usb), `drivers/firmware/qcom/` (TZMEM),
  `drivers/usb/gadget/function/` (USB_F_QDSS gate). The companion
  workaround config fragment lives in
  `arch/arm64/configs/lineage_genksyms_workaround.config`.

- **`kernel: finish standalone build — modpost clean, vmlinux + 137 .ko`** —
  fixes the duplicate-symbol surface in `include/linux/usb/dwc3-msm.h`
  (`#else` stubs needed `static inline`), restores the `menuconfig
  SPMI` parent stanza that vendor stripped, and pins
  `CONFIG_ARCH_QCOM=y` + `CONFIG_KASAN=n` (clang 22 / kernel 6.12
  `__SANITIZE_ADDRESS__` redefinition) in the workaround fragment.

- **`kernel: enable MODVERSIONS=y end-to-end with musl-static genksyms`** —
  ships a musl-static `scripts/genksyms/genksyms.prebuilt` (~78 KB)
  that sidesteps the `free_node`/`free_list` double-free in vendor's
  parser when fed real preprocessed kernel input under glibc 2.43 or
  musl mallocng. The build script that produces this binary is at
  `~/android/build_musl_genksyms.sh` (outside this repo). The kernel's
  `scripts/genksyms/Makefile` is patched to `cp` the prebuilt at
  HOSTCP time instead of compiling. Also restores `REGMAP_QTI_DEBUGFS`,
  bundles `minidump_smem.o` into `qcom_minidump.ko`.

- **`kernel: absolutize KBUILD_EXTMOD once in the parent make`** —
  patches `Makefile` so that when `mka kernel` invokes external
  modules with relative `M=` and `O=$(KBUILD_OUTPUT)`, kbuild's
  `O=`-driven cwd switch doesn't break the `$(src)/Makefile` lookup
  in `scripts/Makefile.build`. Works because the fix runs in the
  first make invocation (cwd still = kernel src) and exports the
  resolved path via env so the sub-make sees `origin == environment`
  and skips re-resolving.

- **`kernel: prep for hybrid source-build / OEM-prebuilt module set`** —
  enables DRM display helpers (`DRM_DISPLAY_HELPER`,
  `DRM_DISPLAY_DP_HELPER`) by adding visible Kconfig prompts, plus
  `TYPEC_MUX_WCD939X_USBSS=m` and a restored `QCOM_WCD_USBSS_I2C`
  bundle (`wcd939x-i2c.c` + helpers → `wcd_usbss_i2c.ko`). Consumed
  by `display-drivers/msm.ko` (now source-built — Phase D).

- **`kernel: Phase A — restore RPMSG/REMOTEPROC/GUNYAH/SCMI/SMEM/ICC framework`** —
  restores the framework Kconfig stanzas + Makefile entries that
  vendor's Kleaf flow expressed via `module_outs`. Resolves ~85 of
  the original 110 unresolved depmod symbols
  (`rproc_*`/`devm_rproc_*`, `rpmsg_*`/`__register_rpmsg_driver`,
  `gunyah_*`, `scmi_*`, `qcom_smem_state_*`, `qcom_icc_*`).

- **`kernel: Phase B kernel-side support — gh_arm_drv bundle + oplus_project.h shim`** —
  `gh_arm_drv-y := gh_arm.o irq.o reset.o` in
  `arch/arm64/gunyah/Makefile`. New header
  `include/soc/oplus/boot/oplus_project.h` forward-shims to
  `<soc/oplus/system/oplus_project.h>` so vendor source's
  `<soc/oplus/boot/...>` includes resolve. Pairs with the modules-
  side Phase B that added Kbuilds/Makefiles for the four oplus
  device-info modules.

- **`kernel: Phase C residuals — UFS CRYPTO QTI gate + arm64 gunyah Kconfig source`** —
  `SCSI_UFS_CRYPTO_QTI` Kconfig + Makefile entry, plus
  `source "arch/arm64/gunyah/Kconfig"` from `arch/arm64/Kconfig`.
  Combined with the modules-side `OPLUS_FEATURE_CAMERA_COMMON`
  bundling, gets `mka kernel` to exit 0.

- **`kernel: Phase D residuals — altmode-glink + panel_event_notifier + qti_pmic_glink`** —
  three more in-tree modules `drivers/soc/qcom/` that Kleaf expressed
  via `module_outs`: `qti_pmic_glink`, `altmode-glink`,
  `panel_event_notifier`, plus their Kconfig stanzas. Required by the
  newly-source-built `msm_drm.ko`.

- **`kernel: Phase F — resolve last 2 depmod prebuilts (zram_opt + sched_ext)`** —
  the last two unresolved-symbol producers needed for the full OEM
  prebuilt set to merge in cleanly:
  - `free_zram_is_ok`: in-tree stub at
    `drivers/block/zram/hybridswap_stub.c` linked into `zram.ko`,
    plus `hybridswap` symlink fix (5x ../ → 4x ../).
  - `__tracepoint_android_vh_scx_restore_flags`: `DECLARE_HOOK` in
    `include/trace/hooks/sched.h` + `EXPORT_TRACEPOINT_SYMBOL_GPL`
    in `kernel/sched/vendor_hooks.c`.

  After this, the device-side filter-out of `oplus_bsp_zram_opt.ko`
  / `oplus_bsp_sched_ext.ko` was dropped. **0 depmod symbol errors.**

- **`kernel: restore drivers/soc/qcom/sps/Makefile (vendor-strip)`** —
  same vendor-strip pattern as Phase A: vendor ships `sps/` as a
  Bazel target via `modules.bzl` but no parent Makefile, so the
  in-tree make build couldn't pick up `sps_drv.ko`. Restores the
  Makefile with the seven-source bundle.

- **`dtb: retarget vendor symlink to sm8850-modules layout`** —
  `arch/arm64/boot/dts/vendor` was a symlink resolving to a
  non-existent path (`kernel/oneplus/qcom/opensource/devicetree`),
  so the kernel's in-tree `arch/arm64/boot/dts/Makefile` couldn't
  traverse the vendor DTS via `subdir-y += vendor`. The actual
  location is under `kernel/oneplus/sm8850-modules/kernel_platform/
  qcom/opensource/devicetree`. Retargeting the symlink restores
  in-tree dtbs traversal so `make dtbs` produces the canoe SoC
  bases + the 4 fat composed bases (canoe-{,v2,tp,tp-v2}-fat.dtb)
  authored in the sm8850-modules fork. See that fork's Phase G
  for the full DTB source-compose story.

## Genksyms prebuilt

`scripts/genksyms/genksyms.prebuilt` is a static x86_64-linux-musl ELF.
Rebuild with:

```bash
~/android/build_musl_genksyms.sh
```

The script pins:
- AOSP clang at `prebuilts/clang/host/linux-x86/clang-r563880`
- musl sysroot at `prebuilts/build-tools/sysroots/x86_64-unknown-linux-musl`
- bison/flex at `prebuilts/build-tools/linux-x86/bin`

The patch applied to `genksyms.c` at build time (in a tmpdir, source
tree stays clean): `void free_node(...) { (void)node; }` — leak rather
than free, since genksyms is a one-shot tool and the parser
double-frees on multi-declarator extern decls like
`extern char __irqentry_text_start[], __irqentry_text_end[];` when
they recur in preprocessed input.

## Companion repos

- [`jm2/android_device_oneplus_sm8850-common`](../sm8850-common/) —
  device tree. `BoardConfigCommon.mk` sets `TARGET_KERNEL_CLANG_PATH`,
  `KCPPFLAGS=-I$(abspath $(TARGET_KERNEL_SOURCE))`, the
  `TARGET_KERNEL_CONFIG` fragment list, and the hybrid
  `BOARD_VENDOR_KERNEL_MODULES` wildcard for OEM prebuilts.

- [`jm2/android_kernel_oneplus_sm8850-modules`](../sm8850-modules/) —
  vendor external modules tree. Its `README.md` documents the 30
  source-built externals and the Phase A-F audit trail.

- [`jm2/android_vendor_lineage`](../../../vendor/lineage/) — three
  patches against `build/tasks/kernel.mk` (modules-target wrapper fix,
  `BOARD_VENDOR_KERNEL_MODULES` merge into source-build flow, soft-fail
  on missing `BOARD_*_KERNEL_MODULES_LOAD` entries). See
  `README.lineage-jm2.md`.

## Open upstream work

- **AOSP genksyms prebuilt.** Would replace the musl-static one we
  build ourselves. AOSP's `prebuilts/kernel-build-tools` doesn't ship
  it; would need to add a project to the manifest.

- **vendor/lineage upstreaming.** All three patches in the
  `vendor/lineage` jm2 fork are small, self-contained, and reproduce
  on any LineageOS build that uses the relevant `BOARD_*` knobs.
  Worth landing upstream so the fork can be retired.

## Build host

- Arch Linux with system clang 22.1.3 at `/usr/bin/clang`
- Kernel: 6.12.23 (ACK android16-6.12 base merged with vendor)
- Output: `out/target/product/infiniti/obj/KERNEL_OBJ/`
