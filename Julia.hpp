#pragma once
#include <iostream>
#include <vector>


class Julia {
public:
	double c_r;
	double c_i;
	int max_iter;
	double max_radius_squared;

	Julia(double c_r, double c_i, int max_iter, double max_radius):
		c_r{ c_r },
		c_i{ c_i },
		max_iter{ max_iter },
		max_radius_squared{ max_radius * max_radius } {
		std::cout << "Building Julia object\n";
	}

	int iterate_z(double z_r, double z_i) {
		int i{ 0 };
		while ( (i < max_iter ) && (z_r*z_r + z_i * z_i <= max_radius_squared)){

			double z_rn = z_r; //Real part of z at step n is used to compute z_i of step n+1. Hence I need a copy of z_r before modifying it on the next line
			z_r = (z_r * z_r) - (z_i * z_i) + c_r;
			z_i = (2 * z_rn * z_i) + c_i;
			++i;
		}

		return i;
	}

	std::vector<int> iterate_plane(const std::vector<double> z_real, const std::vector<double> z_imag) {
		std::vector<int> convergence_vector;

		for (auto z_r : z_real) {
			for (auto z_i : z_imag) {
				convergence_vector.push_back(iterate_z(z_r, z_i));
			}
		}

		return convergence_vector;
	}


};