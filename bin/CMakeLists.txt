set(DIRS ogrmm ogrsm)

foreach(d ${DIRS})
  add_subdirectory(${d})
endforeach()
