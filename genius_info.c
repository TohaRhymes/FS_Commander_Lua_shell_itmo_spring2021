#include <stdio.h>
#include <string.h>
#include <math.h>
#include <blkid/blkid.h>
#include <malloc.h>
#include "genius_info.h"

void get_size(ll size, struct fs_info *fsInfo) {
    if (size >= TB_amount) {
        fsInfo->fs_size = (ll) (size / TB_amount);
        strcpy(fsInfo->metric, "TiB");
    } else if (size >= GB_amount) {
        fsInfo->fs_size = (ll) (size / GB_amount);
        strcpy(fsInfo->metric, "GiB");
    } else if (size >= MB_amount) {
        fsInfo->fs_size = (ll) (size / MB_amount);
        strcpy(fsInfo->metric, "MiB");
    } else if (size >= KB_amount) {
        fsInfo->fs_size = (ll) (size / KB_amount);
        strcpy(fsInfo->metric, "KiB");
    } else {
        fsInfo->fs_size = (ll) (size);
        strcpy(fsInfo->metric, "B");
    }
}

int initialize_cache(blkid_cache *cache) {
    int status_init = blkid_get_cache(cache, NULL);
    if (status_init < 0) {
        fprintf(stderr, "ERROR: Can not get the cache.");
        return 1;
    }
    return 0;
}

int probe_cache(blkid_cache *cache) {
    int status_probe = blkid_probe_all(*cache);
    if (status_probe < 0) {
        fprintf(stderr, "ERROR: Can not probe devices.");
        return 1;
    }
    return 0;
}

void check_info(blkid_probe *probe, char *tag, struct fs_info *fsInfo) {
    const char *var;
    if (strcmp(tag, "TYPE") == 0) {
        fsInfo->fs_type[0] = '\0';
    }
    if (blkid_probe_has_value(*probe, tag)) {
        blkid_probe_lookup_value(*probe, tag, &var, NULL);
        if (strcmp(tag, "TYPE") == 0) {
            strcpy(fsInfo->fs_type, var);
        }
    }
}

void iterate_dev(blkid_cache *cache, struct fs_info *listHead) {

    blkid_dev dev;
    blkid_dev_iterate iterator = blkid_dev_iterate_begin(*cache);

    char devname[63];

    while (blkid_dev_next(iterator, &dev) == 0) {
        struct fs_info *cur = malloc(sizeof(fs_info));
        strcpy(devname, blkid_dev_devname(dev));
        blkid_probe probe = blkid_new_probe_from_filename(devname);
        if (probe == NULL) {
            fprintf(stderr, "Launch util as root to get more information!\n");
        } else {
            blkid_loff_t probeSize = blkid_probe_get_size(probe);
            struct fs_info currr;
            get_size(probeSize, &currr);
            blkid_do_probe(probe);
            check_info(&probe, "TYPE", &currr);
            cur->fs_size = currr.fs_size;
            strcpy(cur->metric, currr.metric);
            strcpy(cur->fs_type, currr.fs_type);
            strcpy(cur->fs_name, devname);
        }
        PathListAdd(&listHead, *cur);
    }
}

void return_info(struct fs_info *start) {
    blkid_cache cache;
    initialize_cache(&cache);
    probe_cache(&cache);
    iterate_dev(&cache, start);
}