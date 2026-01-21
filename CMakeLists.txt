cmake_minimum_required(VERSION 3.16)
project(media_fix)

find_package(libobs REQUIRED)

add_library(media_fix MODULE src/plugin-main.c)
target_link_libraries(media_fix PRIVATE obs::libobs)

set_target_properties(media_fix PROPERTIES PREFIX "")
