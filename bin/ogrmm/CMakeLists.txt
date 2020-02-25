set(MESH_MERGE ogrmm)
add_executable(${MESH_MERGE} main.cpp)

target_compile_features(
  ${MESH_MERGE}
  PRIVATE
  cxx_std_17
)
set_target_properties(
  ${MESH_MERGE}
  PROPERTIES
  INSTALL_RPATH_USE_LINK_PATH TRUE
  LINK_FLAGS "-Wl,--enable-new-dtags"
)

target_link_libraries(
  ${MESH_MERGE}
  ${OGRE_LIBRARIES}
  CLI11
)

target_include_directories(
  ${MESH_MERGE}
  PRIVATE
  ${OGRE_INCLUDE_DIRS}
)

install(
  TARGETS ${MESH_MERGE}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
