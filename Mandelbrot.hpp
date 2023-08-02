#pragma once
#include <iostream>
#include <vector>

#include "Fractal.hpp"

class Mandelbrot : public Fractal {
public:

	Mandelbrot(int max_iter, double max_radius) :
		Fractal(0.0, 0.0, max_iter, max_radius) {
		std::cout << "Building Mandelbrot object\n";
	}

	virtual int iterate_z(double z_r, double z_i) override {
		double mandelbrot_c_r{ z_r };
		double mandelbrot_c_i{ z_i };
		z_r = 0.0;
		z_i = 0.0;
		int i{ 0 };
		while ((i < max_iter) && (z_r * z_r + z_i * z_i <= max_radius_squared)) {

			double z_rn = z_r; //Real part of z at step n is used to compute z_i of step n+1. Hence I need a copy of z_r before modifying it on the next line
			z_r = (z_r * z_r) - (z_i * z_i) + mandelbrot_c_r;
			z_i = (2 * z_rn * z_i) + mandelbrot_c_i;
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

	virtual ~Mandelbrot() = default;
};
