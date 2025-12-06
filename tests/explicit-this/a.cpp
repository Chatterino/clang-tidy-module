// RUN: %c2-clang-tidy %s -- | FileCheck %s

class Foo
{
    int a;
    void xd();
};

void Foo::xd()
{
    a = 5;
    // CHECK: :[[@LINE-1]]:5: warning: use explicit 'this->' for member access [chatterino-explicit-this]

    this->a = 4;
    // CHECK-NOT: :[[@LINE-1]]
}
