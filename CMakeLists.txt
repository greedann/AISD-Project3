cmake_minimum_required(VERSION 3.5.0)
project(aisd-3 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(aisd-3 main.cpp gipfengine.cpp gipfengine.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
