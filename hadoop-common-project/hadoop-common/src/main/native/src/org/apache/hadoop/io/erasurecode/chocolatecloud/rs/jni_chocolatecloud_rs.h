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

#ifndef _JNI_CHOCOLATECLOUD_RS_H_
#define _JNI_CHOCOLATECLOUD_RS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jni.h>

#include "chocolatecloud_rs_erasure_coder.h"

void loadChocolateCloudRSLib(JNIEnv *env);

void setChocolateCloudRSCoder(JNIEnv* env, jobject thiz, ChocolateCloudRSCoder* coder);

ChocolateCloudRSCoder* getChocolateCloudRSCoder(JNIEnv* env, jobject thiz);

void getChocolateCloudRSInputs(JNIEnv *env, jobjectArray inputs, jintArray inputOffsets,
                              unsigned char** destInputs, int num);

void getChocolateCloudRSOutputs(JNIEnv *env, jobjectArray outputs, jintArray outputOffsets,
                              unsigned char** destOutputs, int num);
#endif //_JNI_CHOCOLATECLOUD_RS_H_