#ifndef MAINUI_H
#define MAINUI_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>

using Pos = std::pair<int, int>;

class Cell;
class Board;
class Global;

class MainUI : public QDialog
{
    Q_OBJECT

    QVBoxLayout* layout;
    QGridLayout* boardLayout;
    QLabel *h[8 * 10], *v1[9 * 4], *v2[9 * 4], *l[8], *chu, *han;
    Cell* red_cells[9 * 10], *black_cells[9 * 10];
    QLineEdit* text;
    static Global* global;

public:
    MainUI();

    static const Board* getBoard();
    static void click(int x, int y);
    static void move(const Pos& from, const Pos& to);

    static void reverse();
    static bool isYourTurn(bool side);
public slots:
    void onWin(bool side) {
        QMessageBox* box = new QMessageBox();
        box->setText(side ? "红方胜！" : "黑方胜！");
        box->show();
    }
};

#endif // MAINUI_H
