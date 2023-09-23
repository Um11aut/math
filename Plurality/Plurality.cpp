#include "Plurality.h"

int main() {
    math::plurality_set<int> t = math::plurality_set<int>(1, 2, 4, 5, 7);
    math::plurality_set<int> a = math::plurality_set<int>(4, 7, 8, 2, 5, 1);

    math::plurality_set<std::pair<int, int>> s = math::multiply(&t, &a);
    std::cout << "Прямий добуток множин A і B:" << std::endl;
    for (const auto& pair : s.get_vec()) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    std::cout << std::endl;

    math::plurality_set<int> bc = t + a;
    math::plurality_set<int> ba = t % a;
    math::plurality_set<int> bb = a - t;

    math::plurality_set<int> bd = t / a;

    std::cout << bd;

    math::plurality_set<int> test = math::plurality_set<int>(1);
    test.append(1);

    math::universum<int> u = math::universum<int>(1, 2, 3, 4, 5, 6, 7, 8);

    if (t.partOf(&u)) {
        std::cout << "True" << std::endl;
    }
    else {
        std::cout << "False" << std::endl;
    }

    math::plurality_set<int> ttt = math::findExtra<int>(&u, &t);
    return 0;
}
