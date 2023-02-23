#include "game.h"

game::game(int width, int height) {
    width_  = width;
    height_ = height;

    int window_width  = width_ + 2*BOARD_MARGIN;
    int window_height = height_ + 2*BOARD_MARGIN;

    window_ = new sf::RenderWindow(sf::VideoMode(window_width, window_height, 32), "Sudoku Solver");
    ui_board_ = new view_sfml(width_, height_);

    ui_board_->set_margin(BOARD_MARGIN);
}

void game::update_ui(bool delay) {
    window_->clear(sf::Color::Black);

    ui_board_->draw_board(brd_);
    window_->draw(sf::Sprite(ui_board_->get_texture()));

    window_->display();

    if (delay) time_delay(DELAY_TIME);
}

void game::time_delay(int time_ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

void game::loop() {
    while (window_->isOpen()) {
        sf::Event event;
        while (window_->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                solve(brd_, [this]() { this->update_ui(true); });
            }
            update_ui();
        }
    } 
}
