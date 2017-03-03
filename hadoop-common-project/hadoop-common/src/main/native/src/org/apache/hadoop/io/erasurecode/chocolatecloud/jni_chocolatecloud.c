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
#include "chocolatecloud_load.h"
#include "chocolatecloud_erasure_code.h"
#include "jni_chocolatecloud.h"

void setChocolateCloudCoder(JNIEnv* env, jobject thiz, ChocolateCloudCoder* pCoder) {
  jclass clazz = (*env)->GetObjectClass(env, thiz);
  jfieldID fid = (*env)->GetFieldID(env, clazz, "nativeCoder", "J");
  if (fid == NULL) {
    THROW(env, "java/lang/UnsatisfiedLinkError",
                                    "Field nativeCoder not found");
  }
  (*env)->SetLongField(env, thiz, fid, (jlong) pCoder);
}

ChocolateCloudCoder* getChocolateCloudCoder(JNIEnv* env, jobject thiz) {
  jclass clazz;
  jfieldID fid;
  ChocolateCloudCoder* pCoder;

  clazz = (*env)->GetObjectClass(env, thiz);
  fid = (*env)->GetFieldID(env, clazz, "nativeCoder", "J");
  if (fid == NULL) {
    THROW(env, "java/lang/UnsatisfiedLinkError",
                                    "Field nativeCoder not found");
  }
  pCoder = (ChocolateCloudCoder*)(*env)->GetLongField(env, thiz, fid);

  return pCoder;
}