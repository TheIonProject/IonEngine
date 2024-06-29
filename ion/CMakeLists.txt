# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)



include(FetchContent)

FetchContent_Declare(
	mathlib
	GIT_REPOSITORY			https://github.com/TheIonProject/mathlib.git
	GIT_TAG					ion
	GIT_SHALLOW				ON
)



FetchContent_MakeAvailable(mathlib)



add_subdirectory(dependencies)
add_subdirectory(engine)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)
endif()