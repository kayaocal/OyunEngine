cmake_minimum_required(VERSION 3.10)


# set the project name
project(Engine VERSION 0.0.1 DESCRIPTION "Best Engine is your Engine")


file (GLOB SOURCES 
	${CMAKE_SOURCE_DIR}/source/*.cpp
	${CMAKE_SOURCE_DIR}/source/*.c
	${CMAKE_SOURCE_DIR}/external/imconfig.h
	${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/imgui.h
	${CMAKE_SOURCE_DIR}/external/imgui/imgui_demo.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/imgui_internal.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/imgui_tables.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.h
	${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
	${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.h
	${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3_loader.h)

file (GLOB INCLUDES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)


add_library(Engine SHARED ${SOURCES} ${INCLUDES})

target_include_directories(Engine 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends)


target_link_libraries (Engine ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)


# Copy dlls

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/lib"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
#
#	PROJECT SAMPLES OVER ENGINE
# 	Define the executable

add_executable(EmptyWindowSample ${CMAKE_SOURCE_DIR}/samples/emptyWindow/emptywindow.cpp)

target_include_directories(EmptyWindowSample 
PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries (EmptyWindowSample Debug\\Engine.lib opengl32.lib)

#
#	EDITOR
# 	Define the executable

add_executable(Editor ${CMAKE_SOURCE_DIR}/editor/editor_main.cpp)

target_include_directories(Editor 
PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries (Editor Debug\\Engine.lib)

