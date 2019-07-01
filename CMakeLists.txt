cmake_minimum_required(VERSION 3.13)
project(Task02)
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/dist)

add_executable(Task02 src/main.c src/coordinate.c src/segmentSize.c src/matrix.c src/rotate.c src/star.c)
target_link_libraries(Task02 m)

# add_custom_target(
#        build ALL
#        COMMAND
#            cd ${CMAKE_SOURCE_DIR}
#            && rm -rf out dist html
#            && mkdir out dist html
#            && clang-format -i src/main.c src/coordinate.c test/test.c src/coordinate.h src/segmentSize.c src/segmentSize.h src/matrix.c src/matrix.h src/rotate.c src/rotate.h test/cgreen_test.c
#            && clang-tidy src/main.c src/coordinate.c src/coordinate.h test/test.c src/segmentSize.c src/segmentSize.h src/matrix.c src/matrix.h src/rotate.c src/rotate.h test/cgreen_test.c
#            && clang -std=c11 -Wall -Wextra -Werror -Wpedantic src/main.c src/coordinate.c src/segmentSize.c src/matrix.c src/rotate.c -o dist/main.out -lm
#            && doxygen Doxyfile
# )

enable_testing()
add_subdirectory(test)