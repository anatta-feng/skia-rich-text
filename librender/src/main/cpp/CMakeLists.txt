# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("render")

include_directories(${CMAKE_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/../../../libs/armeabi-v7a)

add_library(skia SHARED IMPORTED)

set_target_properties(skia PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../../../libs/armeabi-v7a/libskia.so")

message(${CMAKE_SOURCE_DIR})
message(${PROJECT_SOURCE_DIR})
message(${CMAKE_PROJECT_NAME})

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        librender.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        "${CMAKE_SOURCE_DIR}"

        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/android"
        "${CMAKE_SOURCE_DIR}/include/codec"
        "${CMAKE_SOURCE_DIR}/include/config"
        "${CMAKE_SOURCE_DIR}/include/core"
        "${CMAKE_SOURCE_DIR}/include/docs"
        "${CMAKE_SOURCE_DIR}/include/effects"
        "${CMAKE_SOURCE_DIR}/include/encode"
        "${CMAKE_SOURCE_DIR}/include/gpu"
        "${CMAKE_SOURCE_DIR}/include/pathops"
        "${CMAKE_SOURCE_DIR}/include/ports"
        "${CMAKE_SOURCE_DIR}/include/private"
        "${CMAKE_SOURCE_DIR}/include/sksl"
        "${CMAKE_SOURCE_DIR}/include/svg"
        "${CMAKE_SOURCE_DIR}/include/third_party"
        "${CMAKE_SOURCE_DIR}/include/utils"
        )

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        skia
        android
        log)