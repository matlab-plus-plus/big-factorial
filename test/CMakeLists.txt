cmake_minimum_required(VERSION 3.23)
project(big-factorial-tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

if(BUILD_TESTING)
	add_executable(test_log)
	target_link_libraries(test_log gtest_main)
	target_include_directories(test_log PRIVATE ${CMAKE_SOURCE_DIR}/inc)
	target_sources(test_log
		PRIVATE ./src/logtest.cpp
		        ${CMAKE_SOURCE_DIR}/inc/math/log.hpp
	)
endif()
gtest_discover_tests(test_log)