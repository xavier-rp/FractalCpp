#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

#include "SFML/Graphics.hpp"

#include "Fractal.hpp"
#include "Grid.hpp"
#include "ColorMap.hpp"

class Renderer {
public:
	Fractal &fractal;
	Grid &grid;
	ColorMap& color_map;
	sf::VertexArray m_vertices;

	Renderer(Fractal &fractal, Grid &grid, ColorMap &color_map) :
		fractal{ fractal },
		grid{ grid },
		color_map{ color_map } {
		std::cout << "Building Renderer\n";
		m_vertices = sf::VertexArray(sf::Points, grid.width * grid.height);
	}

	void render_fractal() {
		std::vector<int> convergence_vector;
		//auto start = std::chrono::high_resolution_clock::now();
		convergence_vector = fractal.iterate_plane(grid.x_vector, grid.y_vector);
		//auto stop = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		//std::cout << "Computation time : " << duration.count() / 1000000.0 << " s" << std::endl;

		int pos{ 0 };

		for (int y{ grid.height - 1 }; y >= 0; --y) {
			for (int x{ 0 }; x < grid.width; ++x) {
				m_vertices[pos].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
				m_vertices[pos].color = color_map.color_vec[convergence_vector[pos]];
				++pos;
			}
		}
	}
	
};