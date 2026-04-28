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
plus `Module.symvers` (MODVERSIONS=y) and 188 in-tree `.ko` files
under `lib/modules/<release>/kernel/`.

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
  bundle (`wcd939x-i2c.c` + helpers → `wcd_usbss_i2c.ko`). These are
  consumed by vendor's `display-drivers/msm.ko`; needed once Phase 3
  source-builds that module rather than pulling it from the OEM
  prebuilt set.

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
  vendor external modules tree. Its `README.md` documents what builds
  cleanly today and what's blocked behind oplus extension source
  (Phase 3).

## Open work

- **vendor/lineage local patch** — `vendor/lineage/build/tasks/kernel.mk`
  needs a one-liner to pass `modules` explicitly to external module
  wrappers (works around a `%:` catch-all firing on `all`). Currently
  applied in the local clone as branch `local-jm2-mka-modules-fix`;
  needs upstreaming or a jm2 fork.

- **AOSP genksyms prebuilt** — would replace the musl-static one we
  build ourselves. AOSP's `prebuilts/kernel-build-tools` doesn't ship
  it; would need to add a project to the manifest.

- **Phase 3 — full source-build** — see
  `jm2/android_kernel_oneplus_sm8850-modules/README.md`.

## Build host

- Arch Linux with system clang 22.1.3 at `/usr/bin/clang`
- Kernel: 6.12.23 (ACK android16-6.12 base merged with vendor)
- Output: `out/target/product/infiniti/obj/KERNEL_OBJ/`
