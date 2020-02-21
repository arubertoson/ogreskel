cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ogreutil VERSION 0.0.1 LANGUAGES CXX)


# XXX: Should not be in cmake file
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
find_package(OGRE CONFIG REQUIRED)


add_library(CLI11 INTERFACE)
target_include_directories(
  CLI11 INTERFACE
  include
)

add_subdirectory(bin)

