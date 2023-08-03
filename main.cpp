#include <iostream>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "IterativeComplexMap.hpp"
#include "Julia.hpp"
#include "Mandelbrot.hpp"
#include "Grid.hpp"
#include "Renderer.hpp"
#include "WindowUtils.hpp"
#include "Config.hpp"

const double pi = 3.14159265358979323846;

int main() {

	std::cout << "\n";

	Config config{};

	Grid grid{ config.x_min, config.x_max, config.y_min, config.y_max, config.width, config.height };

	//Mandelbrot frac{ config.max_iter, config.max_radius };

	Julia frac{ config.c_r, config.c_i, config.max_iter, config.max_radius };

	ColorMap color_map{ config.max_iter, "black_purple_white", false, true, 30 };

	Renderer renderer(frac, grid, color_map);//(julia, grid, color_map);

	renderer.render_fractal();

	sf::RenderWindow window(sf::VideoMode(config.width, config.height), "LimoilouMadness.exe");

	sf::RectangleShape zoomBorder(sf::Vector2f(config.width / 8, config.height / 8));
	zoomBorder.setFillColor(sf::Color(0, 0, 0, 0));
	zoomBorder.setOutlineColor(sf::Color(255, 255, 255, 128));
	zoomBorder.setOutlineThickness(1.0f);
	zoomBorder.setOrigin(sf::Vector2f(zoomBorder.getSize().x / 2, zoomBorder.getSize().y / 2));


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
					config.theta += (pi / 720);
				}
				else {
					window.close();
				}
			} 
				break;

			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					
					zoomx8(grid, event);
					renderer.render_fractal();

				}
			}
				break;

			// we don't process other types of events
			default:
				break;
			}
		}

		zoomBorder.setPosition(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(renderer.m_vertices);
		window.draw(zoomBorder);

		// end the current frame
		window.display();
		if (config.animate) {
			config.theta += (pi / 1440);
			//std::cout << "Phase of c: " << config.theta << std::endl;
			frac.c_r = config.c_norm * std::cos(config.theta);
			frac.c_i = config.c_norm * std::sin(config.theta);
			renderer.render_fractal();
		}

	}

	return 0;
}

int main2() {

	std::cout << "Running main\n";

    int width = 800;
    int height = 300;
	double x_min = -1.55;
	double x_max = 1.55;
	double y_min = -0.9;// -1.25;
	double y_max = 0.9;// 1.25;

	double c_norm = 0.7885;//0.815;
	double theta = 0.0;// 2.9830;
	double c_r = c_norm * std::cos(theta);
	double c_i = c_norm * std::sin(theta);
	int max_iter = 81;
	double max_radius = 2.0;

	Grid grid{ x_min, x_max, y_min, y_max, width, height };

	Julia julia{ c_r, c_i, max_iter, max_radius};//{ -0.8, 0.156, max_iter, 2.0 };

	ColorMap color_map{ max_iter, "black_white", false, false, 30};

	Renderer renderer(julia, grid, color_map);//(julia, grid, color_map);

	renderer.render_fractal();

	sf::RenderWindow window(sf::VideoMode(width, height), "LimoilouMadness.exe");
	

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
					theta += ( pi / 720);
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
		std::cout << "Phase of c: " << theta << std::endl;
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