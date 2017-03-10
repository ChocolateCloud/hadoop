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
#include "chocolatecloud/chocolatecloud_erasure_code.h"
#include "chocolatecloud/jni_chocolatecloud.h"
#include "jni_chocolatecloud_rs.h"
#include "chocolatecloud/chocolatecloud_load.h"
#include "../../jni_common.h"
#include "org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawEncoder.h"

typedef struct _RSEncoder {
  ChocolateCloudCoder encoder;
  unsigned char* inputs[MAXUNITSNUM];
  unsigned char* outputs[MAXUNITSNUM];
} RSEncoder;

JNIEXPORT void JNICALL
Java_org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawEncoder_initImpl(
JNIEnv *env, jobject thiz, jint numDataUnits, jint numParityUnits) {
  RSEncoder* rsEncoder = (RSEncoder*)malloc(sizeof(RSEncoder));
  memset(rsEncoder, 0, sizeof(*rsEncoder));
  initChocolateCloudCoder(&rsEncoder->encoder, (int)numDataUnits, (int)numParityUnits);

  setChocolateCloudCoder(env, thiz, &rsEncoder->encoder);
}

JNIEXPORT void JNICALL
Java_org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawEncoder_encodeImpl(
JNIEnv *env, jobject thiz, jobjectArray inputs, jintArray inputOffsets,
jint dataLen, jobjectArray outputs, jintArray outputOffsets) {
  RSEncoder* rsEncoder = (RSEncoder*)getChocolateCloudCoder(env, thiz);

  int numDataUnits = rsEncoder->encoder.numDataUnits;
  int numParityUnits = rsEncoder->encoder.numParityUnits;
  int chunkSize = (int)dataLen;

  getInputs(env, inputs, inputOffsets, rsEncoder->inputs, numDataUnits);
  getOutputs(env, outputs, outputOffsets, rsEncoder->outputs, numParityUnits);

  chocolateCloudEncode(rsEncoder->inputs, rsEncoder->outputs,
                        &rsEncoder->encoder, chunkSize);
}

JNIEXPORT void JNICALL
Java_org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawEncoder_destroyImpl(
JNIEnv *env, jobject thiz) {
  RSEncoder* rsEncoder = (RSEncoder*)getChocolateCloudCoder(env, thiz);
  exitChocolateCloudCoder();
  free(rsEncoder);
}