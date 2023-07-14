#include "mainui.h"

#include "cell.h"
#include "global.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

Global* MainUI::global = nullptr;

MainUI::MainUI() : QDialog(),
    layout(new QVBoxLayout), boardLayout(new QGridLayout),
    chu(new QLabel("楚河")), han(new QLabel("汉界"))
{
    auto count = 0;
    for (auto& i : h) {
        i = new QLabel("---");
        boardLayout->addWidget(i, count / 8 * 2, count % 8 * 2 + 1, Qt::AlignCenter);
        count++;
    }
    count = 0;
    for (auto& i : v1) {
        i = new QLabel("|");
        boardLayout->addWidget(i, count / 9 * 2 + 1, count % 9 * 2, Qt::AlignCenter);
        count++;
    }
    boardLayout->addWidget(chu, 9, 0, 1, 8, Qt::AlignCenter);
    boardLayout->addWidget(han, 9, 10, 1, 8, Qt::AlignCenter);
    for (auto& i : v2) {
        i = new QLabel("|");
        boardLayout->addWidget(i, count / 9 * 2 + 3, count % 9 * 2, Qt::AlignCenter);
        count++;
    }
    count = 0;
    for (auto& i : red_cells) {
        i = new Cell(count% 9 + 1, 10 - count / 9);
        boardLayout->addWidget(i, count / 9 * 2, count % 9 * 2);
        count++;
    }
    for (int i = 0; i < 90; i++)
        black_cells[i] = red_cells[89 - i];
    l[0] = new QLabel("\\");
    boardLayout->addWidget(l[0], 1, 7, Qt::AlignCenter);
    l[1] = new QLabel("/");
    boardLayout->addWidget(l[1], 1, 9, Qt::AlignCenter);
    l[2] = new QLabel("/");
    boardLayout->addWidget(l[2], 3, 7, Qt::AlignCenter);
    l[3] = new QLabel("\\");
    boardLayout->addWidget(l[3], 3, 9, Qt::AlignCenter);
    l[0] = new QLabel("\\");
    boardLayout->addWidget(l[0], 15, 7, Qt::AlignCenter);
    l[1] = new QLabel("/");
    boardLayout->addWidget(l[1], 15, 9, Qt::AlignCenter);
    l[6] = new QLabel("/");
    boardLayout->addWidget(l[6], 17, 7, Qt::AlignCenter);
    l[7] = new QLabel("\\");
    boardLayout->addWidget(l[7], 17, 9, Qt::AlignCenter);

    layout->addLayout(boardLayout);
    setLayout(layout);

    global = new Global(red_cells, black_cells);

    connect(&global->board[true], &Board::win, this, &MainUI::onWin);
    connect(&global->board[false], &Board::win, this, &MainUI::onWin);
}

const Board* MainUI::getBoard() {
    return global->getBoard();
}

void MainUI::click(int x, int y) {
    global->getBoard()->onClick(x, y);
}

void MainUI::move(const Pos& from, const Pos& to) {
    global->getBoard()->move(from, to);
}

void MainUI::reverse() {
    global->side = !global->side;
}

bool MainUI::isYourTurn(bool side) {
    return side == global->side;
}
