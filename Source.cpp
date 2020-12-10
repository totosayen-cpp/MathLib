// write here the #define

#include "math.hpp"

int main() {
	math::FFrac f = math::FFrac(10);
	std::cin >> f;
	std::cout << f << std::endl;

	math::IMatrix2D matrix = math::IMatrix2D();
	matrix.output_mode(GRID_SPACE);
	matrix[0] = { 10, 2, 3 };
	matrix[1] = { 0, 1, 2, 85, 520 };
	matrix.swap_columns(3, 4);
	std::cout << matrix << std::endl;
	std::system("pause");
	return 0;
}
