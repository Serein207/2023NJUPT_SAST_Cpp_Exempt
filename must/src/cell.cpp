#include "cell.h"

#include "mainui.h"

Cell* Cell::chosen = nullptr;

Cell::Cell(int x, int y) : QPushButton("+"), x(x), y(y)
{
    setFlat(true);
    setFixedSize(20, 20);
    fade();
    setAutoFillBackground(true);
    connect(this, &Cell::clicked, this, &Cell::onClick);
}

void Cell::onClick() {
    MainUI::click(x, y);
}
