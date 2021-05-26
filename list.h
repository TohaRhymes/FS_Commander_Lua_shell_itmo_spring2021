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


typedef struct fs_info {
    struct fs_info *next;
    ll fs_size;
    char fs_type[15];
    char fs_name[63];
    char metric[3];
} fs_info;

typedef struct file_info {
    struct file_info *next;
    char file_name[128];
    char file_type[5];
} file_info;


typedef struct stringData {
    char *s;
    char *s_type;
    struct stringData *next;
} files_Node;


files_Node *files_createNode(char *s, char *s_type);

void files_insert(files_Node **link, files_Node *newNode);

void files_printList(files_Node *head);


void PathListAdd_fs_info(fs_info **listHead, fs_info newNode);

void PathListAdd_file_info(file_info **listHead, file_info newNode);




