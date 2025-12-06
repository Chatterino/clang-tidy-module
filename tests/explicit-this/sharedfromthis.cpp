// RUN: %c2-clang-tidy %s -- | FileCheck %s

#include <memory>

class Foo : std::enable_shared_from_this<Foo>
{
    int a;
    void xd();
};

void Foo::xd()
{
    auto b = shared_from_this();
    // CHECK-NOT: :[[@LINE-1]]

    a = 1;
    // CHECK: :[[@LINE-1]]:5: warning: use explicit 'this->' for member access [chatterino-explicit-this]
}
