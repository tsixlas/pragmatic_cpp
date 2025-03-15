cmake_minimum_required(VERSION 3.28)
project(PragmaticCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SourceFiles CONFIGURE_DEPENDS "src/*")
file(GLOB HeaderFiles CONFIGURE_DEPENDS "inc/*")
add_executable(PragmaticCPP ${HeaderFiles} ${SourceFiles})

include_directories(include)