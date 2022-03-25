cmake_minimum_required(VERSION 3.13)
project(task)

add_executable(task src/task.cpp src/scanner.cpp src/scanner.h src/token.cpp src/token.h)
set_property(TARGET task PROPERTY CXX_STANDARD 20)
