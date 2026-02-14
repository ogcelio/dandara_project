cmake_minimum_required(VERSION 3.10)
project(LinearC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/cmd)

include_directories(include)
include_directories(src/file)

set(COMMON_SOURCES
    src/calc/absorption_rate.c
    src/calc/escape_rate.c
    src/calc/quadrature.c
    src/calc/relative_deviation.c
    src/calc/scalar_flux.c
    src/calc/trival_solution_test.c
    src/core/init.c
    src/file/cJSON.c
)

set(DD_SOURCES
    src/methods/dd.c
    src/methods/dd/medium_flux.c
    src/methods/dd/scattering_source.c
    src/methods/dd/sweep.c
)

set(MSD_SOURCES
    src/methods/msd.c
    src/methods/msd/alpha_matrix.c
    src/methods/msd/alpha.c
    src/methods/msd/angular_flux.c
    src/methods/msd/average_angular.c
    src/methods/msd/eigen.c
    src/methods/msd/particular_solution.c
    src/methods/msd/scattering_source.c
    src/methods/msd/solution_difference.c
)

add_executable(exec_dd main/exec_dd.c ${COMMON_SOURCES} ${DD_SOURCES})
target_link_libraries(exec_dd m)

add_executable(exec_msd main/exec_msd.c ${COMMON_SOURCES} ${MSD_SOURCES})
target_link_libraries(exec_msd m lapacke cblas lapack blas)
