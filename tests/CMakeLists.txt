add_executable(
    TMTFTestProg
    test_main.cpp
)

target_link_libraries(
    TMTFTestProg
    testy
)

add_definitions(
    -std=c++98 -Wall -Werror -Wextra -pedantic
)

add_test(
    TMTFTest
    TMTFTestProg
)
