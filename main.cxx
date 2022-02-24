#include <iostream>
#include <cassert>

#include "matrix.hpp"

static constexpr size_t fill_start = 0;
static constexpr size_t fill_count = 10;
static constexpr size_t print_start = 1;
static constexpr size_t print_count = 9;

int main() {
	Matrix<int, 0> m;

	for (auto i = fill_start; i < fill_count; i ++) {
		m[i][i] = i;
		m[i][fill_count - 1 - i] = fill_count - 1 - i;
	}
	for (auto i = print_start; i < print_count; i ++) {
		for (auto j = print_start; j < print_count; j ++) {
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "number of busy cells is " << m.size()  << std::endl;
	for (auto p : m) {
		auto [i, j, v] = p;
		std::cout << " i " << i << " j " << j << " val " << v << std::endl;
	}
	return 0;
}
