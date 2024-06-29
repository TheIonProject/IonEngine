# Engine CMake

# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#set(TARGET_NAME "IonEngine")


file(GLOB_RECURSE TARGET_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(GLOB_RECURSE TARGET_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file(GLOB TARGET_EXTRA_FILES
	${CMAKE_SOURCE_DIR}/.gitignore
	${CMAKE_SOURCE_DIR}/.gitattributes
	${CMAKE_SOURCE_DIR}/*.md
)

file(GLOB COMMON_FILES
	${CMAKE_SOURCE_DIR}/ion/*.hpp
	${CMAKE_SOURCE_DIR}/ion/*.h
)

set (TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

# Useful files at the solution's root
source_group("extra files" FILES ${TARGET_EXTRA_FILES})

# Files shared by several modules
source_group("common" FILES ${COMMON_FILES})

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES} ${TARGET_EXTRA_FILES} ${COMMON_FILES})

target_include_directories(${TARGET_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET_NAME}
	PRIVATE ${DEPENDENCIES_LIBRARY}
	PRIVATE mathlib
)