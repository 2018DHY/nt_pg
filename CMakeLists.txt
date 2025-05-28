cmake_minimum_required(VERSION 3.28)

project(net_pg C)

add_executable(showip showip.c)
target_compile_options(showip PRIVATE "-std=gnu99")