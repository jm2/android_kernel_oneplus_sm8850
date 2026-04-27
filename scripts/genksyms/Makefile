# SPDX-License-Identifier: GPL-2.0

# scripts/genksyms's Yacc/Lex parser has a pre-existing heap bug that the
# glibc 2.43 (Arch Linux) tcache double-free check trips on; the host build
# crashes on real preprocessed input the moment a CONFIG_MODVERSIONS=y kernel
# tries to compute symbol versions. Until the upstream fix lands or distros
# settle, ship a musl-static prebuilt at scripts/genksyms/genksyms.prebuilt
# and copy it into the build dir instead of compiling.
#
# Note: we deliberately do NOT use `hostprogs-always-y += genksyms` here.
# That would pull in scripts/Makefile.host's host-csingle / host-cmulti
# recipes — they would either override our copy rule (rule-redefinition
# warning, last definition wins) or successfully invoke the host gcc/clang
# that crashes. Instead we register the target via plain `always-y` so
# kbuild walks into this directory and builds it via our own recipe.
#
# To rebuild the prebuilt:
#   ~/android/build_musl_genksyms.sh
# It produces a static x86_64-linux-musl ELF that is host-libc-independent.

always-y	+= genksyms

quiet_cmd_genksyms_copy = HOSTCP  $@
      cmd_genksyms_copy = cp -f $< $@ && chmod +x $@

$(obj)/genksyms: $(src)/genksyms.prebuilt FORCE
	$(call if_changed,genksyms_copy)
