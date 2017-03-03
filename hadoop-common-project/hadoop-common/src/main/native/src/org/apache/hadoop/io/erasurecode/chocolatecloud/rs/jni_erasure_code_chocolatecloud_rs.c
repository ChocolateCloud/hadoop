/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "org_apache_hadoop.h"
#include "chocolatecloud/jni_chocolatecloud.h"
#include "jni_chocolatecloud_rs.h"
#include "chocolatecloud/chocolatecloud_load.h"
#include "org_apache_hadoop_io_erasurecode_ErasureCodeChocolateCloudRS.h"

#ifdef UNIX
#include "config.h"
#endif

JNIEXPORT void JNICALL
Java_org_apache_hadoop_io_erasurecode_ErasureCodeChocolateCloudRS_loadLibrary
(JNIEnv *env, jclass myclass) {
  loadChocolateCloudRSLib(env, HADOOP_CHOCOLATECLOUD_RS_LIBRARY);
}

JNIEXPORT jstring JNICALL
Java_org_apache_hadoop_io_erasurecode_ErasureCodeChocolateCloudRS_getLibraryName
(JNIEnv *env, jclass myclass) {
  if (chocolateCloudLoader == NULL) {
    THROW(env, "java/lang/UnsatisfiedLinkError",
                             "Unavailable: library not loaded yet");
    return (jstring)NULL;
  }

  return (*env)->NewStringUTF(env, chocolateCloudLoader->libname);
}