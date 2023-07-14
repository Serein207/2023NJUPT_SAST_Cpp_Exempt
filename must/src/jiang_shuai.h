#ifndef JIANG_SHUAI_H
#define JIANG_SHUAI_H

#include "piece.h"
#include "algorithms.h"
#include "board.h"

class Jiang_Shuai : public Piece
{
public:
    Jiang_Shuai(int x, int y, bool side) : Piece(x, y, side ? Piece::PieceType::RED_SHUAI : Piece::PieceType::BLACK_JIANG){}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const {
        auto jiang_shuai = Algorithms::findJiangShuai(side(), pieces);
        if (x == jiang_shuai.first && !Algorithms::countBetween(std::make_pair(x, y), jiang_shuai, pieces))
            return true;
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for (const auto& i : Board::JiuGongGe[side()]) {
            if (std::abs(i.first - x) + std::abs(i.second - y) != 1)
                continue;
            if (Algorithms::isFriend(i, side()))
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
    virtual bool isBasicMove(int x2, int y2) const {
        if (Algorithms::isFriend(std::make_pair(x2, y2), side()))
            return false;
        return (std::abs(x2 - x) + std::abs(y2 - y) == 1);
    }
};

#endif // JIANG_SHUAI_H
