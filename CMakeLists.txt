cmake_minimum_required(VERSION 3.25)
project(trees-practic C)
add_compile_options(-Wall -Wextra -pedantic)

add_library(bst src/bst.c)
add_library(stack src/stack.c)

add_executable(main src/main.c)

target_link_libraries(bst PRIVATE stack)
target_link_libraries(main PRIVATE bst)
