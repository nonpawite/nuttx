/****************************************************************************
 * include/nuttx/usb/pl2303.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_USB_PL2303_H
#define __INCLUDE_NUTTX_USB_PL2303_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#  define EXTERN extern "C"
extern "C"
{
#else
#  define EXTERN extern
#endif

/****************************************************************************
 * Public Functions Definitions
 ****************************************************************************/

/****************************************************************************
 * Name: usbdev_serialinit
 *
 * Description:
 *   Register PL2303 USB serial port
 *   (and USB serial console if so configured).
 *
 ****************************************************************************/

int usbdev_serialinitialize(int minor);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __INCLUDE_NUTTX_USB_PL2303_H */
