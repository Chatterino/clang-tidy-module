#include <memory>

class Foo : std::enable_shared_from_this<Foo>
{
    int a;
    void xd();
};

void Foo::xd()
{
    auto b = shared_from_this();  // `chatterino-explicit-this` should _not_ warn about this
}
