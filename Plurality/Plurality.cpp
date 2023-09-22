#include "Plurality.h"

using namespace math;

int main() {
    plurality plurality1 = plurality(1, 2);
    plurality plurality2 = plurality(1, 2, 3, 4, 10, 22, 12);
    plurality plurality3 = plurality("str", "main", 0.f, 1.2, 'a', "proj");

    plurality p = plurality1 + plurality2 + plurality3;
    p.print_range();

    plurality a = plurality(1, 2);

    if (a == plurality2) {
        std::cout << "True" << std::endl;
    }
    std::cout << a.size() << std::endl;

    math::universum<int> u;
    u.print_range();

    return 0;
}