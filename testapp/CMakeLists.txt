file (GLOB SRC_FILES *.cpp)
file (GLOB FSRC_FILES file_logger_tests/*.cpp)

if (BUILD_TESTS_WITH_DISABLED_LOGGER)
    set (CMAKE_CXX_FLAGS "-DDISABLE_ALL_LOGS")
endif ()

add_executable (logger_test ${SRC_FILES})
target_link_libraries (logger_test logger-static)

add_executable (file_logger_test ${FSRC_FILES})
target_link_libraries (file_logger_test logger-static)
