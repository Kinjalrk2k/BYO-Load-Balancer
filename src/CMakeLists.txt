include_directories(${MyProject_SOURCE_DIR}/include)

file(GLOB SOURCES
  ../include/*.h
  *.c
)

# add_library(Example Example.cpp)
add_executable(lb ${SOURCES})

# target_link_libraries(server PUBLIC map)

# add_definitions(-w)