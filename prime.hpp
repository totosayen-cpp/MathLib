#pragma once

#include "include.hpp"

namespace math {
	inline bool is_prime(long long int number) {
		if (number < 0) {
			return math::is_prime(std::abs(number));
		}
		if (number == 0 || number == 1) {
			return false;
		}
		if (number == 2) {
			return true;
		}
		if (number % 2 == 0) {
			return false;
		}
		const long long int limit = static_cast<long long int>(std::sqrt(number) + 1);
		for (std::size_t i = 3; i < limit; i += 2) {
			if (number % i == 0) {
				return false;
			}
		}
		return true;
	}

	inline long long int first_divisor(long long int number) {
		if (number < 0) {
			return 0 - math::first_divisor(std::abs(number));
		}
		if (math::is_prime(number)) {
			return number;
		}
		const long long int limit = static_cast<long long int>(std::sqrt(number) + 1);
		for (std::size_t i = 3; i < limit; i += 2) {
			if (number % i == 0) {
				return i;
			}
		}
	}

	inline std::vector<long long int> prime_factors(long long int number) {
		if (number < 0) {
			std::vector<long long int> result = math::prime_factors(std::abs(number));
			for (long long int& val : result) {
				val -= val * 2; // 4 => -4
			}
			return result;
		}
		std::vector<long long int> factors;
		factors.reserve(static_cast<std::size_t>(number)); // in the case of lot of divisors
		while (number % 2 == 0) {
			factors.push_back(2ll);
			number /= 2;
		}
		const std::size_t limit = std::sqrt(number) + 1;
		for (std::size_t i = 3; i < limit; i += 2) {
			while (number % i == 0) {
				factors.push_back(i);
				number /= i;
			}
		}
		if (number > 2) {
			factors.push_back(number);
		}
		return factors;
	}
}