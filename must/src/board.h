#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

#include <QObject>
#include <functional>
#include <mutex>
#include <utility>

/* BOARD Layout
 * 对手：
 * 10   +-+-+-+-+-+-+-+-+
 *      | | | |\|/| | | |
 * 9    +-+-+-+-+-+-+-+-+
 *      | | | |/|\| | | |
 * 8    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 7    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 6    +-+-+-+-+-+-+-+-+
 *        楚河      汉界
 * 5    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 4    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 3    +-+-+-+-+-+-+-+-+
 *      | | | |\|/| | | |
 * 2    +-+-+-+-+-+-+-+-+
 *      | | | |/|\| | | |
 * 1    +-+-+-+-+-+-+-+-+
 *      1 2 3 4 5 6 7 8 9
 * 我方：
*/
class Board : public QObject
{
    Q_OBJECT

    using Constructor = std::function<const std::shared_ptr<Piece>(int, int, bool)>;    //工厂函数类型
private:
    bool checked[2] = { false, false };
    const bool SIDE;            //哪一方？
    std::mutex lock;
public:
    inline bool isChecked(bool side) const {
        return checked[side];
    }
    inline bool isYourTurn() const;
    inline bool side() const {
        return SIDE;
    }

    const static std::vector<Pos> JiuGongGe[2];
private:
    static std::map<Pos, std::shared_ptr<Piece>> pieces;
    static std::map<Pos, Cell*> cells;

    void setPieces(const std::map<Piece::PieceType, Constructor> &);
    void judgeStatus(); //走棋后对局势评估（输赢和当前是否处于将军状态）
public:
    const std::list<std::pair<Pos, Piece::PieceType>> find(int x = -1, int y = -1, int side = -1) const;
signals:
    void win(bool side);
public:
    void onClick(int x, int y);
    void move(const Pos from, const Pos to);

    Board(bool side, Cell** cells);

    friend class Algorithms;
};
#endif // BOARD_H
