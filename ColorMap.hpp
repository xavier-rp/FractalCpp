#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>

#include "SFML/Graphics.hpp"

class ColorMap {
public:
	int max_iter;
	std::string cmap_str;
	bool reverse;
	bool cyclical;
	uint32_t nonlinear_dividor; // if 0 or 1, we select colors linearly, otherwise nonlinearly in the total_cmap. 10 and higher give good results.
	std::vector<sf::Color> total_cmap_vec;
	std::vector<sf::Color> color_vec;
	std::map<std::string, std::function<void()>> cmap_function{{"jet", [this]() { compute_jet(); }},
															   { "black_purple", [this]() { compute_black_purple(); } },
															   { "black_purple_white", [this]() { compute_black_purple_white(); } },
															   { "black_white", [this]() { compute_black_and_white(); } }};
	// Weird Syntax, but it has to be binded to the instance see : https://stackoverflow.com/questions/70804439/how-to-use-stdfunctionvoid-as-a-typename-in-initializing-a-map

	ColorMap(int max_iter, std::string cmap_str, bool reverse = false, bool cyclical = false, uint32_t nonlinear_dividor = 30) :
		max_iter{ max_iter },
		cmap_str{ cmap_str },
		reverse{ reverse },
		cyclical{ cyclical },
		nonlinear_dividor{ nonlinear_dividor } {

		cmap_function[cmap_str]();

		if (cyclical) {
			make_cyclical();
		}
		if (reverse) {
			reverse_cmap();
		}

		compute_colors();
		
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

	void compute_black_purple() {
		for (int i{ 0 }; i < 256; ++i) {
			total_cmap_vec.push_back(sf::Color(i, 0, i, 255));
		}
	}

	void compute_black_purple_white() {
		for (int i{ 0 }; i < 256; ++i) {
			total_cmap_vec.push_back(sf::Color(i, 0, i, 255));
		}
		for (int i{ 0 }; i < 256; ++i) {
			total_cmap_vec.push_back(sf::Color(255, i, 255, 255));
		}
	}

	void compute_black_and_white() {
		for (int i{ 0 }; i < 256; ++i) {
			total_cmap_vec.push_back(sf::Color(255, 255, 255, i));
		}
	}

	void make_cyclical() {
		std::vector<sf::Color> cpy = total_cmap_vec;
		std::reverse(cpy.begin(), cpy.end());
		total_cmap_vec.insert(total_cmap_vec.end(), cpy.begin(), cpy.end());
	}

	void reverse_cmap() {
		std::reverse(total_cmap_vec.begin(), total_cmap_vec.end());
		color_vec.clear();
		compute_colors();
	}

	void compute_colors() {

		int total_cmap_size = static_cast<int>(total_cmap_vec.size());
		double ratio{ static_cast<double>(total_cmap_size) / (max_iter + 1) }; // We want max iter + 1 groups because max_iter is reachable when iterating the complex numbers
		int new_pos{ 0 };

		for (int i{ 0 }; i < max_iter + 1; ++i) {
			if (nonlinear_dividor < 2){
				std::cout << total_cmap_size << "         " << i << "        " << static_cast<int>(i * ratio) << "\n";
				color_vec.push_back(total_cmap_vec[static_cast<int>(i * ratio)]);
			}
			else {
				color_vec.push_back(total_cmap_vec[new_pos]);
				new_pos = new_pos + (total_cmap_size - new_pos) / nonlinear_dividor; // This operation makes the selection within the total cmap non linear (30 is arbitrary)
																	  // In the case of jet, we thus have more yellow - red colors for high convergence.
			}
		}														  
		
		//TODO Reimplement option?
		//color_vec.push_back(sf::Color(0, 0, 0, 255)); // Add black at the end
	}

};