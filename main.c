
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


static int shell_cd(lua_State *L) {
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


static int exit(lua_State *L) {
    free_fs(fs);
    return 1;
}



int shell_cp(lua_State *L){
    char *to = lua_tostring(L, -1);
    char *from = lua_tostring(L, -2);
    printf("%s %s", from, to);
    char *output = cp(fs, from, to);
    lua_newtable(L);
    lua_createtable(L, 0, 1);
    lua_pushstring(L, output);
    lua_setfield(L, -2, "cp");
    free(output);
    return 1;
}



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
        {"shell_cp",    shell_cp},
        {"exit", exit},
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