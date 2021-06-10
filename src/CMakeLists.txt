cmake_minimum_required(VERSION 3.6)
project(pacgui LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM3 REQUIRED IMPORTED_TARGET gtkmm-3.0)
include_directories(PkgConfig::GTKMM3
    ${CMAKE_SOURCE_DIR}/../include)
add_executable(pacgui
    main.cpp
    application.cpp
    )
add_executable(test
    test.cpp)
add_custom_command(TARGET pacgui
    PRE_BUILD
    COMMAND "${CMAKE_SOURCE_DIR}/bundle.sh"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(test
    alpm)
target_link_libraries(pacgui PUBLIC
    PkgConfig::GTKMM3
    alpm
    )
