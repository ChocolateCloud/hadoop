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
#include "chocolatecloud_rs_load.h"
#include "chocolatecloud_rs_erasure_code.h"

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

ChocolateCloudRSLibLoader* chocolateCloudRSLoader;

/**
 *  chocolatecloud_rs_load.c
 *  Utility of loading the ChocolateCloud-RS library and the required functions.
 */

static const char* load_chocolatecloud_rs_functions() {
#ifdef UNIX
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_init),
                            "hdfs_ec_chocolate_cloud_rs_init");
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_exit),
                            "hdfs_ec_chocolate_cloud_rs_exit");
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_encode),
                            "hdfs_ec_chocolate_cloud_rs_encode");
  EC_LOAD_DYNAMIC_SYMBOL((chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_reconstruct),
                            "hdfs_ec_chocolate_cloud_rs_reconstruct");
#endif

#ifdef WINDOWS
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_init,
                            (chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_init),
                            "hdfs_ec_chocolate_cloud_rs_init");
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_exit,
                            (chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_exit),
                            "hdfs_ec_chocolate_cloud_rs_exit");
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_encode,
                            (chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_encode),
                            "hdfs_ec_chocolate_cloud_rs_encode");
  EC_LOAD_DYNAMIC_SYMBOL(__d_hdfs_ec_chocolate_cloud_rs_reconstruct,
                            (chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_reconstruct),
                            "hdfs_ec_chocolate_cloud_rs_reconstruct");
#endif

  return NULL;
}

void load_chocolatecloud_rs_lib(char* err, size_t err_len) {
  const char* errMsg;
  const char* library = NULL;
#ifdef UNIX
  Dl_info dl_info;
#else
  LPTSTR filename[MAX_PATH];
#endif

  err[0] = '\0';

  if (chocolateCloudRSLoader != NULL) {
    return;
  }
  chocolateCloudRSLoader = calloc(1, sizeof(ChocolateCloudRSLibLoader));
  memset(chocolateCloudRSLoader, 0, sizeof(ChocolateCloudRSLibLoader));

  // Load ChocolateCloud-RS library
  #ifdef UNIX
  chocolateCloudRSLoader->libec = dlopen(HADOOP_CHOCOLATECLOUD_RS_LIBRARY, RTLD_LAZY);
  if (chocolateCloudRSLoader->libec == NULL) {
    snprintf(err, err_len, "Failed to load %s (%s). Please make sure that /usr/lib/%s exists and it is readable.",
                             HADOOP_CHOCOLATECLOUD_RS_LIBRARY, dlerror(), HADOOP_CHOCOLATECLOUD_RS_LIBRARY);
    return;
  }
  // Clear any existing error
  dlerror();
  #endif

  #ifdef WINDOWS
  chocolateCloudRSLoader->libec = LoadLibrary(HADOOP_CHOCOLATECLOUD_RS_LIBRARY);
  if (chocolateCloudRSLoader->libec == NULL) {
    snprintf(err, err_len, "Failed to load %s (%s). Please make sure that %s exists and it is readable.",
                             HADOOP_CHOCOLATECLOUD_RS_LIBRARY, GetLastError(), HADOOP_CHOCOLATECLOUD_RS_LIBRARY);
    return;
  }
  #endif

  errMsg = load_chocolatecloud_rs_functions(chocolateCloudRSLoader->libec);
  if (errMsg != NULL) {
    snprintf(err, err_len, "Loading functions from ChocolateCloud-RS library failed: %s", errMsg);
  }

#ifdef UNIX
  if(dladdr(chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_encode, &dl_info)) {
    library = dl_info.dli_fname;
  }
#else
  if (GetModuleFileName(chocolateCloudRSLoader->libec, filename, MAX_PATH) > 0) {
    library = filename;
  } else {
    snprintf(err, err_len, "Failed to get filename: %s", GetLastError());
  }
#endif

  if (library == NULL) {
    library = HADOOP_CHOCOLATECLOUD_RS_LIBRARY;
  }

  chocolateCloudRSLoader->libname = strdup(library);

  h_hdfs_ec_chocolate_cloud_rs_init();
}

int build_support_chocolate_cloud_rs() {
#ifdef HADOOP_CHOCOLATECLOUD_RS_LIBRARY
  return 1;
#else
  return 0;
#endif
}