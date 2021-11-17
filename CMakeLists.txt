cmake_minimum_required(VERSION 3.10)


# set the project name
project(OyunEngine VERSION 0.0.1 DESCRIPTION "Best OyunEngine is your OyunEngine")

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

file (GLOB ASSIMP_INCLUDES
	${CMAKE_SOURCE_DIR}/include/assimp/*.h
	${CMAKE_SOURCE_DIR}/include/assimp/*/*.h)

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

file (GLOB GLM_INCLUDES 
	${CMAKE_SOURCE_DIR}/include/glm/*.h
	${CMAKE_SOURCE_DIR}/include/glm/*.hpp
	${CMAKE_SOURCE_DIR}/include/glm/*.cpp
	${CMAKE_SOURCE_DIR}/include/glm/*/*.h
	${CMAKE_SOURCE_DIR}/include/glm/*/*.hpp
	${CMAKE_SOURCE_DIR}/include/glm/*/*.cpp)

add_library(OyunEngine SHARED ${ENGINE_SOURCES} ${IMGUI_SOURCES} ${ENGINE_INCLUDES} ${COMPONENT_SOURCES} ${COMPONENT_INCLUDES} ${GLM_INCLUDES} ${ASSIMP_INCLUDES})

source_group("Imgui" 					FILES ${IMGUI_SOURCES})
source_group("Source Files/Components" 	FILES ${COMPONENT_SOURCES})
source_group("Header Files/Components" 	FILES ${COMPONENT_INCLUDES})
source_group("Header Files/GLM" 		FILES ${GLM_INCLUDES})
source_group("Header Files/Assimp" 		FILES ${ASSIMP_INCLUDES})

target_include_directories(OyunEngine 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends)


target_link_libraries (OyunEngine ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib ${CMAKE_SOURCE_DIR}/lib/assimp-vc142-mt.lib)


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

add_executable(OyunEditor ${CMAKE_SOURCE_DIR}/editor/editor_main.cpp ${EDITOR_INCLUDES} ${EDITOR_SOURCES})

target_include_directories(OyunEditor 
	PUBLIC ${CMAKE_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/editor/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends)

target_link_libraries (OyunEditor Debug\\OyunEngine.lib ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)

add_dependencies(OyunEditor OyunEngine)

