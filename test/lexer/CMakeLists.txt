set(TARGET_NAME Test_Lexer)

set(TARGET_SRC test_lexer.cpp)

include_directories(
${FRONT_END_DIR}
)

add_executable(${TARGET_NAME} ${TARGET_SRC})

target_link_libraries(
 ${TARGET_NAME}
 tcc-front-end
)
install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_BINARY_DIR}/lib/test)
install(FILES test.c DESTINATION ${CMAKE_BINARY_DIR}/lib/test)
