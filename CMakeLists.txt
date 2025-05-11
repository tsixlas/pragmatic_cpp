cmake_minimum_required(VERSION 3.28)
project(PragmaticCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

install(TARGETS ${PROJECT_NAME})
install(FILES ${PROJECT_NAME} ${HEADERS}
        DESTINATION include/${PROJECT_NAME}
        COMPONENT headers)
