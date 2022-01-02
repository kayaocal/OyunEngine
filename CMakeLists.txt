cmake_minimum_required(VERSION 3.10)

# set the project name
project(OyunEngine VERSION 0.0.1 DESCRIPTION "Best OyunEngine is your OyunEngine")

set (ENGINE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Engine)


file (GLOB IMGUI_SOURCES
	${CMAKE_SOURCE_DIR}/External/imgui/imconfig.h
	${CMAKE_SOURCE_DIR}/External/imgui/imgui.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/imgui.h
	${CMAKE_SOURCE_DIR}/External/imgui/imgui_demo.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/imgui_draw.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/imgui_internal.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/imgui_tables.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/imgui_widgets.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/backends/imgui_impl_glfw.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/backends/imgui_impl_glfw.h
	${CMAKE_SOURCE_DIR}/External/imgui/backends/imgui_impl_opengl3.cpp
	${CMAKE_SOURCE_DIR}/External/imgui/backends/imgui_impl_opengl3.h
	${CMAKE_SOURCE_DIR}/External/imgui/backends/imgui_impl_opengl3_loader.h)


file (GLOB JSONES_INCLUDE
	${CMAKE_SOURCE_DIR}/External/JSONes/Jsones.h)

file (GLOB JSONES_SOURCE
	${CMAKE_SOURCE_DIR}/External/JSONes/Jsones.cpp)

file (GLOB ASSIMP_INCLUDES
	${ENGINE_SOURCE_DIR}/Include/assimp/*.h
	${ENGINE_SOURCE_DIR}/Include/assimp/*/*.h)

file (GLOB ENGINE_SOURCES 
	${ENGINE_SOURCE_DIR}/Source/*.cpp
	${ENGINE_SOURCE_DIR}/Source/*.c)

file (GLOB ENGINE_INCLUDES 
	${ENGINE_SOURCE_DIR}/Include/*.h
	${ENGINE_SOURCE_DIR}/Include/*.hpp)

file (GLOB MATH_SOURCES 
	${ENGINE_SOURCE_DIR}/Source/Math/*.cpp
	${ENGINE_SOURCE_DIR}/Source/Math/*.c)

file (GLOB MATH_INCLUDES 
	${ENGINE_SOURCE_DIR}/Include/Math/*.h
	${ENGINE_SOURCE_DIR}/Include/Math/*.hpp)

file (GLOB COMPONENT_SOURCES 
	${ENGINE_SOURCE_DIR}/Source/Components/*.cpp
	${ENGINE_SOURCE_DIR}/Source/Components/*.c)

file (GLOB COMPONENT_INCLUDES 
	${ENGINE_SOURCE_DIR}/Include/Components/*.h
	${ENGINE_SOURCE_DIR}/Include/Components/*.hpp)

file (GLOB SUBSYSTEM_SOURCES 
	${ENGINE_SOURCE_DIR}/Source/Subsystems/*.cpp
	${ENGINE_SOURCE_DIR}/Source/Subsystems/*.c)

file (GLOB SUBSYSTEM_INCLUDES 
	${ENGINE_SOURCE_DIR}/Include/Subsystems/*.h
	${ENGINE_SOURCE_DIR}/Include/Subsystems/*.hpp)

file (GLOB GLM_INCLUDES 
	${ENGINE_SOURCE_DIR}/Include/glm/*.h
	${ENGINE_SOURCE_DIR}/Include/glm/*.hpp
	${ENGINE_SOURCE_DIR}/Include/glm/*.cpp
	${ENGINE_SOURCE_DIR}/Include/glm/*/*.h
	${ENGINE_SOURCE_DIR}/Include/glm/*/*.hpp
	${ENGINE_SOURCE_DIR}/Include/glm/*/*.cpp)


add_library(OyunEngine SHARED ${ENGINE_SOURCES} ${JSONES_SOURCE} ${JSONES_INCLUDE} ${IMGUI_SOURCES} ${ENGINE_INCLUDES} ${COMPONENT_SOURCES} ${COMPONENT_INCLUDES} ${MATH_SOURCES} ${MATH_INCLUDES} ${SUBSYSTEM_INCLUDES} ${SUBSYSTEM_SOURCES} ${GLM_INCLUDES} ${ASSIMP_INCLUDES})

target_compile_features(OyunEngine PRIVATE cxx_std_11)

source_group("Imgui" 						FILES ${IMGUI_SOURCES})
source_group("Source Files/Math"	 		FILES ${MATH_SOURCES})
source_group("Header Files/Math"	 		FILES ${MATH_INCLUDES})
source_group("Source Files/Components" 		FILES ${COMPONENT_SOURCES})
source_group("Header Files/Components" 		FILES ${COMPONENT_INCLUDES})
source_group("Header Files/Subsystems" 		FILES ${SUBSYSTEM_INCLUDES})
source_group("Source Files/Subsystems" 		FILES ${SUBSYSTEM_SOURCES})
source_group("Header Files/GLM" 			FILES ${GLM_INCLUDES})
source_group("Header Files/Assimp" 			FILES ${ASSIMP_INCLUDES})
source_group("Header Files/Tools/JSONes"	FILES ${JSONES_INCLUDE})
source_group("Source Files/Tools/JSONes"	FILES ${JSONES_SOURCE})

