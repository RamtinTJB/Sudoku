#ifndef SUDOKU_VIEW_SFML_H_
#define SUDOKU_VIEW_SFML_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "board.h"

constexpr int ROW_COUNT = 9;
constexpr int COL_COUNT = 9;

const sf::Color BACKGROUND_COLOR = sf::Color::White;
const sf::Color OUTLINE_COLOR = sf::Color::Black;

const float BORDER_WIDTH = 3.f;
const float BOX_LINE_WIDTH = 10.f;

class view_sfml {
	public:
		view_sfml(int w, int h) : width_{w}, height_{h} {
			setup();
		}

		~view_sfml() {
			teardown();
		}

		void draw_board(const board& brd);

		void teardown();

		const sf::Texture get_texture() const { return _render_texture.getTexture(); }

		int get_margin() const { return margin_; }
		void set_margin(int margin) { margin_ = margin; }

	private:
		int square_width_;
		int width_;
		int height_;
		int margin_;
		
		sf::RenderTexture _render_texture;
		sf::Font font_;

		void setup();

		sf::RectangleShape make_rect(int row, int col, const sf::Color&) const;
		sf::Text make_text(int row, int col, const std::string& str, const sf::Color&) const;

		sf::Color get_cell_color(const CellStyle&);

		void draw_box_lines();
};

#endif
