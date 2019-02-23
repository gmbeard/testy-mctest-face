#include "testy/testy.hpp"
#include <string>
#include <iostream>

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
    bool succeeded = true;
    for (FunctionIter it = all_tests().cbegin();
         it != all_tests().cend();
         ++it)
    {
        std::stringstream ctx;
        testy_context() = &ctx;
        try {
            (it->first)();
            std::cerr << (it->second) << " succeeded!\n";
        }
        catch (std::exception const& e) {
            std::cerr << (it->second) << " failed!: " << e.what() << "\n";
            succeeded = false;
            std::string capture = ctx.str();
            if (!capture.empty()) {
                std::cerr << "CAPTURE:\n" << capture << "\n";
            }
        }
        testy_context() = 0;
    }

    return succeeded ? 0 : -1;
}

InlineRegistration::InlineRegistration(TestyMcTestFaceFunction f,
                                       char const* name) 
{
    register_test(f, name);
}

