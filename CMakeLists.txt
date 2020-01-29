
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ogreskel VERSION 0.0.1 LANGUAGES CXX)


add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES
  INSTALL_RPATH_USE_LINK_PATH TRUE
  LINK_FLAGS "-Wl,--enable-new-dtags"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(Ogre CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES})
target_include_directories(${PROJECT_NAME} 
  PRIVATE ${OGRE_INCLUDE_DIRS})
