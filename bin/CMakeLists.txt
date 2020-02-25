set(DIRS ogrmm ogrsm ogrnfo)

foreach(d ${DIRS})
  add_subdirectory(${d})
endforeach()
