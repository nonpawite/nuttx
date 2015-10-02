/****************************************************************************
 * libc/stdio/lib_printf.c
 *
 *   Copyright (C) 2007-2008, 2011-2012, 2014 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Compilation Switches
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdio.h>
#include <syslog.h>

#include "lib_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Type Declarations
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**************************************************************************
 * Public Constant Data
 **************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/**************************************************************************
 * Private Constant Data
 **************************************************************************/

/****************************************************************************
 * Private Variables
 **************************************************************************/

/****************************************************************************
 * Public Functions
 **************************************************************************/

/****************************************************************************
 * Name: printf
 **************************************************************************/

int printf(FAR const char *fmt, ...)
{
  va_list ap;
  int     ret;

  va_start(ap, fmt);
#if CONFIG_NFILE_STREAMS > 0
  ret = vfprintf(stdout, fmt, ap);
#elif CONFIG_NFILE_DESCRIPTORS > 0
  ret = vsyslog(LOG_INFO, fmt, ap);
#elif defined(CONFIG_ARCH_LOWPUTC)
  ret = lowvsyslog(LOG_INFO, fmt, ap);
#else
# ifdef CONFIG_CPP_HAVE_WARNING
#   warning "printf has no data sink"
# endif
  ret = 0;
#endif
  va_end(ap);

  return ret;
}

