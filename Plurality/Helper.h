﻿#include <vector>
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

    template <typename T>
    void removeDuplicates(std::vector<T>& vec) {
        std::unordered_map<T, int> countMap;

        // Count occurrences of each element
        for (const auto& element : vec) {
            countMap[element]++;
        }

        // Remove elements with count > 1
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [&countMap](const T& element) { return countMap[element] > 1; }),
            vec.end());
    }

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

        for (const T& element : vec) {
            elementCount[element]++;
        }

        std::vector<T> result;

        for (const auto& pair : elementCount) {
            if (pair.second > 1) {
                for (int i = 0; i < pair.second; ++i) {
                    result.push_back(pair.first);
                }
            }
        }

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
    template<typename T>
    std::vector<T> compareVectors(const std::vector<T>& vec1, const std::vector<T>& vec2) {
        std::vector<T> result;
        int count = 0;

        for (int i = 0; i < vec2.size(); ++i) {
            int element = vec2[i];
            int found = 0;


            if (count < vec1.size() && vec1[count] == element) {
                found = 1;
                count++;
            }
            else if (count > vec1.size() && vec1.back() == element) {
                found = 1;
            }

            result.push_back(found);
        }

        return result;
    }
}