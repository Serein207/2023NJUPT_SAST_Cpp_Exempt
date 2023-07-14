#ifndef GLOBAL_H
#define GLOBAL_H

#include "board.h"

class Global {
    bool side = true;
    Board board[2];
    Global(Cell** red, Cell** black) : board{{false, black}, {true, red}} {}

    inline Board* getBoard() {
        return &board[side];
    }

    friend class MainUI;
};

#endif // GLOBAL_H
