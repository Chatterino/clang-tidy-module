class Base
{
protected:
    static void a();
};

class Derived : Base
{
    static void b();

    static int c;

    void xd();
};

void Derived::xd()
{
    Base::a();  // `chatterino-explicit-this` should _not_ warn about this

    Derived::a();  // `chatterino-explicit-this` should _not_ warn about this

    Derived::b();  // `chatterino-explicit-this` should _not_ warn about this

    Derived::c = 1;  // `chatterino-explicit-this` should _not_ warn about this

    c = 1;

    a();  // `chatterino-explicit-this` should _not_ warn about this

    b();  // `chatterino-explicit-this` should _not_ warn about this
}
