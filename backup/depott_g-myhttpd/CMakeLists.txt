
Cmake_minimum_required(VERSION 3.5)
project(my_httpd)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++17 -pedantic -Wall -Wextra -Werror -pthread -lstdc++fs -g" )

#---------------------- files section -------------------------
#file are added here regrouped by module, .hh are not mandatory
set(SERVER
        src/server/server.cc
        src/server/server.hh
        src/response/http_response.cc
        src/response/http_response.hh)

set (SOCKET
        src/socket/socket.cc
        src/socket/socket.hh)

set (HOST
        src/host/host.cc
        src/host/host.hh)

set (PARSER
        src/parser/parser.cc
        src/parser/parser.hh)

set (EXCEPTION
        src/exception/global-exception.cc
        src/exception/global-exception.hh
        src/exception/accept-fail-exception.cc
        src/exception/accept-fail-exception.hh
        src/exception/add-fail-exception.cc
        src/exception/add-fail-exception.hh
        src/exception/epoll-create-exception.cc
        src/exception/epoll-create-exception.hh
        src/exception/epoll-ctl-exception.cc
        src/exception/epoll-ctl-exception.hh
        src/exception/wait-fail-exception.cc
        src/exception/wait-fail-exception.hh
        src/exception/missing-parameter-exception.cc
        src/exception/missing-parameter-exception.hh)

set(MAIN
        src/main.cc)

#---------------------- library section -----------------------
#libary module are added here following the format: add_library(<lib name> STATIC ${<group of file>})

find_package(Threads)

add_library(serv_module STATIC ${SERVER})

add_library(sock_module STATIC ${SOCKET})

add_library(host_module STATIC ${HOST})

add_library(pars_module STATIC ${PARSER})

add_library(exce_module STATIC ${EXCEPTION})

#---------------------- executable section --------------------

add_executable(my_httpd ${MAIN})
target_include_directories(my_httpd PRIVATE src/socket)
target_link_libraries(my_httpd serv_module)
target_link_libraries(my_httpd sock_module)
target_link_libraries(my_httpd host_module)
target_link_libraries(my_httpd pars_module)
target_link_libraries(my_httpd exce_module)
target_link_libraries(my_httpd ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} stdc++fs)
