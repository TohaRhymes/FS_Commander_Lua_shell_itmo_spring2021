#pragma once

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <blkid/blkid.h>

#define ll long long
#define TB_amount pow(2, 40)
#define GB_amount pow(2, 30)
#define MB_amount pow(2, 20)
#define KB_amount pow(2, 10)


typedef struct fs_info{
    struct fs_info* next;
    ll fs_size;
    char fs_type[15];
    char fs_name[63];
    char metric[3];
}fs_info;



void PathListAdd(fs_info** listHead, fs_info newNode);




