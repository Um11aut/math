﻿// Plurality.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include "Helper.h"

namespace math {

    template<typename Type>
    class plurality_set {
    private:
        std::vector<Type> _data;

        template<class ...Ts>
        void fill(Ts&&... args) {
            (_data.push_back(args), ...);
        }

        void print() const {
            std::for_each(this->_data.begin(), this->_data.end(), [](const auto& value) {
                std::cout << value << " ";
                });
        }
    public:
        template<class ...T>
        explicit plurality_set(T&&... args) {
            fill(std::forward<T>(args)...);
        }

        explicit plurality_set() = default;

        explicit plurality_set(std::vector<Type> vec) {
            this->_data.insert(this->_data.end(), vec.begin(), vec.end());
        }

        template<class ...Args>
        void append(Args&&... args) {
            this->_data.push_back(std::forward<Args>(args)...);
        }

        bool partOf(plurality_set<Type>* second) {
            for (const int& elem : this->_data) {
                if (std::find(second->get_vec().begin(), second->get_vec().end(), elem) == second->get_vec().end()) {
                    return false;
                }
            }
            return true;
        }

        plurality_set operator+(const plurality_set& other) {
            plurality_set res = *this;
            for (const auto& value : other._data) {
                if (std::find(this->_data.begin(), this->_data.end(), value) == this->_data.end()) {
                    res._data.push_back(value);
                }
            }

            return res;
        }

        bool operator==(const plurality_set& other) const {
            if (this->_data.size() == other._data.size()) {
                return this->_data == other._data;
            }
            return false;
        }

        plurality_set& operator=(const plurality_set& other) {
            this->_data = other._data;
            return *this;
        }

        plurality_set operator%(const plurality_set& other) {
            plurality_set temp = *this;
            for (const auto& value : other._data) {
                temp._data.push_back(value);
            }
            math_helper::removeDuplicates(temp._data);

            return temp;
        }

        plurality_set operator-(const plurality_set& other) {
            plurality_set res = *this;

            for (const auto& value : other._data) {
                res._data.push_back(value);
            }

            math_helper::removeUnique(res._data);

            return res;
        }

        plurality_set operator/(const plurality_set& other) {
            plurality_set res = *this;

            plurality_set temp = res;
            for (const auto& value : other._data) {
                temp._data.push_back(value);
            }

            math_helper::removeUnique(temp._data);

            math_helper::subtract(res._data, temp._data);

            return res;
        }

        friend std::ostream& operator<<(std::ostream& os, const plurality_set& t) {
            t.print();
            return os;
        }

        virtual std::vector<Type>& get_vec() {
            return this->_data;
        }
    };

    template<typename Type>
    class universum : public plurality_set<Type> {
    private:
        std::vector<Type> _data;

        template<class ...Ts>
        void fill(Ts... args) {
            (_data.push_back(args), ...);
        }
        void print() const {
            std::for_each(_data.begin(), _data.end(), [](const Type& value) {
                std::cout << value << " ";
                });
            std::cout << std::endl;
        }
    public:
        template<class ...T>
        explicit universum(T&&... args) {
            fill(std::forward<T>(args)...);
        }

        universum& operator=(const universum& other) {
            this->_data = other._data;
            return *this;
        }

        bool operator==(const universum& other) const {
            if (this->_data.size() == other._data.size()) {
                return this->_data == other._data;
            }
            return false;
        }

        std::vector<Type>& get_vec() override {
            return this->_data;
        }

        friend std::ostream& operator<<(std::ostream& os, const universum& t) {
            t.print();
            return os;
        }
    };

    template<typename Type>
    plurality_set<Type> findExtra(universum<Type>* U, plurality_set<Type>* T) {
        auto* U_copy = new plurality_set<Type>(U->get_vec());
        auto* T_copy = new plurality_set<Type>(T->get_vec());
        math_helper::subtract<Type>(U_copy->get_vec(), T_copy->get_vec());

        if (!U_copy->get_vec().empty()) {
            return *U_copy;
        }
        else {
            std::cerr << "Universum must be bigger than plurality" << std::endl;
            return plurality_set<Type>();
        }
        delete U_copy;
        delete T_copy;
    }

    template<class Arg1, class Arg2>
    plurality_set<std::pair<Arg1, Arg2>> multiply(plurality_set<Arg1>* a, plurality_set<Arg2>* b) {
        auto* res = new plurality_set<std::pair<Arg1, Arg2>>();

        for (const auto& elA : a->get_vec()) {
            for (const auto& elB : b->get_vec()) {
                res->append(std::make_pair(elA, elB));
            }
        }

        return *res;
        delete res;
    }
}
