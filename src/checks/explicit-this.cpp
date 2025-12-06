#include "checks/explicit-this.hpp"

#include <clang-tidy/ClangTidyCheck.h>
#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/Expr.h>
#include <clang/AST/ParentMap.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Basic/SourceLocation.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Lex/Lexer.h>

#include <iostream>

namespace chatterino {

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tidy;

ExplicitThis::ExplicitThis(llvm::StringRef checkName,
                           clang::tidy::ClangTidyContext *ctx)
    : ClangTidyCheck(checkName, ctx)
{
}

void ExplicitThis::registerMatchers(MatchFinder *finder)
{
    finder->addMatcher(memberExpr().bind("memberExpr"), this);
}

void ExplicitThis::check(const MatchFinder::MatchResult &result)
{
    const auto *expr = result.Nodes.getNodeAs<MemberExpr>("memberExpr");
    if (!expr)
    {
        return;
    }

    // Only act on implicit member accesses (no explicit base like this-> or obj.)
    if (!expr->isImplicitAccess())
    {
        // std::cerr << "is explicit access "
        //           << expr->getMemberNameInfo().getName().getAsString() << " - "
        //           << expr->isImplicitCXXThis() << '\n';

        // expr->dumpPretty(*result.Context);
        // std::cerr << '\n';
        return;
    }

    const auto *decl = expr->getMemberDecl();
    if (!decl)
    {
        return;
    }

    if (expr->getMemberNameInfo().getName().getAsString() == "shared_from_this")
    {
        // TODO: make this a setting
        return;
    }

    if (expr->getQualifier() != nullptr)
    {
        // usage has qualifier (e.g. `Base::`)
        return;
    }

    // Skip static members (they don't need `this->`).
    if (const auto *FD = dyn_cast<FieldDecl>(decl))
    {
        auto xd = FD->firstType;
        // if (clang_Cursor_getStorageClass(*FD)) {
        // }
    }
    if (const auto *MD = dyn_cast<CXXMethodDecl>(decl))
    {
        // std::cerr << "is c++ method decl "
        //           << expr->getMemberNameInfo().getName().getAsString() << '\n';

        // expr->dumpPretty(*result.Context);
        // std::cerr << '\n';
        if (MD->isStatic())
            return;
    }

    // const auto *functionDecl = result.Context->getParents(*expr).begin()->get<FunctionDecl>();

    SourceManager &SM = *result.SourceManager;
    SourceLocation InsertLoc = expr->getBeginLoc();

    // Avoid suggesting inside macros.
    if (InsertLoc.isMacroID())
    {
        return;
    }

    auto Diag = diag(InsertLoc, "use explicit 'this->' for member access")
                << FixItHint::CreateInsertion(InsertLoc, "this->");
}

}  // namespace chatterino