target_include_directories(OyunEngine 
	PUBLIC ${PROJECT_SOURCE_DIR}/Engine/Include
	PUBLIC ${PROJECT_SOURCE_DIR}/External/JSONes/
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui/backends)


target_link_libraries (OyunEngine $(OutDir)glfw3.lib opengl32.lib $(OutDir)assimp-vc142-mt.lib)


# Copy dlls

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/Libs"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# #######################################################################################
#	FLOATING CUBES
# 	Basic Project
# #######################################################################################

set(FLOATING_CUBES_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Samples/FloatingCubes)

file (GLOB FLOATING_CUBES_SOURCES
	${FLOATING_CUBES_SOURCE_DIR}/Source/*.cpp
	${FLOATING_CUBES_SOURCE_DIR}/Source/*.c)


file (GLOB FLOATING_CUBES_INCLUDES
	${FLOATING_CUBES_SOURCE_DIR}/Include/*.hpp
	${FLOATING_CUBES_SOURCE_DIR}/Include/*.h)

add_library(FloatingCubes SHARED ${FLOATING_CUBES_INCLUDES} ${FLOATING_CUBES_SOURCES} )

target_compile_features(FloatingCubes PRIVATE cxx_std_11)

target_include_directories(FloatingCubes 
	PUBLIC ${ENGINE_SOURCE_DIR}/Include
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui/backends
	PUBLIC ${FLOATING_CUBES_SOURCE_DIR}/Include)

target_link_libraries (FloatingCubes $(OutDir)OyunEngine.lib $(OutDir)glfw3.lib opengl32.lib)

add_dependencies(FloatingCubes OyunEngine)

# #######################################################################################
#	EDITOR
# 	DLL the executable
# #######################################################################################

set(EDITOR_SOURCE_DIR ${PROJECT_SOURCE_DIR}/editor)

file (GLOB EDITOR_SOURCES 
	${EDITOR_SOURCE_DIR}/Source/*.cpp
	${EDITOR_SOURCE_DIR}/Source/*.c)

file (GLOB EDITOR_INCLUDES 
	${EDITOR_SOURCE_DIR}/Include/*.h
	${EDITOR_SOURCE_DIR}/Include/*.hpp)

add_library(OyunEditor SHARED ${EDITOR_INCLUDES} ${EDITOR_SOURCES})

target_include_directories(OyunEditor 
	PUBLIC ${ENGINE_SOURCE_DIR}/Include
	PUBLIC ${EDITOR_SOURCE_DIR}/Include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/JSONes/
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui/backends
	PUBLIC ${FLOATING_CUBES_SOURCE_DIR}/Include)

target_link_libraries (OyunEditor $(OutDir)OyunEngine.lib $(OutDir)FloatingCubes.lib $(OutDir)glfw3.lib opengl32.lib)

target_compile_features(OyunEditor PRIVATE cxx_std_11)

add_dependencies(OyunEditor OyunEngine FloatingCubes)

# #######################################################################################
#	EDITOR STARTER
# 	Define the executable
# #######################################################################################

set(EDITOR_STARTER_DIR ${PROJECT_SOURCE_DIR}/EditorStarter)

add_executable(OyunEditorStarter ${EDITOR_STARTER_DIR}/EditorStarter.cpp)

target_include_directories(OyunEditorStarter
	PUBLIC ${ENGINE_SOURCE_DIR}/Include
	PUBLIC ${EDITOR_SOURCE_DIR}/Include
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui/backends)


target_link_libraries (OyunEditorStarter $(OutDir)OyunEditor.lib $(OutDir)OyunEngine.lib $(OutDir)glfw3.lib opengl32.lib)

target_compile_features(OyunEditorStarter PRIVATE cxx_std_11)

add_dependencies(OyunEditorStarter OyunEngine OyunEditor FloatingCubes)

# #######################################################################################
#	FLOATING CUBES STARTER
# 	Define the executable
# #######################################################################################

set(FLOATING_CUBES_STARTER_DIR ${PROJECT_SOURCE_DIR}/Samples/FloatingCubesStarter)

add_executable(FloatingCubesStarter ${FLOATING_CUBES_STARTER_DIR}/FloatingCubesStarter.cpp)

target_include_directories(FloatingCubesStarter
	PUBLIC ${ENGINE_SOURCE_DIR}/Include
	PUBLIC ${FLOATING_CUBES_SOURCE_DIR}/Include
	PUBLIC ${PROJECT_SOURCE_DIR}/external/JSONes/
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/External/imgui/backends)


target_link_libraries (FloatingCubesStarter $(OutDir)FloatingCubes.lib $(OutDir)OyunEngine.lib $(OutDir)glfw3.lib opengl32.lib)

target_compile_features(FloatingCubesStarter PRIVATE cxx_std_11)

add_dependencies(FloatingCubesStarter OyunEngine FloatingCubes)