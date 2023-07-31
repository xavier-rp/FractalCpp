#pragma once
#include <iostream>
#include <vector>


class Fractal {
public:
	double c_r;
	double c_i;
	int max_iter;
	double max_radius_squared;

	Fractal(double c_r, double c_i, int max_iter, double max_radius) :
		c_r{ c_r },
		c_i{ c_i },
		max_iter{ max_iter },
		max_radius_squared{ max_radius * max_radius } {}

	virtual int iterate_z(double z_r, double z_i) = 0;

	virtual std::vector<int> iterate_plane(const std::vector<double> z_real, const std::vector<double> z_imag) = 0;

	virtual ~Fractal() = default;
};
