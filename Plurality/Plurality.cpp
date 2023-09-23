#include "Plurality_bit.h"

int main() {
    auto A = math::plurality_set<int>(1, 2, 4, 5, 7);
    auto B = math::plurality_set<int>(4, 7, 8, 2, 5, 1);
    auto U = math::universum<int>(1, 2, 3, 4, 5, 6, 7, 8);


    math::plurality_set<std::pair<int, int>> s = math::multiply(&A, &B);

    for (const auto& pair : s.get_vec()) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    std::cout << std::endl;


    math::plurality_set<int> test = math::plurality_set<int>(1);
    test.append(1);

    math::universum<int> u = math::universum<int>(1, 2, 3, 4, 5, 6, 7, 8);
    math::universum<int> uC = math::universum<int>(1, 2, 3, 4, 5, 6, 7, 8);

    if (A.partOf(&B)) {
    }

    math::plurality_set<int> ttt = math::findExtra<int>(&U, &B);


    auto AU = math::plurality_bit<int>(&A, &U);
    auto BU = math::plurality_bit<int>(&B, &U);

    std::cout << BU;

    auto test1 = AU + BU;
    auto test2 = AU - BU;
    auto test3 = AU / BU;

    test1.print_converted();


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}
