cmake_minimum_required(VERSION 2.8)
project(tcc)

set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/9.2.0_2/bin/g++-9")
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

include_directories(./utils/include)

aux_source_directory(. MAINSRC)
add_subdirectory(frontend)
add_subdirectory(mid_end)
add_subdirectory(backend)

add_executable(tcc ${MAINSRC})
target_link_libraries(tcc frontend)

add_custom_command(TARGET tcc  PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test $<TARGET_FILE_DIR:tcc>
                   COMMENT "Copying test")

