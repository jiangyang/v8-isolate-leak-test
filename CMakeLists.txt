cmake_minimum_required(VERSION 3.0)

project ("isolate-leak")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(V8_LIB_PATH v8)
get_filename_component(V8_STATIC_PATH ${V8_LIB_PATH} ABSOLUTE)
add_definitions(-DV8_LIB_FULL_PATH="${V8_STATIC_PATH}/")

add_library(V8_LIB_BASE STATIC IMPORTED)
set_property(TARGET V8_LIB_BASE PROPERTY IMPORTED_LOCATION ${V8_STATIC_PATH}/libv8_base.a)

add_library(V8_LIB_LIBBASE STATIC IMPORTED)
set_property(TARGET V8_LIB_LIBBASE PROPERTY IMPORTED_LOCATION ${V8_STATIC_PATH}/libv8_libbase.a)

add_library(V8_LIB_EXT_SNAP STATIC IMPORTED)
set_property(TARGET V8_LIB_EXT_SNAP PROPERTY IMPORTED_LOCATION ${V8_STATIC_PATH}/libv8_external_snapshot.a)

add_library(V8_LIB_LIBPLAT STATIC IMPORTED)
set_property(TARGET V8_LIB_LIBPLAT PROPERTY IMPORTED_LOCATION ${V8_STATIC_PATH}/libv8_libplatform.a)

add_library(V8_LIB_LIBSAMPLER STATIC IMPORTED)
set_property(TARGET V8_LIB_LIBSAMPLER PROPERTY IMPORTED_LOCATION ${V8_STATIC_PATH}/libv8_libsampler.a)

add_executable("isolate-leak" main.cpp)

target_include_directories("isolate-leak" PRIVATE "${V8_STATIC_PATH}/include")

target_link_libraries("isolate-leak" V8_LIB_BASE)
target_link_libraries("isolate-leak" V8_LIB_LIBPLAT)
target_link_libraries("isolate-leak" V8_LIB_LIBBASE V8_LIB_LIBPLAT V8_LIB_BASE V8_LIB_EXT_SNAP V8_LIB_LIBSAMPLER)
