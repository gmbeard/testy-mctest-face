#include "testy/testy.hpp"

#define UNUSED(x) (void)(x)

McTest(add_two) {
    int r = 1 + 1;
    Capture(r);
    Expect(r == 3);
}

McTest(add_three) {
    Expect(1 + 1 + 1 == 3);
}

int main(int argc, char const** argv) {
    UNUSED(argc);
    UNUSED(argv);

    return testy::run_all_tests();
}
