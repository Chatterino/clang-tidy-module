#include "checks/explicit-this.hpp"

#include <clang-tidy/ClangTidyCheck.h>
#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

namespace chatterino {

class Module : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(
        clang::tidy::ClangTidyCheckFactories &Factories) override
    {
        Factories.registerCheck<ExplicitThis>("chatterino-explicit-this");
    }
};

}  // namespace chatterino

namespace clang::tidy {

static ClangTidyModuleRegistry::Add<chatterino::Module> X(
    "chatterino", "Chatterino clang-tidy checks");
volatile int ClazyModuleAnchorSource = 0;

}  // namespace clang::tidy
