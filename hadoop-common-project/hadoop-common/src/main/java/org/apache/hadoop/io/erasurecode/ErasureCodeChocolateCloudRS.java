/*
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

package org.apache.hadoop.io.erasurecode;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.hadoop.util.NativeCodeLoader;

/**
 * ChocolateCloud-RS native erasure coding library related utilities.
 */
public final class ErasureCodeChocolateCloudRS {

    private static final Log LOG =
            LogFactory.getLog(ErasureCodeChocolateCloudRS.class.getName());

    /**
     * The reason why ChocolateCloud-RS library is not available, or null if it is available.
     */
    private static final String LOADING_FAILURE_REASON;

    static {
        if (!NativeCodeLoader.isNativeCodeLoaded()) {
            LOADING_FAILURE_REASON = "hadoop native library cannot be loaded. Use -Pnative to compile/bundle native code.";
        } else if (!NativeCodeLoader.buildSupportsChocolateCloudRS()) {
            LOADING_FAILURE_REASON = "libhadoop was built without ChocolateCloud-RS support. Please make sure that /usr/lib/libhdfs_ec_chocolate_cloud_rs.so.1 exists to use ChocolateCloud-RS library. Use -Drequire.chocolatecloud.rs to fail the build if libhdfs_ec_chocolate_cloud_rs.so.1 is not found.";
        } else {
            String problem = null;
            try {
                loadLibrary();
            } catch (Throwable t) {
                problem = "Loading ChocolateCloud-RS failed: " + t.getMessage();
                LOG.error("Loading ChocolateCloud-RS failed", t);
            }
            LOADING_FAILURE_REASON = problem;
        }
    }

    private ErasureCodeChocolateCloudRS() {}

    /**
     * Are native libraries loaded?
     */
    public static boolean isNativeCodeLoaded() {
        return LOADING_FAILURE_REASON == null;
    }

    /**
     * Is the native ChocolateCloud-RS library loaded and initialized? Throw exception if not.
     */
    public static void checkNativeCodeLoaded() {
        if (LOADING_FAILURE_REASON != null) {
            throw new RuntimeException(LOADING_FAILURE_REASON);
        }
    }

    /**
     * Load native library available or supported.
     */
    public static native void loadLibrary();

    /**
     * Get the native library name that's available or supported.
     */
    public static native String getLibraryName();

    public static String getLoadingFailureReason() {
        return LOADING_FAILURE_REASON;
    }
}
