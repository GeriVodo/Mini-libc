/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __TYPES_H__
#define __TYPES_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>
typedef long time_t;
typedef long suseconds_t;
typedef long ssize_t;
typedef unsigned long size_t;
typedef long off_t;
typedef int pid_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;

#ifdef __cplusplus
}
#endif

#endif
