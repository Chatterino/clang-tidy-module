// RUN: %c2-clang-tidy %s -- | FileCheck %s

class Base
{
protected:
    static void a();
};

class Derived : Base
{
    static void b();

    static int c;

    int d;

    void xd();
};

void Derived::xd()
{
    Base::a();
    // CHECK-NOT: :[[@LINE-1]]

    Derived::a();
    // CHECK-NOT: :[[@LINE-1]]

    Derived::b();
    // CHECK-NOT: :[[@LINE-1]]

    Derived::c = 1;
    // CHECK-NOT: :[[@LINE-1]]

    c = 1;
    // CHECK-NOT: :[[@LINE-1]]

    d = 3;
    // CHECK: :[[@LINE-1]]:5: warning: use explicit 'this->' for member access [chatterino-explicit-this]

    a();
    // CHECK-NOT: :[[@LINE-1]]

    b();
    // CHECK-NOT: :[[@LINE-1]]
}
