// RUN: %c2-clang-tidy %s -- | FileCheck %s

class Base
{
protected:
    virtual void c();
};

class Derived : Base
{
    void xd();
};

void Derived::xd()
{
    this->c();
    // CHECK-NOT: :[[@LINE-1]]

    c();
    // CHECK: :[[@LINE-1]]:5: warning: use explicit 'this->' for member access [chatterino-explicit-this]

    Base::c();
    // CHECK-NOT: :[[@LINE-1]]
}
