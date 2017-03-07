/*
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "org_apache_hadoop.h"

#ifdef UNIX
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>

#include "config.h"
#endif

#ifdef WINDOWS
#include <Windows.h>
#endif

#ifndef _CHOCOLATECLOUD_LOAD_H_
#define _CHOCOLATECLOUD_LOAD_H_

#ifdef UNIX

typedef int (*__d_hdfs_ec_chocolate_cloud_rs_init)();
typedef int (*__d_hdfs_ec_chocolate_cloud_rs_exit)();
typedef int (*__d_hdfs_ec_chocolate_cloud_rs_encode)
(
    unsigned char**,
    unsigned char**,

    const unsigned,
    const unsigned,
    const int
);
typedef int (*__d_hdfs_ec_chocolate_cloud_rs_reconstruct)
(
    const unsigned,
    const unsigned,
    const int,

    unsigned char**,
    unsigned char**,

    const int*,
    const unsigned
);

#endif

#ifdef WINDOWS

typedef int (__cdecl *__d_hdfs_ec_chocolate_cloud_rs_init)();
typedef int (__cdecl *__d_hdfs_ec_chocolate_cloud_rs_exit)();
typedef int (__cdecl *__d_hdfs_ec_chocolate_cloud_rs_encode)
(
    unsigned char**,
    unsigned char**,

    const unsigned,
    const unsigned,
    const int
);
typedef int (__cdecl *__d_hdfs_ec_chocolate_cloud_rs_reconstruct)
(
    const unsigned,
    const unsigned,
    const int,

    unsigned char**,
    unsigned char**,

    const int*,
    const unsigned
);

#endif

typedef struct __ChocolateCloudLibLoader {
  // The loaded library handle
  void* libec;
  char* libname;

  __d_hdfs_ec_chocolate_cloud_rs_init hdfs_ec_chocolate_cloud_rs_init;
  __d_hdfs_ec_chocolate_cloud_rs_exit hdfs_ec_chocolate_cloud_rs_exit;
  __d_hdfs_ec_chocolate_cloud_rs_encode hdfs_ec_chocolate_cloud_rs_encode;
  __d_hdfs_ec_chocolate_cloud_rs_reconstruct hdfs_ec_chocolate_cloud_rs_reconstruct;
} ChocolateCloudLibLoader;

extern ChocolateCloudLibLoader* chocolateCloudLoader;

/**
 * A helper function to dlsym a 'symbol' from a given library-handle.
 */

#ifdef UNIX

static __attribute__ ((unused))
void *myDlsym(void *handle, const char *symbol) {
  void *func_ptr = dlsym(handle, symbol);
  return func_ptr;
}

/* A helper macro to dlsym the requisite dynamic symbol in NON-JNI env. */
#define EC_LOAD_DYNAMIC_SYMBOL(func_ptr, symbol) \
  if ((func_ptr = myDlsym(chocolateCloudLoader->libec, symbol)) == NULL) { \
    return "Failed to load symbol" symbol; \
  }

#endif

#ifdef WINDOWS

static FARPROC WINAPI myDlsym(HMODULE handle, LPCSTR symbol) {
  FARPROC func_ptr = GetProcAddress(handle, symbol);
  return func_ptr;
}

/* A helper macro to dlsym the requisite dynamic symbol in NON-JNI env. */
#define EC_LOAD_DYNAMIC_SYMBOL(func_type, func_ptr, symbol) \
  if ((func_ptr = (func_type)myDlsym(chocolateCloudLoader->libec, symbol)) == NULL) { \
    return "Failed to load symbol" symbol; \
  }

#endif

/**
 * Return 0 if not support, 1 otherwise.
 */
int build_support_chocolate_cloud_rs();

/**
 * Initialize and load erasure code library, returning error message if any.
 *
 * @param err     The err message buffer.
 * @param err_len The length of the message buffer.
 */
void load_chocolatecloud_lib(char* err, size_t err_len, const char*);

#endif //_CHOCOLATECLOUD_LOAD_H_