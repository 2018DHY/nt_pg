cmake_minimum_required(VERSION 3.28)

project(net_pg CXX)

add_executable(net_api example/net_api.cpp)

add_executable(showip showip.cpp)
# target_compile_options(showip PRIVATE "-std=gnu99")

add_executable(server simple_server.cpp)
# target_compile_options(server PRIVATE "-std=gnu99")

add_executable(poll_server poll_server.cpp)
# target_compile_options(server PRIVATE "-std=gnu99")

add_executable(ipconfig ipconfig.cpp)
# target_compile_options(server PRIVATE "-std=gnu99")