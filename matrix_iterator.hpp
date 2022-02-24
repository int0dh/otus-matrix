#pragma once

#include <tuple>

template <typename T>
struct MatrixIterator {

	using storage = std::map<size_t, std::map<size_t, T>>;
	using iterator = storage::iterator;
	using internal_iterator = std::map<size_t, T>::iterator;

	iterator end;

	iterator current_row;
	internal_iterator current_col;
	size_t i;

	MatrixIterator(storage& data) {

		current_row = data.begin();
		end = data.end();

		auto &[key, val] = *current_row;
		current_col = val.begin();
		i = key;
	}
	MatrixIterator(iterator e) : end(e) {};

	bool operator != (const MatrixIterator<T> &other) const {
		return !(*this == other);
	}

	bool operator == (const MatrixIterator<T> &other) const {
		return current_row == other.end;
	}

	MatrixIterator<T> & operator ++() {

		auto &[k, v] = *current_row;
		i = k;

		++ current_col;
		if (current_col == v.end()) {
			++ current_row;
			if (current_row != end) {
				auto &[_, w] = *current_row;
				current_col = w.begin();
				i = _;
			}
		}
		return *this;
	}

	std::tuple<size_t, size_t, T> operator *()  {

		auto [j, val] = *current_col;
		return {i, j, val};
	}
}; 


