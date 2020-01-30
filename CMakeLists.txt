
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ogreskel VERSION 0.0.1 LANGUAGES CXX)

set(SOURCE_FILE src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILE})

# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# set_target_properties(${PROJECT_NAME} PROPERTIES
#   INSTALL_RPATH_USE_LINK_PATH TRUE
#   LINK_FLAGS "-Wl,--enable-new-dtags"
# )

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(OGRE CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES} stdc++fs)
# target_include_directories(${PROJECT_NAME} 
#   PRIVATE ${OGRE_INCLUDE_DIRS})
