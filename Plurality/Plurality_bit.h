#include "Plurality.h"

#include <algorithm>
#include <optional>

namespace math {
    template<typename Type>
    class plurality_bit {
    private:
        std::vector<int> _data;
        math::universum<Type>* _universum;

        size_t _real_size = 0;
        std::vector<Type> _real_data;

        void get_real_size() {
            _real_size = 0;
            for (const auto& el : _data) {
                if (el != 0) {
                    _real_size++;
                }
            }
        }

        void print() const {
            std::for_each(_data.begin(), _data.end(), [](const auto& value) {
                std::cout << value << " ";
                });
            std::cout << std::endl;
        }
        explicit plurality_bit(size_t size, math::universum<Type>* universum) { _data.resize(size); this->_universum = universum; }
    public:
        template<typename Arg=Type>
        explicit plurality_bit(math::plurality_set<Arg>* plurality, math::universum<Arg>* universum) {
            this->_universum = universum;
            this->_data.reserve(_universum->get_vec().size());

            for (const auto& element : _universum->get_vec()) {
                if (std::find(plurality->get_vec().begin(), plurality->get_vec().end(), element) != plurality->get_vec().end()) {
                    this->_data.push_back(1);
                }
                else {
                    this->_data.push_back(0);
                }
            }
            std::cout << *plurality;
        }

        plurality_bit operator+(const plurality_bit& other) {
            if (this->_universum == other._universum) {
                plurality_bit* result = new plurality_bit(this->_data.size(), this->_universum);

                for (size_t i = 0; i < this->_data.size(); ++i) {
                    result->_data[i] = this->_data[i] | other._data[i];
                }

                return *result;
                delete result;
            }
            else {
                std::cerr << "plurality_bit operations can be made only with the same universum!";
            }
        }

        plurality_bit operator-(const plurality_bit& other) {
            if (this->_universum == other._universum) {
                plurality_bit* result = new plurality_bit(this->_data.size(), this->_universum);

                for (size_t i = 0; i < this->_data.size(); ++i) {
                    result->_data[i] = this->_data[i] & other._data[i];
                }

                return *result;
                delete result;
            }
            else {
                std::cerr << "plurality_bit operations can be made only with the same universum!";
            }
        }

        plurality_bit operator/(const plurality_bit& other) {
            if (this->_universum == other._universum) {
                plurality_bit* result = new plurality_bit(this->_data.size(), this->_universum);

                for (size_t i = 0; i < this->_data.size(); ++i) {
                    result->_data[i] = this->_data[i] ^ other._data[i];
                }

                return *result;
                delete result;
            }
            else {
                std::cerr << "plurality_bit operations can be made only with the same universum!";
            }
        }

        void print_converted() {
            get_real_size();
            this->_real_data.resize(this->_real_size);

            for (size_t i = 0; i < this->_real_data.size(); i++) {
                if (this->_data[i] != 0) {
                    std::cout << this->_universum->get_vec()[i] << " ";
                }
            }
            std::cout << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os, const plurality_bit& t) {
            t.print();
            return os;
        }
    };
}