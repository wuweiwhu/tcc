cmake_minimum_required(VERSION 3.0)
set(TCC_VERSION_MAJOR 0)
set(TCC_VERSION_MINOR 1)
project(TCC VERSION ${TCC_VERSION_MAJOR}.${TCC_VERSION_MINOR} LANGUAGES CXX)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(front-end)
#add_subdirectory(mid-end)
#add_subdirectory(backend-end)
#add_subdirectory(ir)
#add_subdirectory(tools)

set(TCC_COMPONENTS tcc-front-end)

foreach (COMPONENT ${TCC_COMPONENTS})
message(STATUS "Adding Component ${COMPONENT}")
  add_custom_command(
      OUTPUT ${COMPONENT}.out
      COMMAND "${CMAKE_COMMAND} -DCOMPONENT=${COMPONENT}
      -P ${CMAKE_BINARY_DIR}/cmake_install.cmake"
      COMMENT "Compiling ${COMPONENT}")
endforeach(COMPONENT)
