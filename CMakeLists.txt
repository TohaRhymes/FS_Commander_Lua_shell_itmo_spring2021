cmake_minimum_required(VERSION 3.19)
project(_ntfs C)

add_library(_ntfs SHARED
        list.c
        list.h
        genius_info.h
        genius_info.c
        genius_commander.h
        genius_commander.c
        genius_ntfs.h
        genius_ntfs.c
        main.c)


#add_executable(spo_lab2_fs_for_lua
#        list.c
#        list.h
##        genius_info.h
##        genius_info.c
##        genius_commander.h
##        genius_commander.c
##        genius_ntfs.h
##        genius_ntfs.c
#        )

target_link_libraries(_ntfs blkid)

find_package(Lua REQUIRED)
include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LUA_INCLUDE_DIR}
)
link_directories(${ARGOS_LIBRARY_DIRS})