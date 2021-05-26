
#include <string.h>

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <malloc.h>

#include "list.h"
#include "genius_info.h"
#include "genius_ntfs.h"
#include "genius_commander.h"


struct ntfs_sb_info *fs;
char *DName;


static int info(lua_State *L) {
    fs_info start;
    return_info(&start);
    start = *start.next;
    int i = 0;
    char *snum = malloc(20);

    lua_newtable(L);
    do {
        sprintf(snum, "%d", i);
        lua_pushstring(L, snum);

        start = *start.next;

        lua_createtable(L, 0, 2);
        lua_pushstring(L, start.fs_name);
        lua_setfield(L, -2, "name");
        lua_pushinteger(L, start.fs_size);
        lua_setfield(L, -2, "size");
        lua_pushstring(L, start.metric);
        lua_setfield(L, -2, "metric");
        lua_pushstring(L, start.fs_type);
        lua_setfield(L, -2, "type");

        lua_settable(L, -3);

        i += 1;

    } while (start.next);

    return 1;
}

static int shell_check(lua_State *L) {
    DName = lua_tostring(L, -1);
    fs = ntfs_init(DName);
    lua_newtable(L);
    lua_createtable(L, 0, 1);
    if (fs == NULL)
        lua_pushboolean(L, 0);
    else
        lua_pushboolean(L, 1);
    lua_setfield(L, -2, "is_okay");
    return 1;
}


int shell_pwd(lua_State *L) {
    char *pwd_path = pwd(fs);
    lua_newtable(L);
    lua_createtable(L, 0, 1);
    lua_pushstring(L, pwd_path);
    lua_setfield(L, -2, "pwd");
    return 1;
}


static int shell_ls(lua_State *L) {

    char *path = lua_tostring(L, -1);


    files_Node *head = NULL;
    files_Node *tail = NULL;
    files_Node *n;
    n = files_createNode("", "");
    // First node at start of list - head is updated.
    files_insert(&head, n);
    // First node is also the tail.
    tail = n;


    char *output = ls(fs, path, head, tail, n);
    if (output == NULL) {
        return 0;
    }
//    printf("%s", output);

    int i = 0;
    char *snum = malloc(20);
    head = head->next;
    lua_newtable(L);
    while (head != NULL) {

        sprintf(snum, "%d", i);
//        printf("_____%s\t%s\t%s\n", head->s_type, head->s, snum);
        lua_pushstring(L, snum);

        lua_createtable(L, 0, 2);

        lua_pushstring(L, head->s);
        lua_setfield(L, -2, "name");
        lua_pushstring(L, head->s_type);
        lua_setfield(L, -2, "type");

        lua_settable(L, -3);
        i += 1;
//
        head = head->next;
    }

    free(output);


    return 1;
}


int shell_cd(lua_State *L) {
    char *path = lua_tostring(L, -1);
//    printf("%s\n", path);
    char *output = cd(fs, path);
    lua_newtable(L);
    lua_createtable(L, 0, 1);
    lua_pushstring(L, output);
    lua_setfield(L, -2, "cd");
    free(output);
    return 1;
}


//
//
//int shell(lua_State *L){
//    struct ntfs_sb_info *fs  = ntfs_init(filename);
//    if (fs == NULL) return -1;
//    printf("NTFS filesystem detected.\n");
//    int exitFlag = 0;
//    char *inputString = malloc(1024);
//    while (!exitFlag) {
//        char *pwd_path = pwd(fs);
//        printf("%s$ ", pwd_path);
//        free(pwd_path);
//        fgets(inputString, 1024, stdin);
//        char *command = strtok(inputString, " \n");
//        if (command == NULL) {
//            continue;
//        }
//        char *path = strtok(NULL, " \n");
//        char *out_path = strtok(NULL, " \n");
//        if (strcmp(command, "exit") == 0) {
//            exitFlag = 1;
//        } else if (strcmp(command, "help") == 0) {
//            printf("cd [directory] - change working directory\n");
//            printf("pwd - print full path to working directory \n");
//            printf("cp [directory/file] [target directory] - copy dir or file from mounted device\n");
//            printf("ls/ll - show working directory elements\n");
//            printf("exit - terminate program\n");
//            printf("help - print help\n");
//        } else if (strcmp(command, "ls") == 0 || strcmp(command, "ll") == 0 ) {
//            char *output = ls(fs, path);
//            if (output == NULL) {
//                printf("No such file or directory\n");
//                continue;
//            }
//            printf("%s", output);
//            free(output);
//        } else if (strcmp(command, "pwd") == 0) {
//            char *output = pwd(fs);
//            printf("%s\n", output);
//            free(output);
//        } else if (strcmp(command, "cd") == 0) {
//            if (path == NULL){
//                printf("cd command requires path argument\n");
//                continue;
//            }
//            char *output = cd(fs, path);
//            printf("%s", output);
//            free(output);
//        } else if (strcmp(command, "cp") == 0) {
//            if (path == NULL) {
//                printf("cp command requires path argument\n");
//                continue;
//            }
//            if (out_path == NULL) {
//                printf("cp command requires out_path argument\n");
//                continue;
//            }
//            char *output = cp(fs, path, out_path);
//            printf("%s", output);
//            free(output);
//        } else {
//            printf("Wrong command. Enter 'help' to get help.\n");
//        }
//    }
//    free_fs(fs);
//    return 0;
//}
//
//

static const struct luaL_Reg linfo_methods[] = {
//        { "add",         lcounter_add       },
//        { "__tostring",  lcounter_tostring  },
        {NULL, NULL},
};

static const struct luaL_Reg linfo_functions[] = {
        {"info",        info},
//        {"test", test},
        {"shell_check", shell_check},
        {"shell_pwd",   shell_pwd},
        {"shell_ls",    shell_ls},
        {"shell_cd",    shell_cd},
        {NULL, NULL}
};

int luaopen_lib_ntfs(lua_State *L) {
    /* Create the metatable and put it on the stack. */
    luaL_newmetatable(L, "LInfo");
    /* Duplicate the metatable on the stack (We know have 2). */
    lua_pushvalue(L, -1);
    /* Pop the first metatable off the stack and assign it to __index
     * of the second one. We set the metatable for the table to itself.
     * This is equivalent to the following in lua:
     * metatable = {}
     * metatable.__index = metatable
     */
    lua_setfield(L, -2, "__index");

    /* Set the methods to the metatable that should be accessed via object:func */
    luaL_setfuncs(L, linfo_methods, 0);

    /* Register the object.func functions into the table that is at the top of the
     * stack. */
    luaL_newlib(L, linfo_functions);

    return 1;
}