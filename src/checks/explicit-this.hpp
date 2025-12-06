#pragma once

#include <clang-tidy/ClangTidyCheck.h>
#include <llvm/ADT/StringRef.h>

namespace chatterino {

class ExplicitThis : public clang::tidy::ClangTidyCheck
{
public:
    ExplicitThis(llvm::StringRef checkName, clang::tidy::ClangTidyContext *ctx);
    void registerMatchers(clang::ast_matchers::MatchFinder *Finder) override;
    void check(
        const clang::ast_matchers::MatchFinder::MatchResult &Result) override;
};

}  // namespace chatterino
