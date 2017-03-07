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
#include "chocolatecloud_load.h"
#include "chocolatecloud_erasure_code.h"

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

ChocolateCloudLibLoader* chocolateCloudLoader;

/**
 *  chocolatecloud_load.c
 *  Utility of loading the ChocolateCloud library and the required functions.
 */

static const char* load_functions() {
#ifdef UNIX
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_init),
                            "hdfs_ec_chocolate_cloud_rs_init");
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_exit),
                            "hdfs_ec_chocolate_cloud_rs_exit");
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_encode),
                            "hdfs_ec_chocolate_cloud_rs_encode");
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_reconstruct),
                            "hdfs_ec_chocolate_cloud_rs_reconstruct");
#endif

#ifdef WINDOWS
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_init,
                            (chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_init),
                            "hdfs_ec_chocolate_cloud_rs_init");
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_exit,
                            (chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_exit),
                            "hdfs_ec_chocolate_cloud_rs_exit");
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_encode,
                            (chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_encode),
                            "hdfs_ec_chocolate_cloud_rs_encode");
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_reconstruct,
                            (chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_reconstruct),
                            "hdfs_ec_chocolate_cloud_rs_reconstruct");
#endif

  return NULL;
}

void load_chocolatecloud_lib(char* err, size_t err_len, const char* library_name) {
  const char* errMsg;
  const char* library = NULL;
#ifdef UNIX
  Dl_info dl_info;
#else
  LPTSTR filename = NULL;
#endif

  err[0] = '\0';

  if (chocolateCloudLoader != NULL) {
    return;
  }
  chocolateCloudLoader = calloc(1, sizeof(ChocolateCloudLibLoader));
  memset(chocolateCloudLoader, 0, sizeof(ChocolateCloudLibLoader));

  // Load ChocolateCloud library
  #ifdef UNIX
  chocolateCloudLoader->libec = dlopen(library_name, RTLD_LAZY);
  if (chocolateCloudLoader->libec == NULL) {
    snprintf(err, err_len, "Failed to load %s (%s). Please make sure that /usr/lib/%s exists and it is readable.",
                             library_name, dlerror(), library_name);
    return;
  }
  // Clear any existing error
  dlerror();
  #endif

  #ifdef WINDOWS
  chocolateCloudLoader->libec = LoadLibrary(library_name);
  if (chocolateCloudLoader->libec == NULL) {
    snprintf(err, err_len, "Failed to load %s", library_name);
    return;
  }
  #endif

  errMsg = load_functions(chocolateCloudLoader->libec);
  if (errMsg != NULL) {
    snprintf(err, err_len, "Loading functions from ChocolateCloud library failed: %s", errMsg);
  }

#ifdef UNIX
  if(dladdr(chocolateCloudLoader->hdfs_ec_chocolate_cloud_rs_encode, &dl_info)) {
    library = dl_info.dli_fname;
  }
#else
  if (GetModuleFileName(chocolateCloudLoader->libec, filename, 256) > 0) {
    library = filename;
  }
#endif

  if (library == NULL) {
    library = library_name;
  }

  chocolateCloudLoader->libname = strdup(library);

  h_hdfs_ec_chocolate_cloud_rs_init();
}

int build_support_chocolatecloud(const char* library_name) {
#ifdef library_name
  return 1;
#else
  return 0;
#endif
}