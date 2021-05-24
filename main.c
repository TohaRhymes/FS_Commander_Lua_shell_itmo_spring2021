#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>

#include "list.h"
#include "genius_info.h"



struct {
    char *name;
    int size;
} _files[] = {
        {"myfile.txt", 533},
        {"hww.bin",    4444444}
};

static int info(lua_State *L) {
    fs_info start;
    return_info(&start);
    start = *start.next;
    int i = 0;
    char *snum = malloc( 20);

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

//        strcpy(cu->fs_type,start.fs_type);
        i+=1;

    } while (start.next);

    return 1;
}


int test(lua_State *L) {

    lua_newtable(L);

    lua_pushstring(L, "12");

    lua_createtable(L, 0, 2);
    lua_pushstring(L, _files[0].name);
    lua_setfield(L, -2, "name");
    lua_pushinteger(L, _files[0].size);
    lua_setfield(L, -2, "size");

    lua_settable(L, -3);

    lua_pushstring(L, "23");
    lua_createtable(L, 0, 2);
    lua_pushstring(L, _files[1].name);
    lua_setfield(L, -2, "name");
    lua_pushinteger(L, _files[1].size);
    lua_setfield(L, -2, "size");


    lua_settable(L, -3);

    return 1;
}


static const struct luaL_Reg linfo_methods[] = {
//        { "add",         lcounter_add       },
//        { "__tostring",  lcounter_tostring  },
        {NULL, NULL},
};

static const struct luaL_Reg linfo_functions[] = {
        {"info", info},
        {"test", test},
        {NULL, NULL}
};

int luaopen_libspo_lab2_fs_for_lua(lua_State *L) {
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