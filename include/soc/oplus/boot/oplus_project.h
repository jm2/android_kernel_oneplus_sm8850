/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Lineage source-build wrapper. Vendor source uses two paths
 * interchangeably: <soc/oplus/boot/oplus_project.h> and
 * <soc/oplus/system/oplus_project.h>. The actual file lives under
 * system/. Forward to it so both paths resolve.
 */
#ifndef _OPLUS_PROJECT_H_BOOT_FWD_
#define _OPLUS_PROJECT_H_BOOT_FWD_
#include <soc/oplus/system/oplus_project.h>
#endif
