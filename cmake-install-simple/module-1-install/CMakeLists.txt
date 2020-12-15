message("mod1: ")

project(MODULE1)
cmake_minimum_required(VERSION 3.17)

message("MODULE1_VERSION=${MODULE1_VERSION}")
# message("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
# CMAKE_BUILD_TYPE is only meaningful for single-configuration generators (make, ninja)
# VS supports multi-configuration projects (solutions), ie. we can build debug and release using the same (generated) solution (.sln project) 

set(header_path "${MODULE1_SOURCE_DIR}/include")
set(header ${header_path}/module-1.h
		   ${header_path}/other.h
     )

set( src src/module-1.cpp)

message("header=${header}")
message("src=${src}")

add_library (module-1 ${header} ${src})
#target_include_directories(module-1 PUBLIC ${MODULE1_SOURCE_DIR}/include )

# https://foonathan.net/2016/03/cmake-install/
# set(include_dest "include/module-1-${MODULE1_VERSION}")
# set(main_lib_dest "lib/module-1-${MODULE1_VERSION}")
set(include_dest "include/module-1")
set(main_lib_dest "lib/module-1")

target_include_directories(module-1 PUBLIC
                       $<BUILD_INTERFACE:${MODULE1_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${include_dest}> # for client in install mode
                       )

# in src/CMakeLists.txt
install(TARGETS module-1 DESTINATION "${main_lib_dest}")
install(FILES ${header} DESTINATION "${include_dest}")

set(lib_dest "${main_lib_dest}/${CMAKE_BUILD_TYPE}")

install(TARGETS module-1 EXPORT module-1 DESTINATION "${lib_dest}")

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


install(FILES module-1-config.cmake DESTINATION ${main_lib_dest})
#install(EXPORT ...)

install(EXPORT module-1 DESTINATION "${lib_dest}")




