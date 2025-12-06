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
    this->c();  // `chatterino-explicit-this` should _not_ warn about this

    c();  // `chatterino-explicit-this` should warn about this

    Base::c();  // `chatterino-explicit-this` should _not_ warn about this
}
