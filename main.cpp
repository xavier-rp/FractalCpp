#include <iostream>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Julia.hpp"
#include "Grid.hpp"
#include "Renderer.hpp"

const double pi = 3.14159265358979323846;

int main() {

	std::cout << "Running main\n";

    int width = 640;
    int height = 360;
	double x_min = -1.55;
	double x_max = 1.55;
	double y_min = -1.25;
	double y_max = 1.25;

	double c_norm = 0.7885;//0.815;
	double theta = 0;
	double c_r = c_norm * std::cos(theta);
	double c_i = c_norm * std::sin(theta);
	int max_iter = 81;
	double max_radius = 2.0;

	Grid grid{ x_min, x_max, y_min, y_max, width, height };

	Julia julia{ c_r, c_i, max_iter, max_radius};//{ -0.8, 0.156, max_iter, 2.0 };

	ColorMap color_map{ max_iter };

	Renderer renderer(julia, grid, color_map);

	renderer.render_fractal();

	sf::RenderWindow window(sf::VideoMode(width, height), "My Window");

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
				// "close requested" event: we close the window
			case sf::Event::Closed:
				window.close();
				break;

				// key pressed
			case sf::Event::KeyReleased: 
				{
				if (event.key.scancode == sf::Keyboard::Scan::Right) {
					theta += (2 * pi / 360);
					julia.c_r = c_norm * std::cos(theta);
					julia.c_i = c_norm * std::sin(theta);
					renderer.render_fractal();
				}
				else {
					window.close();
				}
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}

		theta += (pi / 1440);
		julia.c_r = c_norm * std::cos(theta);
		julia.c_i = c_norm * std::sin(theta);
		renderer.render_fractal();

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(renderer.m_vertices);

		// end the current frame
		window.display();
	}

	return 0;
}