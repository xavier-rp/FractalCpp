#pragma once
#include <vector>

#include "SFML/Graphics.hpp"

class ColorMap {
public:
	int max_iter;
	std::vector<sf::Color> total_cmap_vec;
	std::vector<sf::Color> color_vec;

	ColorMap(int max_iter) :
		max_iter{ max_iter } {
		compute_jet();
		compute_colors();
		int i{ 0 };
		for (auto c : color_vec) {
			std::cout << i << ": " << static_cast<int>(c.r) << ", " << static_cast<int>(c.g) << ", " << static_cast<int>(c.b) << "\n";
			++i;
		}
	}

	void compute_jet() {
		for (int i{ 128 }; i < 256; ++i) {
			total_cmap_vec.push_back(sf::Color(0, 0, i, 255));
		}
		for (int i{ 0 }; i < 256; ++i) {
			total_cmap_vec.push_back(sf::Color(0, i, 255, 255));
		}
		for (int i{ 0 }; i < 256; ++i) {
			total_cmap_vec.push_back(sf::Color(i, 255, 255 - i, 255));
		}
		for (int i{ 255 }; i >= 0; --i) {
			total_cmap_vec.push_back(sf::Color(255, i, 0, 255));
		}
		for (int i{ 255 }; i >= 128; --i) {
			total_cmap_vec.push_back(sf::Color(i, 0, 0, 255));
		}
	}

	void compute_colors() {
		/*
		int steps_for_fetching{ static_cast<int>(total_cmap_vec.size()) / max_iter };
		for (int i{ 0 }; i < max_iter; ++i) {
			color_vec.push_back(total_cmap_vec[i * steps_for_fetching]);
		}*/

		int total_cmap_size = static_cast<int>(total_cmap_vec.size());
		int new_pos{ 0 };

		for (int i{ 0 }; i < max_iter; ++i) {

			color_vec.push_back(total_cmap_vec[new_pos]);
			new_pos = new_pos + (total_cmap_size - new_pos) / 30;
		}
		
		color_vec.push_back(sf::Color(0, 0, 0, 255));
	}
	


	void compute_colors2(){
		// https://math.stackexchange.com/questions/1635999/algorithm-to-convert-integer-to-3-variables-rgb
		double group_length{ 256 * 256 * 256 / static_cast<double>(max_iter) };
		int c;
		int r;
		int g;
		int b;

		for (int i{ 0 }; i < max_iter; ++i) {
			c = static_cast<int>(i * group_length);
			b = c % 256;
			g = ((c - b) / 256) % 256;
			r = ((c - b) / (256 * 256)) - g / 256;
			color_vec.push_back(sf::Color(r, g, b, 255));

		}

	}


};