project(Cjson)

set(HEADER_FILES
        cJSON.h
        )

set(SOURCE_FILES
        cJSON.c
        )

add_library(Cjson_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})