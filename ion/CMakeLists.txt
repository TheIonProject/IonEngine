#	 _____                               _
#	|_   _|                             (_)
#	  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
#	  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
#	 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
#	 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
#	                                __/ |
#	                               |___/
#
#
#	ion subfolder CMake file
#
#	DESCTIPTION: IonEngine/ion subfolder, fetches and configures dependencies
#				 before configuring engine project
#
#
#


# FetchContent is supported by CMake 3.24 and up
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)


include(FetchContent)

FetchContent_Declare(
	mathlib
	GIT_REPOSITORY			https://github.com/torrra/mathlib		# Fetch our math library from github
	GIT_TAG					main									# Get main branch
	GIT_SHALLOW				ON										# Allow branch names as GIT_TAG argument
)


# Ensure mathlib is populated
FetchContent_MakeAvailable(mathlib)

# Configure engine third-party dependencies
add_subdirectory(dependencies)

# Begin configuring engine
add_subdirectory(engine)
