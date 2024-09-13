
#include <memory>
#include <iostream>

int main(int argc, char* argv[])
{
    std::shared_ptr<int> p1(new int(10));
    // std::shared_ptr<int> p2(p1);
    std::cout << *p1 << std::endl;

    p1.reset();
    std::cout << *p1 << std::endl;

    return 0;
}
