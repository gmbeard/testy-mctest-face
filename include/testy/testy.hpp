#ifndef TESTY_TESTY_HPP_INCLUDED
#define TESTY_TESTY_HPP_INCLUDED

#include <vector>
#include <stdexcept>
#include <sstream>
#include <utility>
#include <cassert>

#define StringifyImpl(x) #x
#define Stringify(x) StringifyImpl(x)
#define Expect(cond)                        \
do {                                        \
    if (!(cond)) {                          \
        throw std::logic_error(             \
            "Expectation failed"            \
            ": " Stringify(cond)            \
            " (" __FILE__ ":" Stringify(__LINE__) ")"); \
    }                                       \
}                                           \
while (0)

#define ExpectThrows(statement, err_type)   \
do {                                        \
    bool thrown = false;                    \
    try {                                   \
        statement;                          \
    }                                       \
    catch (err_type const&) {               \
        thrown = true;                      \
    }                                       \
    Expect(thrown && "Statement should have thrown");   \
}                                           \
while (0)

#define Capture(x)                          \
do {                                        \
    assert(0 != ::testy::testy_context() && \
        "testy_context() is NULL. This shouldn't happen!");         \
    (*::testy::testy_context()) << "" Stringify(x) " == " << (x)    \
        << " (" << __FILE__ << ":" Stringify(__LINE__) << ")";      \
}                                           \
while (0)

#define McTest(name)                        \
void name();                                \
::testy::InlineRegistration const reg_##name(name, "" Stringify(name)); \
inline void name()

namespace testy {
typedef void (*TestyMcTestFaceFunction)();
typedef std::vector<std::pair<TestyMcTestFaceFunction, char const*> > 
    FunctionList;
typedef FunctionList::const_iterator FunctionIter;

FunctionList& all_tests();
void register_test(TestyMcTestFaceFunction f, char const* name);
int run_all_tests();
std::stringstream*& testy_context();

struct InlineRegistration {
    explicit InlineRegistration(TestyMcTestFaceFunction f,
                                char const* name);
};

}
#endif // TESTY_TESTY_HPP_INCLUDED
