/****************************************************************************
 * libs/libc/stdlib/lib_realpath.c
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

#include <sys/stat.h>

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libc.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

FAR char *lib_realpath(FAR const char *path, FAR char *resolved,
                       bool notfollow)
{
#ifdef CONFIG_PSEUDOFS_SOFTLINKS
  FAR char *wbuf[2] =
    {
    };

  int nlnk = 0;
  int idx = 0;
  ssize_t n;
#endif
  FAR const char *q;
  FAR char *fres = NULL;
  FAR char *p;
  struct stat sb;
  size_t len;

  if (path == NULL)
    {
      set_errno(EINVAL);
      return NULL;
    }

  if (*path == '\0')
    {
      set_errno(ENOENT);
      return NULL;
    }

  if (resolved == NULL)
    {
      fres = resolved = lib_malloc(PATH_MAX);
      if (resolved == NULL)
        {
          set_errno(ENOMEM);
          return NULL;
        }
    }

  /* Build real path one by one with paying an attention to .,
   * .. and symbolic link.
   */

  /* `p' is where we'll put a new component with prepending
   * a delimiter.
   */

  p = resolved;

  /* If relative path, start from current working directory. */

  if (*path != '/')
    {
      /* check for resolved pointer to appease coverity */

      if (getcwd(resolved, PATH_MAX) == NULL)
        {
          goto out;
        }

      len = strlen(resolved);
      if (len > 1)
        {
          p += len;
        }
    }

loop:

  /* Skip any slash. */

  while (*path == '/')
    {
      path++;
    }

  if (*path == '\0')
    {
      if (p == resolved)
        {
          *p++ = '/';
        }

      *p = '\0';

#ifdef CONFIG_PSEUDOFS_SOFTLINKS
      if (wbuf[0] != NULL)
        {
          lib_free(wbuf[0]);
        }
#endif

      return resolved;
    }

  /* Find the end of this component. */

  q = path;
  do
    {
      q++;
    }
  while (*q != '/' && *q != '\0');

  /* Test . or .. */

  if (path[0] == '.')
    {
      if (q - path == 1)
        {
          path = q;
          goto loop;
        }

      if (path[1] == '.' && q - path == 2)
        {
          /* Trim the last component. */

          if (p != resolved)
            {
              while (*--p != '/')
                {
                  continue;
                }
            }

          path = q;
          goto loop;
        }
    }

  /* Append this component. */

  if (p - resolved + 1 + q - path + 1 > PATH_MAX)
    {
      set_errno(ENAMETOOLONG);
      goto out;
    }

  p[0] = '/';
  memcpy(&p[1], path, q - path);
  p[1 + q - path] = '\0';

  if (notfollow)
    {
      p += 1 + q - path;
      path = q;
      goto loop;
    }

  /* If this component is a symlink, toss it and prepend link
   * target to unresolved path.
   */

  if (lstat(resolved, &sb) == -1)
    {
      goto out;
    }

#ifdef CONFIG_PSEUDOFS_SOFTLINKS
  if (S_ISLNK(sb.st_mode))
    {
      if (nlnk++ >= SYMLOOP_MAX)
        {
          set_errno(ELOOP);
          goto out;
        }

      if (wbuf[0] == NULL)
        {
          wbuf[0] = lib_calloc(2, PATH_MAX);
          if (wbuf[0] == NULL)
            {
              set_errno(ENOMEM);
              goto out;
            }

          wbuf[1] = wbuf[0] + PATH_MAX;
        }

      n = readlink(resolved, wbuf[idx], PATH_MAX - 1);
      if (n <= 0)
        {
          if (n == 0)
            {
              set_errno(ENOENT);
            }

          goto out;
        }

      /* Append unresolved path to link target and switch to it. */

      if (n + (len = strlen(q)) + 1 > PATH_MAX)
        {
          set_errno(ENAMETOOLONG);
          goto out;
        }

      memcpy(&wbuf[idx][n], q, len + 1);
      path = wbuf[idx];
      idx ^= 1;

      /* If absolute symlink, start from root. */

      if (*path == '/')
        {
          p = resolved;
        }

      goto loop;
    }
#endif

  if (*q == '/' && !S_ISDIR(sb.st_mode))
    {
      set_errno(ENOTDIR);
      goto out;
    }

  /* Advance both resolved and unresolved path. */

  p += 1 + q - path;
  path = q;
  goto loop;

out:
  lib_free(fres);
#ifdef CONFIG_PSEUDOFS_SOFTLINKS
  if (wbuf[0] != NULL)
    {
      lib_free(wbuf[0]);
    }
#endif

  return NULL;
}

FAR char *realpath(FAR const char *path, FAR char *resolved)
{
  return lib_realpath(path, resolved, false);
}
