cmake_minimum_required(VERSION 3.4.1)
project(FkBase LANGUAGES C CXX)

set(INCLUDES
        ${ANDROID_NDK}/sources/android/cpufeatures
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/../glm
        ${THIRD_PARTY_DIR}/cjson/include
        )
include_directories(${INCLUDES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS_CONFIGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS_CONFIGS}")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    if (${ENABLE_TINY})
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,ALL,--gc-sections")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/rules-tiny.txt")
    endif ()
endif ()
#将Warning视为Error
if (${ENABLE_BAN_WARNING})
    foreach (var ${WARNING_CONFIGS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${var}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${var}")
    endforeach (var)
endif ()
message(STATUS "${PROJECT_NAME} CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

#------------------STATIC START----------------------
#add_library(cJSON STATIC IMPORTED)
#set_target_properties(cJSON PROPERTIES IMPORTED_LOCATION
#        "${THIRD_PARTY_DIR}/cjson/static/${ANDROID_ABI}/libcjson.a")

#------------------STATIC END----------------------

aux_source_directory(${PROJECT_SOURCE_DIR}/core SOURCES_CORE)
aux_source_directory(${PROJECT_SOURCE_DIR}/entity SOURCES_ENTITY)
aux_source_directory(${PROJECT_SOURCE_DIR}/utils SOURCES_UTILS)
aux_source_directory(${PROJECT_SOURCE_DIR}/thread SOURCES_THREAD)

list(APPEND SOURCES_ROOT ${SOURCES_CORE})
list(APPEND SOURCES_ROOT ${SOURCES_ENTITY})
list(APPEND SOURCES_ROOT ${SOURCES_UTILS})
list(APPEND SOURCES_ROOT ${SOURCES_THREAD})

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set_property(SOURCE ${SOURCES_ROOT} APPEND_STRING PROPERTY COMPILE_FLAGS " -mfpu=neon")
    add_definitions("-DHAVE_NEON=1")
elseif (${ANDROID_ABI} STREQUAL "x86")
    set_property(SOURCE ${SOURCES_ROOT} APPEND_STRING PROPERTY COMPILE_FLAGS
            " -mssse3  -Wno-unknown-attributes \
                   -Wno-deprecated-declarations \
                   -Wno-constant-conversion \
                   -Wno-static-in-inline")
    add_definitions(-DHAVE_NEON_X86=1 -DHAVE_NEON=1)
endif ()

find_library(
        log-lib
        log)
add_library(${PROJECT_NAME} OBJECT ${SOURCES_ROOT})
target_link_libraries(${PROJECT_NAME} PUBLIC ${log-lib})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
