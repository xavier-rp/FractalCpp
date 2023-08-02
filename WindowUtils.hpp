#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Grid.hpp"

void zoomx8(Grid& grid, sf::Event mouseclick) {
	double x_range{ grid.x_max - grid.x_min };
	double y_range{ grid.y_max - grid.y_min };


	double new_x_min{ grid.x_vector[mouseclick.mouseButton.x] - (1.0 / 2.0) * (1.0 / 8.0) * x_range };
	double new_x_max{ grid.x_vector[mouseclick.mouseButton.x] + (1.0 / 2.0) * (1.0 / 8.0) * x_range };
	double new_y_min{ grid.y_vector[(grid.height - 1) - mouseclick.mouseButton.y] - (1.0 / 2.0) * (1.0 / 8.0) * y_range };
	double new_y_max{ grid.y_vector[(grid.height - 1) - mouseclick.mouseButton.y] + (1.0 / 2.0) * (1.0 / 8.0) * y_range };

	std::cout << x_range << " " << y_range << " " << new_y_min << " " << new_y_max;

	grid.update_grid(new_x_min, new_x_max, new_y_min, new_y_max);

}