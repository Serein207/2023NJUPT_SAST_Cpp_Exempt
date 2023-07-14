#ifndef SHI_H
#define SHI_H

#include "piece.h"
#include "algorithms.h"
#include "board.h"

class Shi : public Piece
{
public:
    Shi(int x, int y, bool side) : Piece(x, y, side ? Piece::PieceType::RED_SHI : Piece::PieceType::BLACK_SHI) {}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for (const auto& i : Board::JiuGongGe[side()]) {
            if (!(std::abs(i.first - x) == 1 && std::abs(i.second - y) == 1))
                continue;
            auto board_info = MainUI::getBoard()->find();
            board_info.remove_if([&](const std::pair<Pos, Piece::PieceType>& info)->bool {
                return info.first == std::make_pair(x, y);
            });
            board_info.emplace_back(i, type);
            if (!Algorithms::isCheck(board_info, side()))
                result.push_back(i);
        }
        return result;
    }
    virtual bool isBasicMove(int x2, int y2) const{
        if (Algorithms::isFriend(std::make_pair(x2, y2), side()))
            return false;
        for (const auto& i : Board::JiuGongGe[side()])
            if (i.first == x2 && i.second == y2)
                return std::abs(x2 - x) == 1 && std::abs(y2 - y) == 1;
        return false;
    }
};

#endif // SHI_H
