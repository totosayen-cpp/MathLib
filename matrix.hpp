#pragma once

#include "include.hpp"

enum class matrix_mode { GRID, SPACE, GRID_SPACE };

// GRID :
/*
|4  |5 |8|
|11 |88|
|400|2 |
*/


namespace math {

	template<typename NUMBER>
	class Matrix2D {
		std::vector<std::vector<NUMBER>> vals_ = std::vector<std::vector<NUMBER>>();
		mutable matrix_mode output_ = matrix_mode::SPACE;

		void clean() {
			/*
			transforms vals_ into a square and fills new boxes by NUMBER()
			ex:
			2 2
			3 3 3
			4
			5 5 5 5

			=>

			2 2 0 0
			3 3 3 0
			4 0 0 0
			5 5 5 5
			*/
			std::size_t final_length = 0u; // max size of a line
			for (std::vector<NUMBER> const& line : vals_) {
				final_length = std::max(final_length, line.size());
			}
			for (std::vector<NUMBER>& line : vals_) {
				if (line.size() < final_length) {
					line.reserve(final_length - line.size());
					for (std::size_t i = line.size(); i < final_length; i++) {
						line.push_back(NUMBER());
					}
				}
			}
		}

	public:
		Matrix2D(std::size_t lines = 2u, std::size_t columns = 2u) {
			vals_.reserve(lines);
			for (std::size_t line = 0; line < lines; line++) {
				vals_.push_back(std::vector<NUMBER>());
			}
			for (std::vector<NUMBER>& line : vals_) {
				line.reserve(columns);
				for (NUMBER& val : line) {
					val = NUMBER();
				}
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		Matrix2D(std::size_t lines, std::vector<NUMBER> const& line) {
			vals_.reserve(lines);
			for (std::size_t i = 0; i < lines; i++) {
				vals_.push_back(line);
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		Matrix2D(std::vector<std::vector<NUMBER>> const& vals) {
			vals_ = vals;
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void fill_column(std::size_t column, NUMBER value) { // DON'T throws error if column out of range => because columns's lengthes may be unequal
			for (std::vector<NUMBER>& line : vals_) {
				if (column < line.size()) {
					line[column] = value;
				}
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void fill_line(std::size_t line, NUMBER value) { // THROWS error if line out of range
			if (line >= vals_.size()) {
				error("math::Matrix2D::fill_line", "line index out of bounds !");
			}
			std::fill(vals_[line].begin(), vals_[line].end(), value);
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void fill(NUMBER value) {
			for (std::size_t line = 0; line < vals_.size(); line++) {
				fill_line(line, value);
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		inline std::size_t lines() const {
			return vals_.size();
		}

		inline std::size_t min_columns() const {
			// returns the size of the smallest line
			std::size_t result = 0;
			for (std::vector<NUMBER> const& line : vals_) {
				result = std::min(result, line.size());
			}
			return result;
		}

		inline std::size_t max_columns() const {
			// returns the size of the biggest line
			std::size_t result = 0;
			for (std::vector<NUMBER> const& line : vals_) {
				result = std::max(result, line.size());
			}
			return result;
		}

		std::vector<NUMBER>& operator[](std::size_t index) {
			if (index >= vals_.size()) {
				error("math::Matrix2D::operator[]", "index (" + std::to_string(index) + ") >= vals_.size()");
			}
			return vals_[index];
		}

		const std::vector<NUMBER> operator[](std::size_t index) const {
			if (index >= vals_.size()) {
				error("math::Matrix2D::operator[]", "index (" + std::to_string(index) + ") >= vals_.size()");
			}
			return vals_[index];
		}

		void push_line(std::vector<NUMBER> const& line) {
			vals_.push_back(line);
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void push_column(std::vector<NUMBER> const& column) { 
			/* if column's size is > number of lines, we stop when we are t the end of the lines
			1 1 2
			5 9 6
			7 8 9
			=> push_column({0, 1, 2, 3, 4})
			1 1 2 0
			5 9 6 1
			7 8 9 3
			end
			*/
			for (std::size_t i = 0; i < vals_.size(); i++) {
				if (i >= column.size()) { // column's size < number of lines
					return 0;
				}
				vals_[i].push_back(column[i]);
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void insert_line(std::size_t index, std::vector<NUMBER> const& line) { // if index >= vals_.size => insert at the end
			if (index >= vals_.size()) {
				vals_.push_back(line);
				return;
			}
			vals_.insert(index, line);
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void insert_column(std::size_t index, std::vector<NUMBER> const& column) { // if index >= line.size => insert at the end; if column's size > number of line, stop when at the end of the lines
			for (std::size_t i = 0; i < vals_.size(); i++) {
				if (i >= column.size()) {
					return;
				}
				if (index >= vals_[i].size()) {
					vals_[i].push_back(column[i]);
					continue;
				}
				vals_[i].insert(index, column[i]);
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void reset() {
			vals_ = std::vector<std::vector<NUMBER>>();
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void remove_value(NUMBER value) {
			std::vector<NUMBER> new_line;
			for (std::size_t i = 0; i < vals_.size(); i++) {
				for (NUMBER val : vals_[i]) {
					new_line.reserve(vals_[i].size());
					if (val != value) {
						new_line.push_back(val);
					}
				}
				vals_[i] = new_line;
				new_line = std::vector<NUMBER>();
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void replace_value(NUMBER old_value, NUMBER new_value) {
			std::vector<NUMBER> new_line;
			for (std::size_t i = 0; i < vals_.size(); i++) {
				for (NUMBER val : vals_[i]) {
					new_line.reserve(vals_[i].size());
					if (val != old_value) {
						new_line.push_back(val);
					}
					else {
						new_line.push_back(new_value);
					}
				}
				vals_[i] = new_line;
				new_line = std::vector<NUMBER>();
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void swap_lines(std::size_t first_line, std::size_t second_line) {
			if (first_line >= vals_.size()) {
				error("math::Matrix2D::swap_lines", "first_line index is out of range");
			}
			if (second_line >= vals_.size()) {
				error("math::Matrix2D::swap_lines", "second_line index is out of range");
			}
			std::iter_swap(vals_.begin() + first_line, vals_.begin() + second_line);
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void swap_columns(std::size_t first_column, std::size_t second_column) {
			/*
			7 8 9
			4 5
			7 8 9 6 5
			1 2 3
			=> swap_columns(1, 3)
			7 8 9
			4 5
			7 6 9 8 5
			1 2 3
			=> swaps ONLY if the line is able to do it
			*/
			for (std::vector<NUMBER>& line : vals_) {
				if (std::max(first_column, second_column) < line.size()) { // can swap
					std::iter_swap(line.begin() + first_column, line.begin() + second_column);
				}
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		NUMBER line_sum(std::size_t index) const {
			if (index >+ vals_.size()) {
				error("math::Matrix2D::line_sum", "index is out of range !");
			}
			return std::accumulate(vals_[index]);
		}

		NUMBER column_sum(std::size_t column) const { // if line's size < column's index => does nothing
			NUMBER result = NUMBER();
			for (std::vector<NUMBER> const& line : vals_) {
				if (column < line.size()) {
					result += line[column];
				}
			}
			return result;
		}

		NUMBER sum() const {
			NUMBER result = NUMBER();
			for (std::vector<NUMBER> const& line : vals_) {
				result += std::accumulate(line.begin(), line.end());
			}
			return result;
		}

		void remove_line(std::size_t index) {
			if (index >= vals_.size()) {
				error("math::Matrix2D::remove_line", "index of the line to remove is out of range !");
			}
			vals_.erase(vals_.begin(), vals_.begin() + index);
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		void remove_column(std::size_t index) { // if column is out of range in certain lines, DOESN'T throw error => does nothing
			for (std::vector<NUMBER>& line : vals_) {
				if (index < line.size()) {
					line.erase(line.begin() + index); // erases the (index)th value
				}
			}
			for (std::vector<NUMBER>& line : vals_) {
				math::reduce_number(line);
			}
			clean();
		}

		std::vector<std::vector<NUMBER>> vals() const {
			return vals_;
		}

		void output_mode(matrix_mode mode) const {
			output_ = mode;
		}

		matrix_mode output_mode() const {
			return output_;
		}

		std::size_t max_val_size_line(std::size_t line) const {
			// returns the max number of digits of a number in a line
			if (line >= vals_.size()) {
				error("math::Matrix2D::max_val_size_line", "line index out of range");
			}
			std::size_t result = 0u;
			for (NUMBER val : vals_[line]) {
				result = std::max(result, math::reduce_number(std::string(val)).size());
			}
			return result;
		}

		std::size_t max_val_size_column(std::size_t column) const { // used by std::ostream& operator<<
			// returns the max number of digits of a number in a column => doesn't throw error, if out of range => does nothing
			std::size_t result = 0u;
			for (std::vector<NUMBER> const& line : vals_) {
				if (column < line.size()) {
					result = std::max(result, std::to_string(line[column]).size());
				}
			}
			return result;
		}

	};

	typedef math::Matrix2D<int> IMatrix2D;
	typedef math::Matrix2D<float> FMatrix2D;
	typedef math::Matrix2D<long long int> LIMatrix2D;
	typedef math::Matrix2D<long double> LFMatrix2D;
}



template<typename NUMBER>
std::ostream& operator<<(std::ostream& stream, math::Matrix2D<NUMBER> const& matrix) {
	std::vector<NUMBER> copy;
	std::string separator;
	switch (matrix.output_mode()) {
	case matrix_mode::GRID:
		separator = "|";
		break;
	case matrix_mode::SPACE:
		separator = " ";
		break;
	default:
		separator = " | ";
		break;
	}
	const std::vector<std::vector<NUMBER>> vals_ = matrix.vals();
	for (std::size_t line = 0; line < vals_.size(); line++) {
		copy = vals_[line];
		math::reduce_number<NUMBER>(copy);
		for (std::size_t i = 0; i < copy.size(); i++) {
			stream << copy[i];
			for (std::size_t j = math::reduce_number(copy[i]).size(); j < matrix.max_val_size_column(i); j++) {
				stream << " ";
			}
			if (i != copy.size() - 1) {
				stream << separator;
			}
		}
		if (line < (vals_.size() - 1)) {
			stream << std::endl;
		}
	}
	return stream;	
}

#ifndef DISABLE_MATRIX_TYPES
constexpr matrix_mode SPACE = matrix_mode::SPACE;
constexpr matrix_mode GRID = matrix_mode::GRID;
constexpr matrix_mode GRID_SPACE = matrix_mode::GRID_SPACE;
#endif