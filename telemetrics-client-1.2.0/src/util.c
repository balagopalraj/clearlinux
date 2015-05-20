/*
 * This program is part of the Clear Linux Project
 *
 * Copyright 2015 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms and conditions of the GNU Lesser General Public License, as
 * published by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include "log.h"
#include "util.h"

bool get_header(const char *haystack, const char *needle, char **line, size_t len)
{
        if (haystack && !strncmp(haystack, needle, len)) {
                *line = strdup(haystack);
                return true;
        }
        return false;
}

void *reallocate(void **addr, size_t *allocated, size_t requested)
{
        void *newaddr;
        size_t new_allocated;

        assert(addr);

        if (*allocated >= requested) {
                return *addr;
        }

        new_allocated =  requested * 2;
        newaddr = realloc(*addr, new_allocated);
        if (newaddr == NULL) {
                return NULL;
        }
        *addr = newaddr;
        *allocated = new_allocated;
        return newaddr;
}

bool file_exists(char *file_path)
{
        struct stat buf;
        int ret;

        ret = stat(file_path, &buf);

        if (ret != 0  || !S_ISREG(buf.st_mode)) {
                return false;
        } else {
                return true;
        }
}

long get_directory_size(char *dir_path)
{
        long total_size = 0;
        DIR *dir;
        struct dirent *de;
        int ret;
        struct stat buf;
        char *file_path = NULL;

        dir = opendir(dir_path);
        if (!dir) {
                telem_perror("Error opening spool dir");
                return -1;
        }

        while ((de = readdir(dir)) != NULL) {
                ret = asprintf(&file_path, "%s/%s", dir_path, de->d_name);
                if (ret == -1) {
                        telem_log(LOG_CRIT, "Cannot allocate memory, exiting\n");
                        exit(EXIT_FAILURE);
                }

                ret = stat(file_path, &buf);
                if (ret < 0) {
                        telem_log(LOG_ERR, "Could not stat file %s:%s", file_path, strerror(errno));
                } else {
                        total_size += buf.st_size;
                }

                free(file_path);
        }
        closedir(dir);

        return total_size;
}

/* vi: set ts=8 sw=8 sts=4 et tw=80 cino=(0: */
