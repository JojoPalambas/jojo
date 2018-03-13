cmake_minimum_required(VERSION 2.8.9)

project(42sh)

#Bring the headers, such as lexer.h into the project
#include_directories(./src/lexer)
#To my group : we should regroup our header file into a "include" directory

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_BUILD_TYPE Debug)




#Can manually add the sources using the set command as follows:
#set(SOURCES src/parser.c src/grammar.c)

#However, the file(GLOB...) allows for wildcard additions:
file(
  GLOB_RECURSE
  SOURCES
  src/*
  )

add_executable(42sh ${SOURCES})

target_link_libraries(42sh readline)

add_custom_target(check
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.rb
  )

add_custom_target(clear
  COMMAND rm -rf CMakeCache.txt Doxyfile
  cmake_install.cmake Makefile CMakeFiles
  )

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  # note the option ALL which allows to build the docs together with the application
  add_custom_target(doc #doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)








#To Use cmake
# mkdir tmp
# cd tmp
# cmake ..
# make

#There is no clean rule so please always build in a temporary
#directory you created
# cd ..
# rm -rf tmp
