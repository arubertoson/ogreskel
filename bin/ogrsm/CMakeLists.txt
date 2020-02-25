set(SKEL_MERGE ogrsm)
add_executable(${SKEL_MERGE} main.cpp)

target_compile_features(
  ${SKEL_MERGE}
  PRIVATE
  cxx_std_17
)
set_target_properties(
  ${SKEL_MERGE}
  PROPERTIES
  INSTALL_RPATH_USE_LINK_PATH TRUE
  LINK_FLAGS "-Wl,--enable-new-dtags"
)

target_link_libraries(
  ${SKEL_MERGE}
  ${OGRE_LIBRARIES}
  CLI11
)

target_include_directories(
  ${SKEL_MERGE}
  PRIVATE
  ${OGRE_INCLUDE_DIRS}
)

install(
  TARGETS ${SKEL_MERGE}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
