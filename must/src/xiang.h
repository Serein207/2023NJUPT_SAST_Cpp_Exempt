#ifndef XIANG_H
#define XIANG_H

#include "piece.h"
#include "algorithms.h"
#include "board.h"

class Xiang : public Piece
{
public:
    Xiang(int x, int y, bool side) : Piece(x, y, side ? Piece::PieceType::RED_XIANG : Piece::PieceType::BLACK_XIANG) {}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        const std::pair<int, int> dir[4] = {
            {1, 1}, {-1, 1}, {-1, 1}, {-1, -1}
        };
        for (const auto& i : dir) {
            Pos XiangJiao {x + i.first, y + i.second};
            if (side() ? XiangJiao.second >= 5 : XiangJiao.second <= 6)
                continue;
            if (Algorithms::isValid(XiangJiao) && !Algorithms::exists(XiangJiao)) {
                Pos des{x + i.first * 2, y + i.second * 2};
                if (!Algorithms::isFriend(des, side()))
                    result.emplace_back(des);
            }
        }
        for (auto i = result.begin(); i != result.end();)
            if (noThreat(i->first, i->second))
                i++;
            else
                result.erase(i++);
        return result;
    }
    virtual bool isBasicMove(int x2, int y2) const{
        if (Algorithms::isFriend(std::make_pair(x2, y2), side()))
            return false;
        if (std::abs(x2 - x) != 2 || std::abs(y2 - y) != 2)
            return false;
        if (side() ? y2 >= 5 : y2 <= 6)
            return false;
        Pos XiangJiao {(x + x2) >> 1, (y + y2) >> 1};
        return !Algorithms::exists(XiangJiao);
    }
};


#endif // XIANG_H
