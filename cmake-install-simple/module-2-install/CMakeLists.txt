message("mod1: ")

project(MODULE2)
cmake_minimum_required(VERSION 3.17)

message("MODULE2_VERSION=${MODULE2_VERSION}")
message("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
# CMAKE_BUILD_TYPE is only meaningful for single-configuration generators (make, ninja)
# VS supports multi-configuration projects (solutions), ie. we can build debug and release using the same (generated) solution (.sln project) 

set(header_path "${MODULE2_SOURCE_DIR}/include")
set(header ${header_path}/module-2.h
		   ${header_path}/other.h
     )

set( src src/code.cpp)

message("header=${header}")
message("src=${src}")

add_library (module-2 ${header} ${src})
#target_include_directories(module-1 PUBLIC ${MODULE1_SOURCE_DIR}/include )

# set(include_dest "include/module-1-${MODULE1_VERSION}")
# set(main_lib_dest "lib/module-1-${MODULE1_VERSION}")
set(include_dest "include/module-2")
set(main_lib_dest "lib/module-2")

target_include_directories(module-2 PUBLIC
                       $<BUILD_INTERFACE:${MODULE2_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${include_dest}> # for client in install mode
                       )

# in src/CMakeLists.txt
install(TARGETS module-2 DESTINATION "${main_lib_dest}")
install(FILES ${header} DESTINATION "${include_dest}")

set(lib_dest "${main_lib_dest}/${CMAKE_BUILD_TYPE}")

install(TARGETS module-2 EXPORT module-2 DESTINATION "${lib_dest}")

# If we write find_package(my_library ...), it will go and look for a file
# named my_library-config.cmake (among others) in a directory named my_library* 
# under the ${CMAKE_INSTALL_PREFIX}/lib (among many others).
#
# And our installation directory name lib/my_library-[major].[minor] - the ${main_lib_dest} - matches this expression.
#
# We just need to provide the my_library-config.cmake file.
# The contents of the file will be made available to the calling script of find_package().
# It usually contains code defining the targets but we already have that code!
# It is in the my_library.cmake file created by the install(EXPORT).
# We just need to include() that inside the my_library-config.cmake file.

install(FILES module-2-config.cmake DESTINATION ${main_lib_dest})
install(EXPORT module-2 DESTINATION "${lib_dest}")

set (SCRIPTS "C:/bin/programs/vcpkg/scripts")
set (VCPKG_PLATFORM_TOOLSET v142)
set (VCPKG_TARGET_ARCHITECTURE x64)
set (VCPKG_LIBRARY_LINKAGE static)

message("NINJA_HOST=[${NINJA_HOST}]")
message("CMAKE_HOST_WIN32=[${CMAKE_HOST_WIN32}]")


include("C:/bin/programs/vcpkg/scripts/cmake/vcpkg_build_cmake.cmake")
include("C:/bin/programs/vcpkg/scripts/cmake/vcpkg_configure_cmake.cmake")

vcpkg_configure_cmake( ${src} )

