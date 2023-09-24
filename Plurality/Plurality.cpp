#include "Plurality_bit.h"

int main() {
    auto A = math::plurality_set<int>(1, 2, 4, 5, 7);
    auto B = math::plurality_set<int>(4, 7, 8, 2, 5, 1);
    auto U = math::universum<int>(1, 2, 3, 4, 5, 6, 7, 8);

    math::plurality_set<std::pair<int, int>> s = math::multiply(&A, &B);

    std::cout << "Результат множення A*B" << std::endl;

    for (const auto& pair : s.get_vec()) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    std::cout << std::endl;


    math::plurality_set<int> test = math::plurality_set<int>(1);
    test.append(1);

    math::universum<int> u = math::universum<int>(1, 2, 3, 4, 5, 6, 7, 8);
    math::universum<int> uC = math::universum<int>(1, 2, 3, 4, 5, 6, 7, 8);

    std::cout << std::endl;

    if (u == uC) {
        std::cout << "u та uC однакові" << std::endl;
    }

    if (A.partOf(&B)) {
        std::cout << "А є підмножиною B" << std::endl;
    }

    std::cout << std::endl;

    math::plurality_set<int> ttt = math::findExtra<int>(&U, &B);
    std::cout << "Доповнення до множини B з універсуму U" << std::endl;
    std::cout << ttt << std::endl;

    std::cout << std::endl;

    std::cout << "Небітові операції над множинами" << std::endl;
    std::cout << A + B << std::endl; // об'єднання
    std::cout << A - B << std::endl; // перетин
    std::cout << B % A << std::endl; // симетрична різниця

    // std::cout << B / A << std::endl; // різниця

    auto AU = math::plurality_bit<int>(&A, &U);
    auto BU = math::plurality_bit<int>(&B, &U);

    auto test1 = AU + BU; // об'єднання
    auto test2 = AU - BU; // перетин
    auto test3 = AU % BU; // симетрична різниця

    std::cout << std::endl;

    std::cout << "Бітовий рядок множини A(з універсуму U)" << std::endl;

    std::cout << AU << std::endl;

    std::cout << "Конвертовані бітові рядки операцій A(з універсуму U) і B(з універсуму U)" << std::endl;
    test1.print_converted();
    test2.print_converted();
    test3.print_converted();

    return 0;
}
