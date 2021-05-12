cmake_minimum_required(VERSION 3.19)
project(spo_lab2_fs_for_lua C)

add_library(spo_lab2_fs_for_lua SHARED
#        templates/counter.c
#        templates/counter.h
        list.c
        list.h
        genius_info.h
        genius_info.c
#        genius_info_wrap.c
#        wrap.c
        main.c)
target_link_libraries(spo_lab2_fs_for_lua blkid)


find_package(Lua REQUIRED)
include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LUA_INCLUDE_DIR}
)
link_directories(${ARGOS_LIBRARY_DIRS})