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