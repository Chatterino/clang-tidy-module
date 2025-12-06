class Foo
{
    int a;
    void xd();
};

void Foo::xd()
{
    a = 5;  // `chatterino-explicit-this` should warn about this

    this->a = 4;  // `chatterino-explicit-this` should _not_ warn about this
}
