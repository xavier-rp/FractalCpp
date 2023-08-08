#pragma once
#include <iostream>
#include <vector>
#include <cmath>

#include "Fractal.hpp"

class Burningship : public Fractal {
public:

	Burningship(int max_iter, double max_radius) :
		Fractal(0.0, 0.0, max_iter, max_radius) {
		std::cout << "Building Burningship object\n";
		std::cout << "For the classical Burningship, make y_min > y_max in Config.hpp and zoom on the lower left!\n";
	}

	virtual int iterate_z(double z_r, double z_i) override {
		double burningship_c_r{ z_r };
		double burningship_c_i{ z_i };
		z_r = 0.0;
		z_i = 0.0;
		int i{ 0 };
		while ((i < max_iter) && (z_r * z_r + z_i * z_i <= max_radius_squared)) {

			double z_rn = z_r; //Real part of z at step n is used to compute z_i of step n+1. Hence I need a copy of z_r before modifying it on the next line
			z_r = (z_r * z_r) - (z_i * z_i) + burningship_c_r;
			z_i = (2 * std::abs(z_rn) * std::abs(z_i)) + burningship_c_i;
			++i;
		}

		return i;
	}

	virtual std::vector<int> iterate_plane(const std::vector<double> z_real, const std::vector<double> z_imag) override {
		std::vector<int> convergence_vector;

		for (auto z_i : z_imag) {
			for (auto z_r : z_real) {
				convergence_vector.push_back(iterate_z(z_r, z_i));
			}
		}

		return convergence_vector;
	}

	virtual ~Burningship() = default;
};
