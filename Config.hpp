#pragma once
#include <cmath>

struct Config {

	static constexpr int width = 800;//1240;
	static constexpr int height = 300;//720;
	static constexpr double x_min = -1.55;//-2.0;
	static constexpr double x_max = 1.55;//1.0;
	static constexpr double y_min = -0.9;//-1.2;// -1.25;
	static constexpr double y_max = 0.9;//1.2;// 1.25;

	static constexpr double c_norm = 0.7885;//0.815;
	double theta = 0;// 2.9830;
	double c_r{ c_norm * std::cos(theta) };
	double c_i{ c_norm * std::sin(theta) };
	static constexpr int max_iter = 81;
	static constexpr double max_radius = 2.0;

	bool animate{ 1 };

};

