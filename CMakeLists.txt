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


file (GLOB COMPONENT_SOURCES 
	${CMAKE_SOURCE_DIR}/source/components/*.cpp
	${CMAKE_SOURCE_DIR}/source/components/*.c)

file (GLOB COMPONENT_INCLUDES 
	${CMAKE_SOURCE_DIR}/include/components/*.h
	${CMAKE_SOURCE_DIR}/include/components/*.hpp)



add_library(Engine SHARED ${ENGINE_SOURCES} ${IMGUI_SOURCES} ${ENGINE_INCLUDES} ${COMPONENT_SOURCES} ${COMPONENT_INCLUDES})

source_group("Imgui" 			FILES ${IMGUI_SOURCES})
source_group("Source Files/Components" 	FILES ${COMPONENT_SOURCES})
source_group("Header Files/Components" 	FILES ${COMPONENT_INCLUDES})

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

# #######################################################################################
#	Simple Render
# 	Define the executable
# #######################################################################################

file (GLOB SIMPLE_RENDER_SOURCES 
	${CMAKE_SOURCE_DIR}/simple_render/source/*.cpp
	${CMAKE_SOURCE_DIR}/simple_render/source/*.c)

file (GLOB SIMPLE_RENDER_INCLUDES 
	${CMAKE_SOURCE_DIR}/simple_render/include/*.h
	${CMAKE_SOURCE_DIR}/simple_render/include/*.hpp)

add_executable(SimpleRender ${CMAKE_SOURCE_DIR}/simple_render/simple_render_main.cpp ${SIMPLE_RENDER_INCLUDES} ${SIMPLE_RENDER_SOURCES})

target_include_directories(SimpleRender 
	PUBLIC ${CMAKE_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/simple_render/include)

target_link_libraries (SimpleRender Debug\\Engine.lib ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)

add_dependencies(SimpleRender Engine)