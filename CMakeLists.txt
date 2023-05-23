cmake_minimum_required(VERSION 3.5)
project(tdoku VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -${OPT} ${ARGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -${OPT} ${ARGS}")

configure_file (
    "${CMAKE_SOURCE_DIR}/src/build_info.h.in"
    "${CMAKE_SOURCE_DIR}/src/build_info.h")

# a gcc-linkable library with just the fast solver
add_library(tdoku_object OBJECT src/solver_dpll_triad_simd.cc src/util.cc)

target_compile_options(tdoku_object PUBLIC -fno-exceptions -fno-rtti -fpic)

add_library(tdoku_static STATIC $<TARGET_OBJECTS:tdoku_object>)

set(GENERATE_SOLVER_SOURCES
        src/solver_dpll_triad_simd.cc)

add_definitions(-DMINISAT)

set(GENERATE_SOLVER_SOURCES ${GENERATE_SOLVER_SOURCES}
        other/other_minisat.cc)

set(GENERATE_SOLVER_SOURCES
        src/generator.cc
        src/util.cc
        ${GENERATE_SOLVER_SOURCES})

add_executable(generate src/generate.cc src/util.cc ${GENERATE_SOLVER_SOURCES})

target_link_libraries(generate minisat)
