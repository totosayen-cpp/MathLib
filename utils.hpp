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

	inline bool is_number(std::string const& number) {
		const std::string chars = "0123456789.";
		for (char c : number) {
			if (std::find(chars.begin(), chars.end(), c) == chars.end()) {
				return false;
			}
		}
		// find errors like 8..3 or 6.5.2
		bool has_comma = false;
		for (std::size_t i = 0; i < number.size(); i++) {
			if (number[i] == '.') {
				if (has_comma) {
					return false;
				}
				has_comma = true;
			}
		}
		return true;
	}
}