/*
 *   Software Updater - client side
 *
 *      Copyright © 2012-2015 Intel Corporation.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, version 2 or later of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Authors:
 *         Arjan van de Ven <arjan@linux.intel.com>
 *
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <swupd.h>




static int new_files;
static int deleted_files;
static int changed_files;
static int new_manifests;
static int deleted_manifests;
static int changed_manifests;
static int delta_miss;
static int delta_hit;


void account_new_file(void)
{
	new_files++;
}

void account_deleted_file(void)
{
	deleted_files++;
}

void account_changed_file(void)
{
	changed_files++;
}

void account_new_manifest(void)
{
	new_manifests++;
}

void account_deleted_manifest(void)
{
	deleted_manifests++;
}

void account_changed_manifest(void)
{
	changed_manifests++;
}

void account_delta_hit(void)
{
	delta_hit++;
}


void account_delta_miss(void)
{
	delta_miss++;
}

int have_delta_files(void)
{
	if (changed_files)
		return 1;
	return 0;
}

int have_new_files(void)
{
	if (new_files)
		return 1;
	return 0;
}



void print_statistics(int version1, int version2)
{
	log_stdout("\n");
	log_stdout("Statistics for going from version %i to version %i:\n\n", version1, version2);
	log_stdout("    changed manifests : %i\n", changed_manifests);
	log_stdout("    new manifests     : %i\n", new_manifests);
	log_stdout("    deleted manifests : %i\n\n", deleted_manifests);
	log_stdout("    changed files     : %i\n", changed_files);
	log_stdout("    new files         : %i\n", new_files);
	log_stdout("    deleted files     : %i\n", deleted_files);
	log_stdout("\n");
}

void print_delta_statistics(void)
{
	LOG_INFO(NULL, "Delta stats", class_stats, "%i successful delta usages, %i failures", delta_hit, delta_miss);
}
