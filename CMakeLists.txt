cmake_minimum_required(VERSION 3.21.0)
project(ftxui-starter LANGUAGES CXX VERSION 1.0.0)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

set (CMAKE_CXX_STANDARD 26)

find_package(ftxui 5 REQUIRED)

add_executable(ftxui-starter main.cpp)

target_link_libraries(ftxui-starter
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)
enable_testing()
