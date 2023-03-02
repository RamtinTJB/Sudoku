#include <filesystem>

#include "view_sfml.h"

void view_sfml::setup() {
	square_width_ = width_ / ROW_COUNT;

	/* if (!font_.loadFromFile("/Users/ramtintajbakhsh/Desktop/projects/Sudoku/assets/Arial Unicode.ttf")) { */
    if (!font_.loadFromFile("arial.ttf")) {
		std::cout << "Error" << std::endl;
	}
}

sf::RectangleShape view_sfml::make_rect(int row, int col, const sf::Color& color, int outline_thickness,
        bool transparent) const {
	sf::RectangleShape rect(
			sf::Vector2f(square_width_, square_width_)
			);
	rect.setPosition(col*square_width_ + margin_, row*square_width_ + margin_);
	rect.setFillColor(BACKGROUND_COLOR);
    if (transparent) {
        rect.setFillColor(TRANSPARENT_COLOR);
    }
	rect.setOutlineThickness(outline_thickness);	
	rect.setOutlineColor(color);

	return rect;
}

sf::Text view_sfml::make_text(int row, int col, const std::string& str, const sf::Color& color) const {
	sf::Text text(str, font_);
	text.setCharacterSize(int(0.6*square_width_));

	sf::Vector2f center = {text.getGlobalBounds().width / 2.f,
		text.getGlobalBounds().height / 2.f};
	sf::Vector2f localBounds = {text.getLocalBounds().left, text.getLocalBounds().top};
	localBounds = center + localBounds;
	text.setOrigin(localBounds);

	text.setFillColor(color);
	text.setPosition(col*square_width_+margin_/2+square_width_/2
			, row*square_width_+margin_/2+square_width_/2);

	return text;
}

sf::Color view_sfml::get_cell_color(const CellStyle& style) {
	switch (style) {
		case CellStyle::REGULAR: return OUTLINE_COLOR;
		case CellStyle::GREEN: return sf::Color(25, 166, 102);
		case CellStyle::RED: return sf::Color(209, 56, 25);
	}
}

void view_sfml::draw_box_lines() {
	for (int i = 0; i < 4; ++i) {
		sf::RectangleShape line(sf::Vector2f(width_, BOX_LINE_WIDTH));
		line.setFillColor(OUTLINE_COLOR);

		//Horizontal Lines
		line.setPosition(margin_, 3*i*square_width_+margin_-BORDER_WIDTH);
		_render_texture.draw(line);

		//Vertical Lines
		line.rotate(90);
		line.setPosition(3*i*square_width_+margin_+BOX_LINE_WIDTH-BORDER_WIDTH, margin_);
		_render_texture.draw(line);
	}
}

void view_sfml::draw_board(const board& brd) {
	_render_texture.create(width_ + 2*margin_, height_ + 2*margin_);
	_render_texture.clear(BACKGROUND_COLOR);
	for (int row = 0; row < ROW_COUNT; ++row) {
		for (int col = 0; col < COL_COUNT; ++col) {
			cell c = {row, col};
			sf::Color color = get_cell_color(brd.get_style(c));
			_render_texture.draw(make_rect(row, col, OUTLINE_COLOR));
			if (brd.get_num(c) > 0) {
				_render_texture.draw(make_text(row, col,
							std::to_string(brd.get_num(c)), color));
			}
		}
	}
	draw_box_lines();
	_render_texture.display();
}

void view_sfml::highlight_cell(const cell& c) {
    auto rect = make_rect(c.row, c.col, sf::Color::Cyan, BORDER_WIDTH*2, true); 
    _render_texture.draw(rect);
    _render_texture.display();
}

void view_sfml::teardown() {

}
