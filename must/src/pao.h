#ifndef PAO_H
#define PAO_H

#include "piece.h"
#include "algorithms.h"
#include "board.h"

class Pao : public Piece
{
public:
    Pao(int x, int y, bool side) : Piece(x, y, side ? Piece::PieceType::RED_PAO : Piece::PieceType::BLACK_PAO) {}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const {
        auto jiang_shuai = Algorithms::findJiangShuai(side(), pieces);
        if (Algorithms::countBetween(std::make_pair(x, y), jiang_shuai, pieces) == 1)
            return true;
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        auto v = MainUI::getBoard()->find(x);
        auto h = MainUI::getBoard()->find(-1, y);
        int xmin = 1, xmax = 9, ymin = 1, ymax = 10;
        int xmin2 = 1, xmax2 = 9, ymin2 = 1, ymax2 = 10;
        for (const auto& i : h)
            if (i.first.first < x) {
                if (i.first.first > xmin) {
                    xmin2 = xmin;
                    xmin = i.first.first;
                }
                else if (i.first.first > xmin2)
                    xmin2 = i.first.first;
            }
            else if (i.first.first > x) {
                if (i.first.first < xmax) {
                    xmax2 = xmax;
                    xmax = i.first.first;
                }
                else if (i.first.first < xmax2)
                    xmax2 = i.first.first;
            }
        for (const auto& i : v)
            if (i.first.second < y) {
                if (i.first.second > ymin) {
                    ymin2 = ymin;
                    ymin = i.first.second;
                }
                else if (i.first.second > ymin2)
                    ymin2 = i.first.second;
            }
            else if (i.first.second > y) {
                if (i.first.second < ymax) {
                    ymax2 = ymax;
                    ymax = i.first.second;
                }
                else if (i.first.second < ymax2)
                    ymax2 = i.first.second;
            }
        for (int i = xmin + 1; i < x; i++)
            result.emplace_back(i, y);
        for (int i = x + 1; i < xmax; i++)
            result.emplace_back(i, y);
        for (int i = ymin + 1; i < y; i++)
            result.emplace_back(x, i);
        for (int i = y + 1; i < ymax; i++)
            result.emplace_back(x, i);
        if (Algorithms::exists(std::make_pair(xmin2, y)) && !Algorithms::isFriend(std::make_pair(xmin2, y), side()))
            result.emplace_back(xmin2, y);
        if (Algorithms::exists(std::make_pair(xmax2, y)) && !Algorithms::isFriend(std::make_pair(xmax2, y), side()))
            result.emplace_back(xmax2, y);
        if (Algorithms::exists(std::make_pair(x, ymin2)) && !Algorithms::isFriend(std::make_pair(x, ymin2), side()))
            result.emplace_back(x, ymin2);
        if (Algorithms::exists(std::make_pair(x, ymax2)) && !Algorithms::isFriend(std::make_pair(x, ymax2), side()))
            result.emplace_back(x, ymax2);
        for (auto i = result.begin(); i != result.end();)
            if (noThreat(i->first, i->second))
                i++;
            else
                result.erase(i++);
        return result;
    }
    virtual bool isBasicMove(int x2, int y2) const{
        int result = Algorithms::countBetween(std::make_pair(x, y), std::make_pair(x2, y2));
        if (result == 0)
            return !Algorithms::exists(std::make_pair(x2, y2));
        if (result == 1)
            return Algorithms::exists(std::make_pair(x2, y2)) && !Algorithms::isFriend(std::make_pair(x2, y2), side());
        return false;
    }
};

#endif // PAO_H
