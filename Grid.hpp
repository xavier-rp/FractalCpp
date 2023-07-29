#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Grid {
public:
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	int width;
	int height;
	std::vector<int> x_indices;
	std::vector<int> y_indices;
	std::vector<double> x_vector;
	std::vector<double> y_vector;

	Grid(double x_min, double x_max, double y_min, double y_max, int width, int height) :
		x_min{ x_min },
		x_max{ x_max },
		y_min{ y_min },
		y_max{ y_max },
		width{ width },
		height{ height } {

		std::cout << "Building grid\n";

		double x_step{ (x_max - x_min) / width };
		double y_step{ (y_max - y_min) / height };

		for (int x_i{ 0 }; x_i < width; ++x_i) {
			x_indices.push_back(x_i);
			x_vector.push_back(x_min + x_i * x_step);
		}

		for (int y_i{ 0 }; y_i < height; ++y_i) {
			y_indices.push_back(y_i);
			y_vector.push_back(y_min + y_i * y_step);
		}

	}
};