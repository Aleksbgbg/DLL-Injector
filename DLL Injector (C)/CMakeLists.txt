cmake_minimum_required(VERSION 3.8)
project(DLL_Injector__C_)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c FindProcess.c FindProcess.h)
add_executable(DLL_Injector__C_ ${SOURCE_FILES})