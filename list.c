#include <stdlib.h>
#include "list.h"

void PathListAdd_fs_info(fs_info** listHead, fs_info newNode){
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

void PathListAdd_file_info(file_info** listHead, file_info newNode){
    file_info * newNodePtr = malloc(sizeof(file_info));
    file_info * last =  *listHead;
    strcpy(newNodePtr->file_type, newNode.file_type);
    strcpy(newNodePtr->file_name, newNode.file_name);

    newNodePtr->next = NULL;

    if (*listHead == NULL) {
        *listHead = newNodePtr;
        return;
    }
    int i = 0;
    while(last->next != NULL) {
        i+=1;
        last = last->next;
    }

    last->next = newNodePtr;
    free(newNodePtr);

}


files_Node *files_createNode(char *s, char* s_type) {
    files_Node *newNode = (files_Node *) malloc(sizeof(files_Node));

    newNode->s = (char *) malloc(100);
    strcpy(newNode->s, s);

    newNode->s_type = (char *) malloc(5);
    strcpy(newNode->s_type, s_type);

    newNode->next = NULL;
    return newNode;
}


void files_insert(files_Node **link, files_Node *newNode) {
    newNode->next = *link;
    *link = newNode;
}

void files_printList(files_Node *head) {
    while (head != NULL) {
        printf("%s\n", head->s);
        head = head->next;
    }
}