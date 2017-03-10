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

#include "chocolatecloud_rs_load.h"
#include "chocolatecloud_rs_erasure_code.h"

/**
 *  chocolatecloud_rs_erasure_code.c
 *  Implementation erasure code utilities based on ChocolateCloud-RS library.
 *
 */

int h_hdfs_ec_chocolate_cloud_rs_init(){
  return chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_init();
}

int h_hdfs_ec_chocolate_cloud_rs_exit(){
  return chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_exit();
}

int h_hdfs_ec_chocolate_cloud_rs_encode
(
     unsigned char** data_buffers,
     unsigned char** parity_buffers,

     const unsigned data_units_num,
     const unsigned parity_units_num,
     const int chunk_size
){
    return chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_encode
    (
        data_buffers,
        parity_buffers,

        data_units_num,
        parity_units_num,
        chunk_size
    );
}

int h_hdfs_ec_chocolate_cloud_rs_reconstruct
 (
     const unsigned data_units_num,
     const unsigned parity_units_num,
     const int chunk_size,

     unsigned char** input_buffers,
     unsigned char** output_buffers,

     const int* erased_indexes,
     const unsigned erased_units_num
){
    return chocolateCloudRSLoader->hdfs_ec_chocolate_cloud_rs_reconstruct
     (
         data_units_num,
         parity_units_num,
         chunk_size,

         input_buffers,
         output_buffers,

         erased_indexes,
         erased_units_num
    );
}