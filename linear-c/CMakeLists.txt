cmake_minimum_required(VERSION 3.10)
project(LinearC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native")

include_directories(include)
include_directories(src/file)

set(SOURCES
    main/exec_dd.c
    src/calc/absorption_rate.c
    src/calc/escape_rate.c
    src/calc/quadrature.c
    src/calc/relative_deviation.c
    src/calc/scalar_flux.c
    src/calc/trival_solution_test.c
    src/core/init.c
    src/file/cJSON.c
    src/methods/dd.c
    src/methods/dd/medium_flux.c
    src/methods/dd/scattering_source.c
    src/methods/dd/sweep.c
)

add_executable(exec_dd ${SOURCES})
target_link_libraries(exec_dd m)
