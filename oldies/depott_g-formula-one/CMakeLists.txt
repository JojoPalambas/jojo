cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

set(SRC
    src/dijkstra.c
    src/granny.c
    src/formulaone.c
    # Add your source files here in SRC
)

set(OUT
    tests/test.c)

link_directories(${CMAKE_SOURCE_DIR}/control)

# Main binary
add_library(formulaone SHARED ${SRC})
target_link_libraries(formulaone m)

add_executable(check EXCLUDE_FROM_ALL ${OUT})
target_link_libraries(check formulaone formulaonecontrol m)

# DON'T CHANGE THIS PART
# {
add_custom_target(run
  COMMAND cp -u  ${CMAKE_SOURCE_DIR}/control/*.so ${CMAKE_BINARY_DIR}
  COMMAND cp -u  ${CMAKE_SOURCE_DIR}/viewer/*.dll ${CMAKE_BINARY_DIR}
  COMMAND cp -u  ${CMAKE_SOURCE_DIR}/viewer/*.exe ${CMAKE_BINARY_DIR}
  COMMAND cp -rf ${CMAKE_SOURCE_DIR}/viewer/res/  ${CMAKE_BINARY_DIR}/res/
  COMMAND cp -rf ${CMAKE_SOURCE_DIR}/custom/      ${CMAKE_BINARY_DIR}/res/
  COMMAND test ${CMAKE_SOURCE_DIR} != ${CMAKE_BINARY_DIR} &&
          cp -u  ${CMAKE_SOURCE_DIR}/.config      ${CMAKE_BINARY_DIR} || true
  COMMAND mono ./FormulaOne.exe
)
add_dependencies(run formulaone)
#}
