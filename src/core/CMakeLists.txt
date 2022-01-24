project(core)

add_library(${PROJECT_NAME} STATIC
    pair.c
    panic.c
    log.c
)

add_library(collections::core ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ../../include/core
)