cmake_minimum_required(VERSION 3.23)

project(BigFactorial
	VERSION 0.0.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(big-factorial)

target_include_directories(big-factorial PUBLIC ./inc)
target_sources(big-factorial
	PRIVATE ./inc/factorize.hpp
	        ./inc/math/log.hpp
	        ./src/factorize.cpp
)

# Demonstration of the factoring capability
add_executable(factor-demo)
target_include_directories(factor-demo PRIVATE ./inc)
target_sources(factor-demo
	PRIVATE ./inc/factorize.hpp
	        ./src/demo/factor-int.cpp
)