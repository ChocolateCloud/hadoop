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
#include "chocolatecloud_rs_erasure_code.h"
#include "jni_chocolatecloud_rs.h"
#include "chocolatecloud_rs_load.h"
#include "../../jni_common.h"
#include "org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawDecoder.h"

typedef struct _RSDecoder {
  ChocolateCloudRSCoder decoder;
  unsigned char* inputs[MAXUNITSNUM];
  unsigned char* outputs[MAXUNITSNUM];
} RSDecoder;

JNIEXPORT void JNICALL
Java_org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawDecoder_initImpl(
JNIEnv *env, jobject thiz, jint numDataUnits, jint numParityUnits) {
  RSDecoder* rsDecoder = (RSDecoder*)malloc(sizeof(RSDecoder));
  memset(rsDecoder, 0, sizeof(*rsDecoder));
  initChocolateCloudRSCoder(&rsDecoder->decoder, (int)numDataUnits, (int)numParityUnits);

  setChocolateCloudRSCoder(env, thiz, &rsDecoder->decoder);
}

JNIEXPORT void JNICALL
Java_org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawDecoder_decodeImpl(
JNIEnv *env, jobject thiz, jobjectArray inputs, jintArray inputOffsets,
jint dataLen, jintArray erasedIndexes, jobjectArray outputs,
jintArray outputOffsets) {
  RSDecoder* rsDecoder = (RSDecoder*)getChocolateCloudRSCoder(env, thiz);

  int numDataUnits = rsDecoder->decoder.numDataUnits;
  int numParityUnits = rsDecoder->decoder.numParityUnits;
  int chunkSize = (int)dataLen;

  int* tmpErasedIndexes = (int*)(*env)->GetIntArrayElements(env,
                                                        erasedIndexes, NULL);
  int numErased = (*env)->GetArrayLength(env, erasedIndexes);
  getInputs(env, inputs, inputOffsets, rsDecoder->inputs,
                                               numDataUnits + numParityUnits);
  getOutputs(env, outputs, outputOffsets, rsDecoder->outputs, numErased);

  chocolateCloudRSReconstruct(&rsDecoder->decoder, chunkSize,
                            rsDecoder->inputs, rsDecoder->outputs,
                            tmpErasedIndexes, numErased);
}

JNIEXPORT void JNICALL
Java_org_apache_hadoop_io_erasurecode_rawcoder_NativeChocolateCloudRSRawDecoder_destroyImpl(
JNIEnv *env, jobject thiz) {
  RSDecoder* rsDecoder = (RSDecoder*)getChocolateCloudRSCoder(env, thiz);
  exitChocolateCloudRSCoder();
  free(rsDecoder);
}