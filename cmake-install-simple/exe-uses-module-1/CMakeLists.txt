message("mod1: ")

project(exe-uses-module1)
cmake_minimum_required(VERSION 3.17)

set(EXE_SOURCES src/main-exe-1.cpp)

message("EXE_SOURCES=${EXE_SOURCES}")

add_executable (exe-1 ${EXE_SOURCES} )

find_package(module-1)
# note, it doesn't fail il lib is missing
target_link_libraries(exe-1 PUBLIC module-1)
# https://foonathan.net/2016/03/cmake-install/
# But we want to install it and support find_package()



