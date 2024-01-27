cmake_minimum_required(VERSION 3.28.1)

project(frogmake)

include_directories(include)
include_directories(src)

add_executable(frogmake
	src/frogmake.c 
	src/parsefile.c
	src/toml.c
	include/toml.h
	include/frogmake.h
	)





