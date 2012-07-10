set(SRC_FILES
    liblogger.c
    file_logger.c
    LLTimeUtil.c
)

if (NOT DISABLE_THREAD_SAFETY)
    list (APPEND SRC_FILES platform_layer/posix/tPLMutex.c)
endif ()

if (NOT DISABLE_SOCKET_LOGGER)
    list (APPEND SRC_FILES socket_logger.c platform_layer/posix/tPLSocket.c)
endif ()

add_library (logger SHARED ${SRC_FILES})
set_target_properties (logger PROPERTIES
    VERSION ${LIBLOGGER_VERSION}
    SOVERSION ${LIBLOGGER_SOVERSION})
install (TARGETS logger
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin
)

add_library (logger-static ${SRC_FILES})
install (TARGETS logger-static
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin
)
