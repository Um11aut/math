#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
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
    void filterDuplicates(std::vector<T>& vec)
    {
        std::unordered_set<T> seen;
        std::vector<T> result;

        for (const T& element : vec) {
            if (seen.insert(element).second) {
                // Inserted successfully, element is unique
                result.push_back(element);
            }
        }

        vec = std::move(result);
    }

    template<typename T>
    void removeUnique(std::vector<T>& vec)
    {
        std::unordered_map<T, int> elementCount;

        // Count the occurrences of each element
        for (const T& element : vec) {
            elementCount[element]++;
        }

        // Create a new vector to store the elements with duplicates
        std::vector<T> result;

        // Copy elements with duplicates to the result vector
        for (const auto& pair : elementCount) {
            if (pair.second > 1) {
                for (int i = 0; i < pair.second; ++i) {
                    result.push_back(pair.first);
                }
            }
        }

        // Replace the original vector with the result vector
        vec = std::move(result);

        math_helper::filterDuplicates(vec);
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