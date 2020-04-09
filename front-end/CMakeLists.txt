set(TARGET_NAME tcc-front-end)
set(TARGET_SRC lexer.cpp)
add_library(${TARGET_NAME}  ${TARGET_SRC})
install(TARGETS tcc-front-end DESTINATION ${CMAKE_BINARY_DIR}/lib)
