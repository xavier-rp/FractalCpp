#include <iostream>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "IterativeComplexMap.hpp"
#include "Julia.hpp"
#include "Mandelbrot.hpp"
#include "Grid.hpp"
#include "Renderer.hpp"

const double pi = 3.14159265358979323846;

int main() {

	std::cout << "Running main\n";

	int width = 1240;
	int height = 720;
	double x_min = -2.0;
	double x_max = 1.0;
	double y_min = -1.2;// -1.25;
	double y_max = 1.2;// 1.25;

	double c_norm = 0.7885;//0.815;
	double theta = 2.0;// 2.9830;
	double c_r = c_norm * std::cos(theta);
	double c_i = c_norm * std::sin(theta);
	int max_iter = 81;
	double max_radius = 2.0;

	Grid grid{ x_min, x_max, y_min, y_max, width, height };

	Mandelbrot mandel{max_iter, max_radius};//{ -0.8, 0.156, max_iter, 2.0 };

	ColorMap color_map{ max_iter, "black_purple_white", false, true, 30 };

	Renderer renderer(mandel, grid, color_map);//(julia, grid, color_map);

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
					theta += (pi / 720);
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

int main2() {

	std::cout << "Running main\n";

    int width = 800;
    int height = 300;
	double x_min = -1.55;
	double x_max = 1.55;
	double y_min = -0.9;// -1.25;
	double y_max = 0.9;// 1.25;

	double c_norm = 0.7885;//0.815;
	double theta = 2.0;// 2.9830;
	double c_r = c_norm * std::cos(theta);
	double c_i = c_norm * std::sin(theta);
	int max_iter = 81;
	double max_radius = 2.0;

	Grid grid{ x_min, x_max, y_min, y_max, width, height };

	Julia julia{ c_r, c_i, max_iter, max_radius};//{ -0.8, 0.156, max_iter, 2.0 };
	IterativeComplexMap icm{ 2, c_r, c_i, max_iter, max_radius };

	std::vector<int> convergence_vector_j;

	auto start = std::chrono::high_resolution_clock::now();
	convergence_vector_j = julia.iterate_plane(grid.x_vector, grid.y_vector);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Computation time for Julia: " << duration.count() / 1000000.0 << " s" << std::endl;

	std::vector<int> convergence_vector_i;

	start = std::chrono::high_resolution_clock::now();
	convergence_vector_i = icm.iterate_plane(grid.x_vector, grid.y_vector);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Computation time for IterativeComplexMap: " << duration.count() / 1000000.0 << " s" << std::endl;

	for (int i{ 0 }; i < convergence_vector_i.size(); ++i) {
		if (convergence_vector_i[i] != convergence_vector_j[i]) {
			std::cout << "Inequality at index: " << i << " with " << convergence_vector_i[i] << " and " << convergence_vector_j[i] << "\n";
		}
	}
	std::cout << "Identical Convergence Vectors for IterativeComplexMap and Julia objects.\n";

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