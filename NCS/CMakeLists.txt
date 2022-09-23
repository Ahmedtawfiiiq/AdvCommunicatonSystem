cmake_minimum_required(VERSION 3.5)

project(comSys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(comSys main.cpp
state.h
stateMachine.h
systemMachine.cpp
systemMachine.h
systemStates.cpp
systemStates.h
fileHandler.cpp
fileHandler.h
system.cpp
system.h)

install(TARGETS comSys
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    