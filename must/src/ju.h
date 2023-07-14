#ifndef JU_H
#define JU_H

#include "piece.h"
#include "algorithms.h"
#include "board.h"

class Ju : public Piece
{
public:
    Ju(int x, int y, bool side) : Piece(x, y, side ? Piece::PieceType::RED_JU : Piece::PieceType::BLACK_JU){}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const {
        auto jiang_shuai = Algorithms::findJiangShuai(side(), pieces);
        if (!Algorithms::countBetween(std::make_pair(x, y), jiang_shuai, pieces))
            return true;
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        auto v = MainUI::getBoard()->find(x);
        auto h = MainUI::getBoard()->find(-1, y);
        int xmin = 1, xmax = 9, ymin = 1, ymax = 10;
        for (const auto& i : v)
            if (i.first.first < x && i.first.first > xmin)
                xmin = i.first.first;
            else if (i.first.first > x && i.first.first < xmax)
                xmax = i.first.first;
        for (const auto& i : h)
            if (i.first.second < y && i.first.second > ymin)
                ymin = i.first.second;
            else if (i.first.second > x && i.first.second < ymax)
                ymax = i.first.second;
        if (Algorithms::isFriend(std::make_pair(xmin, y), side()))
            xmin++;
        for (int i = xmin; i < x; i++)
            result.emplace_back(i, y);
        if (Algorithms::isFriend(std::make_pair(xmax, y), side()))
            xmax--;
        for (int i = x + 1; i <= xmax; i++)
            result.emplace_back(i, y);
        if (Algorithms::isFriend(std::make_pair(ymin, y), side()))
            ymin++;
        for (int i = ymin; i < y; i++)
            result.emplace_back(x, i);
        if (Algorithms::isFriend(std::make_pair(ymax, y), side()))
            ymax--;
        for (int i = y + 1; i <= ymax; i++)
            result.emplace_back(x, i);
        for (auto i = result.begin(); i != result.end();) {
            auto board_info = MainUI::getBoard()->find();
            board_info.remove_if([&](const std::pair<Pos, Piece::PieceType>& info)->bool {
                return info.first == std::make_pair(x, y);
            });
            board_info.emplace_back(*i, type);
            if (Algorithms::isCheck(board_info, side()))
                result.erase(i++);
            else
                i++;
        }
        return result;
    }
    virtual bool isBasicMove(int x2, int y2) const {
        if (Algorithms::isFriend(std::make_pair(x2, y2), side()))
            return false;
        return !Algorithms::countBetween(std::make_pair(x, y), std::make_pair(x2, y2), MainUI::getBoard()->find(x));
    }
};

#endif // JU_H
