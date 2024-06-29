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
#	Root CMake
#
#	DESCTIPTION: Root file, configures ion subfolder and write build files
#				 into build/ sibling folder
#
#
#

# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Solution name
project(IonEngine)


# Folder containing project files
add_subdirectory(ion)
