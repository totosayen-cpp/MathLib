#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <initializer_list>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>

#ifdef ENABLE_TYPE_SHORTCUTS
#define sui short unsigned int
#define si short int
#define ui unsigned int
#define lui long unsigned int
#define li long int
#define llui long long unsigned int
#define lli long long int
#define ld long double
#endif

inline void error(std::string const& func_name, std::string const& error_msg) {
	std::cerr << "Error in " << func_name << " : " << error_msg << std::endl;
	std::system("pause");
	std::exit(1);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& stream, std::vector<T> const& vector) {
	stream << '[';
	for (std::size_t i = 0; i < vector.size(); i++) {
		stream << vector[i];
		if (i != vector.size() - 1) {
			stream << ", ";
		}
	}
	return stream << "]";
}