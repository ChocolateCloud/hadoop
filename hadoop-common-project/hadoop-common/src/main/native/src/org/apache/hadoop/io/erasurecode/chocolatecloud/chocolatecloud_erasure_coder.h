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

/**
 * This is a sample program illustrating how to use the ChocolateCloud library.
 */

#ifndef _CHOCOLATECLOUD_ERASURE_CODER_H_
#define _CHOCOLATECLOUD_ERASURE_CODER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chocolatecloud_load.h"

#define MAXUNITSNUM 32

typedef struct _ChocolateCloudCoder {
  int numParityUnits;
  int numDataUnits;
} ChocolateCloudCoder;

void initChocolateCloudCoder(ChocolateCloudCoder* pCoder, int numDataUnits, int numParityUnits);

int chocolateCloudEncode(unsigned char** dataUnits, unsigned char** parityUnits,
    ChocolateCloudCoder* encoder, const int chunkSize);

int chocolateCloudReconstruct(ChocolateCloudCoder* decoder, const int chunkSize,
    unsigned char** inputs, unsigned char** outputs,
    const int* erasedIndexes, const unsigned numErased);

void exitChocolateCloudCoder();

#endif //_CHOCOLATECLOUD_ERASURE_CODER_H_