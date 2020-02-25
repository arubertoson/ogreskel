set(OGRE_NFO ogrfo)
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

target_link_libraries(
  ${OGRE_NFO}
  ${OGRE_LIBRARIES}
  CLI11
)

target_include_directories(
  ${OGRE_NFO}
  PRIVATE
  ${OGRE_INCLUDE_DIRS}
)
