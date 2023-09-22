// Plurality.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <tuple>
#include <limits>
#include <vector>
#include <type_traits>
#include <algorithm>

namespace math {
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

    template<typename ...T>
    class plurality {
    private:
        std::tuple<T...> data;

        template <class T1, class T2> struct equal
        {
            static_assert(std::is_same_v<T1, T2>, "types are not the same");
        };
    public:
        explicit plurality(T... args) : data(std::make_tuple(args...)) {}

        template <typename ...M>
        explicit plurality(std::tuple<M...> argT) : data(argT) {}

        virtual void print_range() {
            std::apply(
                [](auto&&... args) {
                    ((std::cout << args << " "), ...);
                }

            , data);
        }

        [[nodiscard]] std::tuple<T...> to_tuple() const {
            return data;
        }

        size_t size() {
            return sizeof...(T);
        }

        template <typename... U>
        plurality<T..., U...> operator+(const plurality<U...>& other) const {
            std::tuple<T..., U...> combined_data = std::tuple_cat(data, other.to_tuple());
            return plurality<T..., U...>(combined_data);
        }

        plurality& operator=(const plurality& other) {
            if (this == other) {
                return *this;
            }
            data = other.data;
            return *this;
        }

        template <typename... U>
        bool operator==(const plurality<U...>& other) const {
            if constexpr (sizeof...(T) == sizeof...(U)) {
                return data == other.to_tuple();
            }
            return false;
        }
    };

    template<typename U>
    class universum : public plurality<> {
    private:
        U minVal;
        U maxVal;
    public:
        universum() {
            if constexpr (math::Intable<U>) {
                minVal = std::numeric_limits<U>::min();
                maxVal = std::numeric_limits<U>::max();
            }
            else {
                throw std::runtime_error("Use int-like types(or remove unsigned)");
            }
        }

        void print_range() override {
            std::cout << minVal << " ... " << maxVal << std::endl;
        }
    };

} // math
