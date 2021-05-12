#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>

#include "templates/counter.h"
#include "list.h"
#include "genius_info.h"

/* Userdata object that will hold the counter and name. */
typedef struct {
    ll fs_size;
    char metric[3];
    char fs_type[15];
    char fs_name[63];
    int id;
} lfs_info_userdata_t;

static int lcounter_new(lua_State *L) {
    fs_info start;
    return_info(&start);
    start = *start.next;
    int i = 0;


    do {
        start = *start.next;
        lfs_info_userdata_t *cu;

        /* Create the user data pushing it onto the stack. We also pre-initialize
     * the member of the userdata in case initialization fails in some way. If
     * that happens we want the userdata to be in a consistent state for __gc. */
        cu = (lfs_info_userdata_t *) lua_newuserdata(L, sizeof(*cu));
        cu->fs_size = NULL;
        cu->metric[0] = '\0';
        cu->fs_type[0] = '\0';
        cu->fs_name[0] = '\0';
        cu->id = NULL;

        /* Add the metatable to the stack. */
        luaL_getmetatable(L, "LInfo");
        /* Set the metatable on the userdata. */
        lua_setmetatable(L, -2);

        /* Create the data that comprises the userdata (the counter). */



        printf("%s\n", start.fs_name);
        strcpy(cu->fs_name,start.fs_name);
        strcpy(cu->fs_type,start.fs_type);
        strcpy(cu->metric,start.metric);
        cu->id = i;
        cu->fs_size=start.fs_size;
        i+=1;

    } while (start.next);

    return 1;
}



static const struct luaL_Reg linfo_methods[] = {
//        { "add",         lcounter_add       },
//        { "__tostring",  lcounter_tostring  },
        {NULL, NULL},
};

static const struct luaL_Reg linfo_functions[] = {
        {"new", lcounter_new},
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