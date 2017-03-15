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

#include "chocolatecloud_rs_erasure_code.h"
#include "chocolatecloud_rs_erasure_coder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initChocolateCloudRSCoder(ChocolateCloudRSCoder* pCoder, int numDataUnits, int numParityUnits) {
  pCoder->numParityUnits = numParityUnits;
  pCoder->numDataUnits = numDataUnits;
}

int chocolateCloudRSEncode(unsigned char** dataUnits, unsigned char** parityUnits,
     ChocolateCloudRSCoder* pCoder, const int chunkSize) {
  int numDataUnits = pCoder->numDataUnits;
  int numParityUnits = pCoder->numParityUnits;

  h_hdfs_ec_chocolate_cloud_rs_encode(dataUnits, parityUnits,
                         numDataUnits, numParityUnits, chunkSize);

  return 0;
}

int chocolateCloudRSReconstruct(ChocolateCloudRSCoder* pCoder, const int chunkSize,
     unsigned char** inputs, unsigned char** outputs,
     const int* erasedIndexes, const unsigned numErased) {
  int numDataUnits = pCoder->numDataUnits;
  int numParityUnits = pCoder->numParityUnits;

  h_hdfs_ec_chocolate_cloud_rs_reconstruct(numDataUnits, numParityUnits, chunkSize,
      inputs, outputs, erasedIndexes, numErased);

  return 0;
}

void exitChocolateCloudRSCoder() {
  h_hdfs_ec_chocolate_cloud_rs_exit();
}