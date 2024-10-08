/****************************************************************************
 * sched/semaphore/sem_initialize.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/trace.h>

#include "semaphore/semaphore.h"

/* Currently only need to setup priority inheritance logic */

#ifdef CONFIG_PRIORITY_INHERITANCE

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nxsem_initialize
 *
 * Description:
 *   The control structures for all semaphores may be initialized by calling
 *   nxsem_initialize().  This should be done once at power-on.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 * Assumptions:
 *   Called once during OS startup initialization
 *
 ****************************************************************************/

void nxsem_initialize(void)
{
  sched_trace_begin();

  /* Initialize holder structures needed to support priority inheritance */

  nxsem_initialize_holders();
  sched_trace_end();
}

#endif /* CONFIG_PRIORITY_INHERITANCE */
