#pragma once

#include <map>
#include "matrix_iterator.hpp"

template <typename T, T default_value>
class Matrix {

	std::map<size_t, std::map<size_t, T>> data;

	class MatrixEntry {
		friend class Matrix;

		Matrix &parent;
		size_t row, col;

	public:
		operator T() {
			if (parent.data.contains(row)) {
				if (parent.data[row].contains(col)) {
					return parent.data[row][col];
				}
			}
			return default_value;
		}
		T operator = (T other) {

			if (other == default_value) {
				return default_value;
			}
			parent.data[row][col] = other;
			return parent.data[row][col];
		}
		MatrixEntry(Matrix &p, size_t r, size_t c) : parent(p), row(r), col(c) {}
	};

	class MatrixRow {
		friend class Matrix;

		Matrix& parent;
		size_t row;

	public:
		MatrixEntry operator [] (size_t col) {
			return MatrixEntry(parent, row, col);
		}
		MatrixRow(Matrix &p, size_t r) : parent(p), row(r) {}
	};

public:
	MatrixIterator<T> begin() {
		return MatrixIterator<T>(data);
	}
	MatrixIterator<T> end() {
		return MatrixIterator<T>(data.end());
	}

	size_t size() const {
		size_t result = 0;

		for (const auto &[_, v] : data) {
			result += v.size();
		}
		return result;
	}
	MatrixRow operator[] (size_t row) {
		return MatrixRow(*this, row);
	}
};
