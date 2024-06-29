# Engine CMake

# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

#set(TARGET_NAME "IonEngine")


#add_subdirectory(ECS)

add_subdirectory(UI)

add_subdirectory(application)
 