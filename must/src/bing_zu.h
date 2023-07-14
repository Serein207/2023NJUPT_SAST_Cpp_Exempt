#ifndef BING_ZU_H
#define BING_ZU_H

#include "piece.h"
#include "algorithms.h"
#include "board.h"

#include <algorithm>

class Bing_Zu : public Piece
{
    static inline bool cross_river(int y, bool side = MainUI::getBoard()->side()) {
        return side == MainUI::getBoard()->side() ? y >= 6 : y <= 5;
    }
    inline bool cross_river() const {
        return cross_river(y, side());
    }

public:
    Bing_Zu(int x, int y, bool side) : Piece(x, y, side ? Piece::PieceType::RED_BING : Piece::PieceType::BLACK_ZU) {}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const {
        auto jiang_shuai = Algorithms::findJiangShuai(side(), pieces);
        if (side()) {
            if (x == jiang_shuai.first && y + 1 == jiang_shuai.second)
                return true;
            if (y == jiang_shuai.second && std::abs(x - jiang_shuai.first) == 1)
                return true;
        }
        else {
            if (x == jiang_shuai.first && y - 1 == jiang_shuai.second)
                return true;
            if (y == jiang_shuai.second && std::abs(x - jiang_shuai.first) == 1)
                return true;
        }
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const {
        std::list<Pos> result;
        if (side() ? y != 10 : y != 1)
            result.emplace_back(x, side() ? y + 1 : y - 1);
        if (cross_river()) {
            if (y != 1)
                result.emplace_back(x - 1, y);
            if (y != 9)
                result.emplace_back(x + 1, y);
        }
        for (auto i = result.begin(); i != result.end();) {
            auto board_info = MainUI::getBoard()->find();
            board_info.remove_if([&](const std::pair<Pos, Piece::PieceType>& info)->bool {
                return info.first == std::make_pair(x, y);
            });
            board_info.emplace_back(*i, type);
            if (Algorithms::isFriend(*i, side()) || Algorithms::isCheck(board_info, side()))
                result.erase(i++);
            else
                i++;
        }
        return result;
    }
    virtual bool isBasicMove(int x2, int y2) const {
        if (Algorithms::isFriend(std::make_pair(x2, y2), side()))
            return false;
        if (side()) {
            if (x == x2 && y + 1 == y2)
                return true;
            if (cross_river() && y == y2 && std::abs(x - x2) == 1)
                return true;
        }
        else {
            if (x == x2 && y - 1 == y2)
                return true;
            if (cross_river() && y == y2 && std::abs(x - x2) == 1)
                return true;
        }
        return false;
    }
};

#endif // BING_ZU_H
