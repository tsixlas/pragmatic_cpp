cmake_minimum_required(VERSION 3.28)
project(PragmaticCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SourceFiles CONFIGURE_DEPENDS "src/*")
add_executable(PragmaticCPP ${SourceFiles})

include_directories(include)