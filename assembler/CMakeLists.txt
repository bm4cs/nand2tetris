cmake_minimum_required(VERSION 3.6)
project(clion_testdrive)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -std=gnu11 -O0")
set(SOURCE_FILES main.c vendor/unity.c person_s.h print_vtable.h print_vtable.c n2t-assy/assy_symtable.h n2t-assy/assy_symtable.c n2t-assy/assy_translator.h n2t-assy/assy_translator.c n2t-assy/assy_parser.c n2t-assy/assy_parser.h n2t-assy/tests/assy_tests.h n2t-assy/assy_frontend.c n2t-assy/assy_frontend.h)

message( STATUS "${PROJECT_SOURCE_DIR}/vendor" )

include_directories( /usr/include )
include_directories("${PROJECT_SOURCE_DIR}/vendor")

# glib
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})


add_executable(clion_testdrive ${SOURCE_FILES})

target_link_libraries(clion_testdrive ${GLIB_LIBRARIES})
