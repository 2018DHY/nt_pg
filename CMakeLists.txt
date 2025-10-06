cmake_minimum_required(VERSION 3.28)

project(net_pg C)

add_executable(showip showip.c)
target_compile_options(showip PRIVATE "-std=gnu99")

add_executable(server simple_server.c)
target_compile_options(server PRIVATE "-std=gnu99")

add_executable(poll_server poll_server.c)
target_compile_options(server PRIVATE "-std=gnu99")

add_executable(ipconfig ipconfig.c)
target_compile_options(server PRIVATE "-std=gnu99")