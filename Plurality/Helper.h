#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

namespace math_helper {
    template<typename S>
    concept Intable = requires(S a)
    {
        { static_cast<int>(a) } -> std::convertible_to<int>;
        { static_cast<double>(a) } -> std::convertible_to<int>;
        { static_cast<long>(a) } -> std::convertible_to<int>;
        { static_cast<float>(a) } -> std::convertible_to<int>;

        //exclude unsigned
            requires (!std::is_unsigned_v<S>);
    };

    template<typename T>
    void removeUnique(std::vector<T>& vec)
    {
        std::set<T> duplicates;

        std::sort(vec.begin(), vec.end());
        std::set<T> distinct(vec.begin(), vec.end());
        std::set_difference(vec.begin(), vec.end(), distinct.begin(), distinct.end(),
            std::inserter(duplicates, duplicates.end()));

        vec = std::vector<T>(duplicates.begin(), duplicates.end());
    }

    template<typename T>
    void subtract(std::vector<T>& first, std::vector<T>& second) {
        if (first.size() < second.size()) {
            first = std::vector<T>();
        }
        std::set<T> result;

        std::sort(first.begin(), first.end());
        std::sort(second.begin(), second.end());

        std::set_difference(first.begin(), first.end(), second.begin(), second.end(),
            std::inserter(result, result.end()));

        first = std::vector<T>(result.begin(), result.end());
    }
}