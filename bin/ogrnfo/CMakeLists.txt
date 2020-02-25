set(OGRE_NFO ogrnfo)
add_executable(${OGRE_NFO} main.cpp)

target_compile_features(
  ${OGRE_NFO}
  PRIVATE
  cxx_std_17
)
set_target_properties(
  ${OGRE_NFO}
  PROPERTIES
  INSTALL_RPATH_USE_LINK_PATH TRUE
  LINK_FLAGS "-Wl,--enable-new-dtags"
)

find_package(nlohmann_json REQUIRED)

target_link_libraries(
  ${OGRE_NFO}
  PRIVATE
  ${OGRE_LIBRARIES}
  CLI11
  nlohmann_json::nlohmann_json
)

target_include_directories(
  ${OGRE_NFO}
  PRIVATE
  ${OGRE_INCLUDE_DIRS}
)

install(
  TARGETS ${OGRE_NFO}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
