cmake_minimum_required(VERSION 3.10)

# set the project name
project(Engine VERSION 0.0.1 DESCRIPTION "Best Engine is your Engine")


file (GLOB SOURCES "source/*.cpp")
file (GLOB INCLUDES "include/*.h")

add_library(Engine STATIC ${SOURCES} ${INCLUDES})

target_include_directories(Engine PUBLIC  
${PROJECT_SOURCE_DIR}/include)

