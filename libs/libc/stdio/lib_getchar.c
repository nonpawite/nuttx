/****************************************************************************
 * libs/libc/stdio/lib_getchar.c
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

#include <stdio.h>
#include <unistd.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int getchar(void)
{
#ifdef CONFIG_FILE_STREAM
  return fgetc(stdin);
#else
  unsigned char c;
  return read(STDIN_FILENO, &c, 1) == 1 ? c : EOF;
#endif
}

int getchar_unlocked(void)
{
#ifdef CONFIG_FILE_STREAM
  return fgetc_unlocked(stdin);
#else
  unsigned char c;
  return read(STDIN_FILENO, &c, 1) == 1 ? c : EOF;
#endif
}
