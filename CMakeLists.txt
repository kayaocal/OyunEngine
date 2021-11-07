cmake_minimum_required(VERSION 3.10)


# set the project name
project(Engine VERSION 0.0.1 DESCRIPTION "Best Engine is your Engine")

file (GLOB IMGUI_SOURCES
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

file (GLOB ENGINE_SOURCES 
	${CMAKE_SOURCE_DIR}/source/*.cpp
	${CMAKE_SOURCE_DIR}/source/*.c)

file (GLOB ENGINE_INCLUDES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)



add_library(Engine SHARED ${ENGINE_SOURCES} ${IMGUI_SOURCES} ${ENGINE_INCLUDES})

source_group("imgui" 	FILES ${IMGUI_SOURCES})

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

# #######################################################################################
#	EDITOR
# 	Define the executable
# #######################################################################################

file (GLOB EDITOR_SOURCES 
	${CMAKE_SOURCE_DIR}/editor/source/*.cpp
	${CMAKE_SOURCE_DIR}/editor/source/*.c)

file (GLOB EDITOR_INCLUDES 
	${CMAKE_SOURCE_DIR}/editor/include/*.h
	${CMAKE_SOURCE_DIR}/editor/include/*.hpp)

add_executable(Editor ${CMAKE_SOURCE_DIR}/editor/editor_main.cpp ${EDITOR_INCLUDES} ${EDITOR_SOURCES})

target_include_directories(Editor 
	PUBLIC ${CMAKE_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/editor/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends)

target_link_libraries (Editor Debug\\Engine.lib ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)

add_dependencies(Editor Engine)