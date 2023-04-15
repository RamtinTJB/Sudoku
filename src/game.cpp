#include <fstream>

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

void game::load_from_file(const std::string& file_path) {
    std::ifstream file(file_path, std::ios_base::in);
    if (file.is_open()) {
        file >> brd_;
    }
    file.close();
}

void game::increment_selected_cell(int count) {
    if (selected_cell_ + count <= 80) {
        selected_cell_ += count;
    }
}

void game::decrement_selected_cell(int count) {
    if (selected_cell_ - count >= 0) {
        selected_cell_ -= count;
    }
}

void game::update_ui(bool delay) {
    window_->clear(sf::Color::Black);

    ui_board_->draw_board(brd_);
    if (status_ == Status::INPUT) {
        ui_board_->highlight_cell(index_to_cell(selected_cell_));
    }

    window_->draw(sf::Sprite(ui_board_->get_texture()));

    window_->display();

    if (delay) time_delay(DELAY_TIME);
}

void game::time_delay(int time_ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

static bool is_number(const sf::Keyboard::Key& key) {
    if (key == sf::Keyboard::Num0 || key == sf::Keyboard::Num1 ||
            key == sf::Keyboard::Num2 || key == sf::Keyboard::Num3 ||
            key == sf::Keyboard::Num4 || key == sf::Keyboard::Num5 ||
            key == sf::Keyboard::Num6 || key == sf::Keyboard::Num7 ||
            key == sf::Keyboard::Num8 || key == sf::Keyboard::Num9) {
        return true;
    }

    return false;
}

static int get_num(const sf::Keyboard::Key& key) {
    switch (key) {
        case sf::Keyboard::Num0: return 0;
        case sf::Keyboard::Num1: return 1;
        case sf::Keyboard::Num2: return 2;
        case sf::Keyboard::Num3: return 3;
        case sf::Keyboard::Num4: return 4;
        case sf::Keyboard::Num5: return 5;
        case sf::Keyboard::Num6: return 6;
        case sf::Keyboard::Num7: return 7;
        case sf::Keyboard::Num8: return 8;
        case sf::Keyboard::Num9: return 9;
        default: return -1;
    }
}

void game::loop() {
    while (window_->isOpen()) {
        sf::Event event;
        while (window_->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up: decrement_selected_cell(9); break;
                    case sf::Keyboard::Down: increment_selected_cell(9); break;
                    case sf::Keyboard::Left: decrement_selected_cell(); break;
                    case sf::Keyboard::Right: increment_selected_cell(); break;
                    case sf::Keyboard::Backspace:
                        brd_.clear_cell(index_to_cell(selected_cell_));
                        break;
                    case sf::Keyboard::Enter:
                        status_ = Status::SOLVE;
                        solve(brd_, [this]() { this->update_ui(true); });
                        status_ = Status::DONE;
                        break;
                    default:
                        break;
                }

                if (is_number(event.key.code)) {
                    if (status_ == Status::INPUT) {
                        brd_.put_num(index_to_cell(selected_cell_), get_num(event.key.code));
                    }
                }
            }
            update_ui();
        }
    } 
}
