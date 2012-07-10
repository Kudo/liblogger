cmake_minimum_required (VERSION 2.8)
project (liblogger)

OPTION (BUILD_SHARED_LIBS "Build shared libraries." OFF)
OPTION (BUILD_TESTS "Build testapp" OFF)
OPTION (DISABLE_THREAD_SAFETY "Set to disable thread safety" OFF)
OPTION (DISABLE_SOCKET_LOGGER "Set to 1 to disable socket logger" OFF)

set (LIBLOGGER_VERSION "0.2")
set (LIBLOGGER_SOVERSION 0)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories (${CMAKE_CURRENT_BINARY_DIR}/inc)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src/platform_layer/inc)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/inc/config.h.cmake
		${CMAKE_CURRENT_BINARY_DIR}/inc/config.h)

file (GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/liblogger/*.h)
install (FILES ${HEADER_FILES} DESTINATION include)

add_subdirectory(src)

if (BUILD_TESTS)
    OPTION (BUILD_TESTS_WITH_DISABLED_LOGGER "Build testapp with disabled logger" OFF)
    add_subdirectory(testapp)
endif ()
