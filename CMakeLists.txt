cmake_minimum_required(VERSION 2.6)

project(Rechop C CXX)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

find_package(Imagine REQUIRED)
find_package (Threads)

add_executable(Rechop
               main.cpp clusters.h clusters.cpp solution.cpp solution.h recuit.cpp recuit.h network.cpp network.h solutions_parser.cpp solutions_parser.h)
ImagineUseModules(Rechop Graphics)


target_link_libraries (Rechop ${CMAKE_THREAD_LIBS_INIT})
