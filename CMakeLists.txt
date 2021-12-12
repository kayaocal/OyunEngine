cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 11)

# set the project name
project(OyunEngine VERSION 0.0.1 DESCRIPTION "Best OyunEngine is your OyunEngine")

set (ENGINE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/engine)

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

file (GLOB CAREAL_INCLUDES
	${CMAKE_SOURCE_DIR}/external/careal/include/cereal/*.*
	${CMAKE_SOURCE_DIR}/external/careal/include/cereal/*/*.*
	${CMAKE_SOURCE_DIR}/external/careal/include/cereal/*/*/*.*
	${CMAKE_SOURCE_DIR}/external/careal/include/cereal/*/*/*/*.*
	)

file (GLOB ASSIMP_INCLUDES
	${ENGINE_SOURCE_DIR}/include/assimp/*.h
	${ENGINE_SOURCE_DIR}/include/assimp/*/*.h)

file (GLOB ENGINE_SOURCES 
	${ENGINE_SOURCE_DIR}/source/*.cpp
	${ENGINE_SOURCE_DIR}/source/*.c)

file (GLOB ENGINE_INCLUDES 
	${ENGINE_SOURCE_DIR}/include/*.h
	${ENGINE_SOURCE_DIR}/include/*.hpp)


file (GLOB COMPONENT_SOURCES 
	${ENGINE_SOURCE_DIR}/source/components/*.cpp
	${ENGINE_SOURCE_DIR}/source/components/*.c)

file (GLOB COMPONENT_INCLUDES 
	${ENGINE_SOURCE_DIR}/include/components/*.h
	${ENGINE_SOURCE_DIR}/include/components/*.hpp)

file (GLOB SUBSYSTEM_SOURCES 
	${ENGINE_SOURCE_DIR}/source/subsystems/*.cpp
	${ENGINE_SOURCE_DIR}/source/subsystems/*.c)

file (GLOB SUBSYSTEM_INCLUDES 
	${ENGINE_SOURCE_DIR}/include/subsystems/*.h
	${ENGINE_SOURCE_DIR}/include/subsystems/*.hpp)

file (GLOB GLM_INCLUDES 
	${ENGINE_SOURCE_DIR}/include/glm/*.h
	${ENGINE_SOURCE_DIR}/include/glm/*.hpp
	${ENGINE_SOURCE_DIR}/include/glm/*.cpp
	${ENGINE_SOURCE_DIR}/include/glm/*/*.h
	${ENGINE_SOURCE_DIR}/include/glm/*/*.hpp
	${ENGINE_SOURCE_DIR}/include/glm/*/*.cpp)

add_library(OyunEngine SHARED ${ENGINE_SOURCES} ${IMGUI_SOURCES} ${ENGINE_INCLUDES} ${COMPONENT_SOURCES} 
	${COMPONENT_INCLUDES} ${SUBSYSTEM_INCLUDES} ${SUBSYSTEM_SOURCES} ${GLM_INCLUDES} ${ASSIMP_INCLUDES} ${CAREAL_INCLUDES})

source_group("Imgui" 						FILES ${IMGUI_SOURCES})
source_group("Careal" 						FILES ${CAREAL_INCLUDES})
source_group("Source Files/Components" 		FILES ${COMPONENT_SOURCES})
source_group("Header Files/Components" 		FILES ${COMPONENT_INCLUDES})
source_group("Header Files/Subsystems" 		FILES ${SUBSYSTEM_INCLUDES})
source_group("Source Files/Subsystems" 		FILES ${SUBSYSTEM_SOURCES})
source_group("Header Files/GLM" 			FILES ${GLM_INCLUDES})
source_group("Header Files/Assimp" 			FILES ${ASSIMP_INCLUDES})

target_include_directories(OyunEngine 
	PUBLIC ${PROJECT_SOURCE_DIR}/engine/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/careal/include
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
#	FLOATING CUBES
# 	Basic Project
# #######################################################################################

set(FLOATING_CUBES_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Samples/FloatingCubes)

file (GLOB FLOATING_CUBES_SOURCES
	${FLOATING_CUBES_SOURCE_DIR}/source/*.cpp
	${FLOATING_CUBES_SOURCE_DIR}/source/*.c)


file (GLOB FLOATING_CUBES_INCLUDES
	${FLOATING_CUBES_SOURCE_DIR}/include/*.hpp
	${FLOATING_CUBES_SOURCE_DIR}/include/*.h)

add_library(FloatingCubes SHARED ${FLOATING_CUBES_INCLUDES} ${FLOATING_CUBES_SOURCES} )

target_include_directories(FloatingCubes 
	PUBLIC ${ENGINE_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/careal/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends
	PUBLIC ${FLOATING_CUBES_SOURCE_DIR}/include)

target_link_libraries (FloatingCubes $(OutDir)OyunEngine.lib ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)

add_dependencies(FloatingCubes OyunEngine)

# #######################################################################################
#	EDITOR
# 	DLL the executable
# #######################################################################################

set(EDITOR_SOURCE_DIR ${PROJECT_SOURCE_DIR}/editor)

file (GLOB EDITOR_SOURCES 
	${EDITOR_SOURCE_DIR}/source/*.cpp
	${EDITOR_SOURCE_DIR}/source/*.c)

file (GLOB EDITOR_INCLUDES 
	${EDITOR_SOURCE_DIR}/include/*.h
	${EDITOR_SOURCE_DIR}/include/*.hpp)

add_library(OyunEditor SHARED ${EDITOR_INCLUDES} ${EDITOR_SOURCES})

target_include_directories(OyunEditor 
	PUBLIC ${ENGINE_SOURCE_DIR}/include
	PUBLIC ${EDITOR_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/careal/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends
	PUBLIC ${FLOATING_CUBES_SOURCE_DIR}/include)

target_link_libraries (OyunEditor $(OutDir)OyunEngine.lib $(OutDir)FloatingCubes.lib ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)

add_dependencies(OyunEditor OyunEngine FloatingCubes)

# #######################################################################################
#	EDITOR STARTER
# 	Define the executable
# #######################################################################################

set(EDITOR_STARTER_DIR ${PROJECT_SOURCE_DIR}/editor_starter)

add_executable(OyunEditorStarter ${EDITOR_STARTER_DIR}/editor_starter.cpp)

target_include_directories(OyunEditorStarter
	PUBLIC ${ENGINE_SOURCE_DIR}/include
	PUBLIC ${EDITOR_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/careal/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends)


target_link_libraries (OyunEditorStarter $(OutDir)OyunEditor.lib $(OutDir)OyunEngine.lib ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)

add_dependencies(OyunEditorStarter OyunEngine OyunEditor FloatingCubes)

# #######################################################################################
#	FLOATING CUBES STARTER
# 	Define the executable
# #######################################################################################

set(FLOATING_CUBES_STARTER_DIR ${PROJECT_SOURCE_DIR}/floating_cubes_starter)

add_executable(FloatingCubesStarter ${FLOATING_CUBES_STARTER_DIR}/floating_starter.cpp)

target_include_directories(FloatingCubesStarter
	PUBLIC ${ENGINE_SOURCE_DIR}/include
	PUBLIC ${FLOATING_CUBES_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/careal/include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/external/imgui/backends)


target_link_libraries (FloatingCubesStarter $(OutDir)FloatingCubes.lib $(OutDir)OyunEngine.lib ${CMAKE_SOURCE_DIR}/lib/glfw3.lib opengl32.lib)

add_dependencies(FloatingCubesStarter OyunEngine FloatingCubes)