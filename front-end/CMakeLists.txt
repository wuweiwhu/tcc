set(TARGET_NAME front_end)
set(TARGET_SRC
    lexer_impl.cpp
    parser_impl.cpp
    parser.cpp
)
add_library(${TARGET_NAME}  ${TARGET_SRC})
install(TARGETS front_end DESTINATION ${CMAKE_BINARY_DIR}/lib COMPONENT tcc-front-end)
