#pragma once

#include "list.h"

void get_size(ll size, struct fs_info *fsInfo);

int initialize_cache(blkid_cache *cache);

int probe_cache(blkid_cache *cache);

void check_info(blkid_probe *probe, char *tag, struct fs_info *fsInfo);


void iterate_dev(blkid_cache *cache, struct fs_info *listHead);

void return_info(struct fs_info *start);