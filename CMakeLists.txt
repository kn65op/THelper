cmake_minimum_required (VERSION 2.8.4) 

#variables
set(SRC_DIR "Code")
set(INCLUDE_DIR "include/THelper")
set(DEBUG_BIN_DIR "Debug")
set(RELEASE_BIN_DIR "Release")
set(LIB_NAME "THelper")

#project
project (thelper)

#externial libs

#compiler options
set(CMAKE_CXX_FLAGS "-std=c++14")

if ("${NO_COVERAGE}" STREQUAL "true")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
else ("${NO_COVERAGE}" STREQUAL "true")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
endif ("${NO_COVERAGE}" STREQUAL "true")

set(NORMAL_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
set(EXTRA_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall  -Wextra")

set(CMAKE_CXX_FLAGS_DEBUG "${EXTRA_WARNING_FLAGS}")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

#tests
set(COVERAGE_COMMAND "gcov")

set(CTEST_MEMORYCHECK_COMMAND "valgrind")
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --quiet
--tool=memcheck --leak-check=yes --show-reachable=yes
--num-callers=100 --verbose --demangle=yes")

#includes
include_directories(${INCLUDE_DIR})

#files
file(GLOB RANDOM_LIB_FILES ${SRC_DIR}/Random/src/*.cpp)
file(GLOB OS_LIB_FILES ${SRC_DIR}/OS/src/*.cpp)
file(GLOB CONFIGURATION_LIB_FILES ${SRC_DIR}/Configuration/src/*.cpp)
file(GLOB DATE_TIME_LIB_FILES ${SRC_DIR}/DateTime/src/*.cpp)
file(GLOB STREAM_LIB_FILES ${SRC_DIR}/Stream/src/*.cpp)
file(GLOB STRING_LIB_FILES ${SRC_DIR}/String/src/*.cpp)

#executables
if ("${NO_COVERAGE}" STREQUAL "true")
else ("${NO_COVERAGE}" STREQUAL "true")
	SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
	SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
	SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
	#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
endif ("${NO_COVERAGE}" STREQUAL "true")

#test
if (NOT "${NO_TEST}" STREQUAL "true")
  add_subdirectory(Test)
endif ( NOT "${NO_TEST}" STREQUAL "true")

add_library(${LIB_NAME} ${RANDOM_LIB_FILES}
	  		${OS_LIB_FILES}
			${CONFIGURATION_LIB_FILES}
			${DATE_TIME_LIB_FILES}
			${STREAM_LIB_FILES}
			${STRING_LIB_FILES}
			)

#libraries
#TARGET_LINK_LIBRARIES(${LIB_OUTPUT_FILE} ${Boost_LIBRARIES} )

#exporting for other projects
export(TARGETS ${LIB_NAME} FILE "${PROJECT_BINARY_DIR}/THelperTargets.cmake")
export(PACKAGE thelper)

set(EXPORT_TARGETS THelper CACHE INTERNAL "export targets")
set(CONFIG_INCLUDE_DIRS "${thelper_SOURCE_DIR}/include")
set(CONFIG_LIBRARY_DIR "${PROJECT_BINARY_DIR}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/thelper-config.cmake.in
       "${PROJECT_BINARY_DIR}/thelper-config.cmake" @ONLY)

