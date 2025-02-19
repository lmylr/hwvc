cmake_minimum_required(VERSION 3.4.1)
project(al_bitmap LANGUAGES C CXX)

set(PREBUILD_STATIC ${PROJECT_SOURCE_DIR}/prebuild/static)
set(JPGE ${PREBUILD_STATIC}/libturbojpeg/libs/${ANDROID_ABI})
set(PNG ${PREBUILD_STATIC}/libpng/libs/${ANDROID_ABI})
set(WEBP ${PREBUILD_STATIC}/libwebp/libs/${ANDROID_ABI})

set(INCLUDES
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/../al_common/include
        ${PREBUILD_STATIC}/libturbojpeg/include
        ${PREBUILD_STATIC}/libpng/include
        ${PREBUILD_STATIC}/libwebp/include
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
message(STATUS "al_bitmap CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

#------------------STATIC START----------------------
#libjpeg
#add_library(
#        libjpeg
#        STATIC
#        IMPORTED)
#set_target_properties(
#        libjpeg
#        PROPERTIES IMPORTED_LOCATION
#        "${JPGE}/libjpeg.a")

#libturbojpeg
add_library(
        libturbojpeg
        STATIC
        IMPORTED)
set_target_properties(
        libturbojpeg
        PROPERTIES IMPORTED_LOCATION
        "${JPGE}/libturbojpeg.a")

#libpng16
add_library(
        libpng16
        STATIC
        IMPORTED)
set_target_properties(
        libpng16
        PROPERTIES IMPORTED_LOCATION
        "${PNG}/libpng16.a")

#libwebp
add_library(
        libwebp
        STATIC
        IMPORTED)
set_target_properties(
        libwebp
        PROPERTIES IMPORTED_LOCATION
        "${WEBP}/libwebp.a")

#------------------STATIC END----------------------

file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/core/*.cpp
        ${PROJECT_SOURCE_DIR}/image/*.cpp
        #Header
        ${PROJECT_SOURCE_DIR}/include/*.h
)
add_library(al_bitmap SHARED ${SOURCES})

find_library(
        log-lib
        log)

set(MODULES
        al_bitmap
        al_common
        libturbojpeg
        libpng16
        libwebp
        ${log-lib}
        )
target_link_libraries(${MODULES})