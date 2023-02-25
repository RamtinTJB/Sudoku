#ifndef SUDOKU_SOLVER_GAME_H_
#define SUDOKU_SOLVER_GAME_H_

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

#include "view_sfml.h"
#include "solver.h"
#include "utils.h"

enum class Status { INPUT, SOLVE, DONE };

constexpr int BOARD_MARGIN = 10;
constexpr int DELAY_TIME = 60;

class game {
    private:
        int width_, height_;

        sf::RenderWindow* window_ = nullptr;
        board brd_;     
        view_sfml* ui_board_ = nullptr;

        Status status_ = Status::INPUT;

        int selected_cell_ = 0;

        void increment_selected_cell(int count=1);
        void decrement_selected_cell(int count=1);
        
        void update_ui(bool delay=false);
        void time_delay(int time_ms) const;

    public:
        game(int width, int height);

        void loop();
};

#endif
