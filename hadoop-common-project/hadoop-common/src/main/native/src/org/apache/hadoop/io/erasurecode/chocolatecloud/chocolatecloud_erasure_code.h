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

#ifndef _CHOCOLATECLOUD_ERASURE_CODE_H_
#define _CHOCOLATECLOUD_ERASURE_CODE_H_

#include <stddef.h>

#include "chocolatecloud_load.h"

/**
 *  Interface to functions supporting erasure code encode and decode.
 */

// Initialize the coding stack factories, has to be called first
int h_hdfs_ec_chocolate_cloud_rs_init();

// Deallocates the factories, must be called before exiting to release all resources properly
int h_hdfs_ec_chocolate_cloud_rs_exit();

/**
 * Encodes the given input buffers.
 *
 * @return Zero on success, a negative number on error.
 */
 int h_hdfs_ec_chocolate_cloud_rs_encode
 (
     unsigned char** data_buffers,
     unsigned char** parity_buffers,

     const unsigned data_units_num,
     const unsigned parity_units_num,
     const int chunk_size
 );

/**
 * Reconstructs based on the given input buffers.
 */
 int h_hdfs_ec_chocolate_cloud_rs_reconstruct
 (
     const unsigned data_units_num,
     const unsigned parity_units_num,
     const int chunk_size,

     unsigned char** input_buffers,
     unsigned char** output_buffers,

     const int* erased_indexes,
     const unsigned erased_units_num
 );

#endif //_CHOCOLATECLOUD_ERASURE_CODE_H_