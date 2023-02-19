#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

#include "solver.h"
#include "view_sfml.h"

sf::RenderWindow window(sf::VideoMode(1020, 1020, 32), "Sudoku Solver");
board brd;
view_sfml ui_board(1000, 1000);

void update_ui(bool delay=false) {
	window.clear(sf::Color::Black);
	ui_board.draw_board(brd);
	window.draw(sf::Sprite(ui_board.get_texture()));
	window.display();	

	if (delay) {
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
	}
}

int main(int argc, const char** argv) {
	ui_board.set_margin(10);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				solve(brd, []() {update_ui(true);});
			}
			update_ui();
		}
	}

	return 0;
}
