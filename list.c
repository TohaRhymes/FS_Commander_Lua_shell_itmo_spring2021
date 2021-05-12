#include <stdlib.h>
#include "list.h"

void PathListAdd(fs_info** listHead, fs_info newNode){
    fs_info * newNodePtr = malloc(sizeof(fs_info));
    fs_info * last =  *listHead;
    strcpy(newNodePtr->fs_type, newNode.fs_type);
    strcpy(newNodePtr->metric, newNode.metric);
    strcpy(newNodePtr->fs_name, newNode.fs_name);
    newNodePtr->fs_size = newNode.fs_size;

    newNodePtr->next = NULL;

    if (*listHead == NULL) {
        *listHead = newNodePtr;
        return;
    }

    while(last->next != NULL) {
        last = last->next;
    }

    last->next = newNodePtr;

}
void PathListClear(fs_info *listHead){
    fs_info *start = listHead;
    fs_info *prev = NULL;

    while (start) {
        prev = start;
        start = start->next;

        if (prev) {
            free(prev);
        }
    }

}

fs_info* GetPathListLastNode(fs_info ** listHead) {
    fs_info * listStart = *listHead;

    while(listStart->next != NULL) {
        listStart = listStart->next;
    }

    return listStart;
}
