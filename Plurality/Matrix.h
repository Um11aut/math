#include "Helper.h"
#include <vector>

namespace math {
	class matrix {
	private:
		std::vector<std::vector<int>> _matrix;
        int n, m;

        template<typename T, typename... Values>
        void fillHelper(int row, int col, T&& val, Values&&... rest) {
            // Set the value in the current position
            _matrix[row][col] = std::forward<T>(val);

            // Move to the next position
            if (++col == _matrix[0].size()) {
                col = 0;
                ++row;
            }

            // Recursively call the function for the remaining values
            if constexpr (sizeof...(rest) > 0) {
                fillHelper(row, col, std::forward<Values>(rest)...);
            }
        }
	public:
		matrix(int& n, int& m) {
            this->n = n;
            this->m = m;

			_matrix.resize(n, std::vector<int>(m));
		}

		template<typename ...Values>
		void fill(Values&&... vals) {
            fillHelper(n, m, std::forward<Values>(vals)...);
		}
	};
}
