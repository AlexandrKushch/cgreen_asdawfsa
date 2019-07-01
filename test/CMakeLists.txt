find_package(cgreen)
set(CGREEN_TEST cgreen_test_c)

set(Sources
    ${CMAKE_SOURCE_DIR}/src/coordinate.c
    ${CMAKE_SOURCE_DIR}/src/segmentSize.c 
    ${CMAKE_SOURCE_DIR}/src/matrix.c 
    ${CMAKE_SOURCE_DIR}/src/rotate.c
    ${CMAKE_SOURCE_DIR}/src/star.c
)

add_executable(${CGREEN_TEST} cgreen_test.c ${Sources})
target_link_libraries(${CGREEN_TEST} cgreen m)

add_test(NAME ${CGREEN_TEST} COMMAND ${CGREEN_TEST})

set(FCT_TEST fct_test_c)
add_executable(${FCT_TEST} test.c ${Sources})
target_link_libraries(${FCT_TEST} m)

add_test(NAME ${FCT_TEST} COMMAND ${FCT_TEST})