cmake_minimum_required(VERSION 3.16)
project(obs_media_fix)

find_package(libobs REQUIRED)

add_library(obs_media_fix MODULE src/plugin-main.c)
target_link_libraries(obs_media_fix PRIVATE obs::libobs)

set_target_properties(obs_media_fix PROPERTIES PREFIX "")
