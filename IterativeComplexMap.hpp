#pragma once
#include <iostream>
#include <vector>


class IterativeComplexMap {
public:
	int exponent;
	double c_r;
	double c_i;
	int max_iter;
	double max_radius_squared;

	IterativeComplexMap(int exponent, double c_r, double c_i, int max_iter, double max_radius) :
		exponent{ exponent },
		c_r{ c_r },
		c_i{ c_i },
		max_iter{ max_iter },
		max_radius_squared{ max_radius * max_radius } {
		std::cout << "Building IterativeComplexMap object\n";
	}

	double cmplx_mult_r(double z1_r, double z1_i, double z2_r, double z2_i) {
		return z1_r * z2_r - z1_i * z2_i;
	}

	double cmplx_mult_i(double z1_r, double z1_i, double z2_r, double z2_i) {
		return z1_r * z2_i + z1_i * z2_r;
	}

	std::vector<double> cmplx_pow(double z1_r, double z1_i, uint32_t expo) {
		if (expo > 1) {
			uint32_t i{ 1 };
			double newz_r{ z1_r };
			double newz_i{ z1_i };
			while (i < expo) {
				double tmp{ z1_r };
				newz_r = cmplx_mult_r(newz_r, newz_i, z1_r, z1_i);
				newz_i = cmplx_mult_i(tmp, newz_i, z1_r, z1_i);
				++i;
			}
			return std::vector<double>{newz_r, newz_i};
		}
		else if (expo == 1) {
			return std::vector<double>{z1_r, z1_i};

		}
		else {
			return std::vector<double>{1.0, 1.0};
		}

	}

	int iterate_z(double z_r, double z_i) {

		int i{ 0 };
		std::vector<double> power_of_z;
		while ((i < max_iter) && (z_r * z_r + z_i * z_i <= max_radius_squared)) {

			power_of_z = cmplx_pow(z_r, z_i, exponent);

			z_r = power_of_z[0] + c_r;
			z_i = power_of_z[1] + c_i;
			
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