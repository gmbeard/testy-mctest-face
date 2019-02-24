Testy Mc-Test Face
---

*Testy Mc-Test Face*, or simply *Testy*, is a small unit testing library with 
and emphasis on backwards compatibility with C++98.

### Using *Testy* in your Project
You can use *Testy* by adding it as a sub-directory or Git sub-module within 
your project and simply including its `cmake/Testy.cmake` file in your 
top-level `CMakeLists.txt` file.

For example:

Add *Testy* as a Git submodule

    # git submodule add https://github.com/gmbeard/testy-mctest-face.git testy

Include *Testy* in your project's `CMakeLists.txt` file

    list(APPEND CMAKE_MODULE_PATH testy/testy-mctest-face/cmake)
    include(Testy)

This will add the target `Testy::testy` to your project (and add *Testy*'s
include path). You can now just use `target_link_libraries` to link against 
this target.

    add_executable(MyTests my_tests.cpp)
    target_link_libraries(MyTests PRIVATE Testy::testy)

### Writing Tests
Tests are created using the `McTest(...) { ... }` macro. E.g.

    #include "testy/testy.hpp"

    McTest(add_two) {
        Expect(1 + 1 == 2);
    }

The `Expect(...)` macro is used to assert expectations. A failed expectation 
will terminate the current test.

### Running Tests
All of the tests defined using `McTest(...)` can be executed by simply adding 
`::testy::run_all_tests()` to your `main` function.

    int main(int argc, char const** argv) {
        return ::testy::run_all_tests();
    }
