cmake_minimum_required(VERSION 3.15)
project(use-zeromq CXX)

find_package(ZeroMQ REQUIRED)
find_package(GTest REQUIRED)

add_executable(test1 test.cc test_util.cc test_util.h)

target_link_libraries(test1 GTest::GTest GTest::Main libzmq)
