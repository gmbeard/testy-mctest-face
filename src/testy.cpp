#include "testy/testy.hpp"
#include <string>
#include <iostream>
#include <stddef.h>

using namespace testy;

FunctionList& testy::all_tests() {
    static FunctionList tests;
    return tests;
}

void testy::register_test(TestyMcTestFaceFunction f,
                          char const* name) 
{
    typedef std::pair<TestyMcTestFaceFunction, char const*> Test;
    all_tests().push_back(Test(f, name));
}

std::stringstream*& testy::testy_context() {
    static std::stringstream* context = 0;
    return context;
}

int testy::run_all_tests() {
    size_t failed = 0; 
    for (FunctionIter it = all_tests().begin();
         it != all_tests().end();
         ++it)
    {
        std::stringstream ctx;
        testy_context() = &ctx;
        try {
            (it->first)();
            std::cerr << "✔︎ " << (it->second) << "\n";
        }
        catch (std::exception const& e) {
            failed += 1;
            std::cerr << "✘ " << (it->second) << ": " << e.what() << "\n";
            std::string capture = ctx.str();
            if (!capture.empty()) {
                std::cerr << "  ▶︎ CAPTURE: " << capture << "\n";
            }
        }
        testy_context() = 0;
    }

    std::cerr << "\nTests succeeded: " 
        << all_tests().size() - failed << "/" << all_tests().size();

    if (failed) {
        std::cerr << " ✘\n";
    }
    else {
        std::cerr << " ✔︎\n";
    }

    return failed == 0 ? 0 : -1;
}

InlineRegistration::InlineRegistration(TestyMcTestFaceFunction f,
                                       char const* name) 
{
    register_test(f, name);
}

