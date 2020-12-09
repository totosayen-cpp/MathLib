#include "include.hpp"

namespace math {

	inline std::string reduce_number(std::string number) { //  number will be copied and modified
		while (true) {
			if (number[number.size() - 1] == '.') {
				return number.substr(0, number.size() - 1);
			}
			if (number[number.size() - 1] != '0') {
				return number;
			}
			else {
				if (std::find(number.begin(), number.end(), '.') == number.end()) { // if there's not any comma, the number is good 
					return number;
				}
				else { // finished with a zero without any comma
					number = number.substr(0, number.size() - 1); // zero deleted
				}
			}
		}
	}

	template<typename NUMBER>
	inline std::string reduce_number(NUMBER number) {
		return math::reduce_number(std::to_string(number));
	}

	template<typename NUMBER>
	inline void reduce_number(std::vector<NUMBER>& numbers) {
		for (std::size_t i = 0; i < numbers.size(); i++) {
			numbers[i] = static_cast<NUMBER>(std::stold(math::reduce_number<NUMBER>(numbers[i])));
		}
	}
}

template<typename T>
std::string display_vector(std::vector<T> const& vector, std::string const& separator = " ") {
	if (vector.size() == 0) {
		return "";
	}
	std::vector<T> copy = vector;
	math::reduce_number(copy);
	std::ostringstream result;
	for (std::size_t i = 0; i < copy.size(); i++) {
		result << copy[i];
		if (i != copy.size() - 1) {
			result << separator;
		}
	}
	return result.str();
}