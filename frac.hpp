#pragma once

#include "include.hpp"
#include "utils.hpp"

enum class frac_mode { FRAC, NUMBER };

namespace math {

	template<typename NUMBER>
	class Frac {
		NUMBER numerator_ = 1.;
		NUMBER denominator_ = 1.;
		mutable frac_mode output_ = frac_mode::FRAC;

	public:

		Frac(NUMBER numerator, NUMBER denominator) {
			numerator_ = numerator;
			if (denominator == 0) {
				error("math::Frac::Frac", "denominator cannot be 0 !");
			}
			denominator_ = denominator;
		}

		Frac(NUMBER result) {
			numerator_ = result;
		}

		Frac() = default;

		inline NUMBER result() const {
			return numerator_ / denominator_;
		}

		inline NUMBER numerator() const {
			return numerator_;
		}

		inline NUMBER denominator() const {
			return denominator_;
		}

		inline void numerator(NUMBER new_numerator) {
			numerator_ = new_numerator;
		}

		inline void denominator(NUMBER new_denominator) {
			if (new_denominator == 0) {
				error("math::Frac::denominator", "denominator cannot be 0 !");
			}
			denominator_ = new_denominator;
		}

		inline frac_mode output_mode() const {
			return output_;
		}

		inline void output_mode(frac_mode mode) const {
			output_ = mode;
		}

		inline Frac operator+(Frac const& frac) const {
			return Frac(numerator_ * frac.denominator() + frac.numerator() * numerator_, denominator_ * frac.denominator());
		}

		inline Frac operator+(NUMBER n) const {
			return Frac(numerator_ + n * denominator_, denominator_);
		}

		inline void operator++() {		// ++Frac
			numerator_ += denominator_;
		}

		inline void operator++(int) { // Frac++
			++(*this);
		}

	};

	typedef math::Frac<int> IFrac;
	typedef math::Frac<float> FFrac;
	typedef math::Frac<long long int> LIFrac;
	typedef math::Frac<long double> LFFrac;
}

inline math::IFrac operator"" _ifrac(const char* expr, std::size_t length) {
	// ex : Frac f = "3/2"_frac; <=> Frac f = Frac(3, 2)
	const std::size_t pos = std::string(expr).find('/');
	try {
		return math::IFrac(std::stoi(std::string(expr).substr(0, pos)), std::stoi(std::string(expr).substr(pos + 1)));
	}
	catch (std::invalid_argument& cast_error) {
		error("operator\"\" _ifrac", "invalid frac expression : " + std::string(expr));
	}
}

inline math::FFrac operator"" _ffrac(const char* expr, std::size_t length) {
	// ex : Frac f = "3/2"_frac; <=> Frac f = Frac(3, 2)
	const std::size_t pos = std::string(expr).find('/');
	try {
		return math::FFrac(std::stof(std::string(expr).substr(0, pos)), std::stof(std::string(expr).substr(pos + 1)));
	}
	catch (std::invalid_argument& cast_error) {
		error("operator\"\" _ifrac", "invalid frac expression : " + std::string(expr));
	}
}

inline math::LIFrac operator"" _lifrac(const char* expr, std::size_t length) {
	// ex : Frac f = "3/2"_frac; <=> Frac f = Frac(3, 2)
	const std::size_t pos = std::string(expr).find('/');
	try {
		return math::LIFrac(std::stol(std::string(expr).substr(0, pos)), std::stol(std::string(expr).substr(pos + 1)));
	}
	catch (std::invalid_argument& cast_error) {
		error("operator\"\" _ifrac", "invalid frac expression : " + std::string(expr));
	}
}

inline math::LFFrac operator"" _lffrac(const char* expr, std::size_t length) {
	// ex : Frac f = "3/2"_frac; <=> Frac f = Frac(3, 2)
	const std::size_t pos = std::string(expr).find('/');
	try {
		return math::LFFrac(std::stold(std::string(expr).substr(0, pos)), std::stold(std::string(expr).substr(pos + 1)));
	}
	catch (std::invalid_argument& cast_error) {
		error("operator\"\" _ifrac", "invalid frac expression : " + std::string(expr));
	}
}

inline math::IFrac operator"" _ifrac(long double result) {
	return math::IFrac(result);
}

inline math::FFrac operator"" _ffrac(long double result) {
	return math::FFrac(result);
}

inline math::LIFrac operator"" _lifrac(long double result) {
	return math::LIFrac(result);
}

inline math::LFFrac operator"" _lffrac(long double result) {
	return math::LFFrac(result);
}

template<typename NUMBER>
inline std::ostream& operator<<(std::ostream& stream, math::Frac<NUMBER> const& frac) {
	if (frac.output_mode() == frac_mode::FRAC) {
		stream << frac.numerator() << std::endl;
		const std::size_t size = std::max(math::reduce_number(std::to_string(frac.numerator())).size(), math::reduce_number(std::to_string((frac.denominator()))).size());
		// fraction bar's length
		for (std::size_t i = 0; i < size; i++) {
			stream << '-';
		}
		return stream << std::endl << frac.denominator();
	}
	return stream << (frac.numerator() / frac.denominator());
}

#ifndef DISABLE_FRAC_TYPES
// to be used in main

constexpr frac_mode FRAC = frac_mode::FRAC;
constexpr frac_mode NUMBER = frac_mode::NUMBER;
#endif