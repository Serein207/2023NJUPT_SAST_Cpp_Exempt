#ifndef MA_H
#define MA_H

#include "algorithms.h"
#include "board.h"
#include "piece.h"

class Ma : public Piece {
   public:
    Ma(int x, int y, bool side)
        : Piece(x, y,
                side ? Piece::PieceType::RED_MA : Piece::PieceType::BLACK_MA) {}

   public:
    virtual bool isThreat(
        const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const {
        auto jiang_shuai = Algorithms::findJiangShuai(side(), pieces);
        return isBasicMove(jiang_shuai.first, jiang_shuai.second);
    }
    virtual const std::list<Pos> getPossibleMoves() const {
        std::list<Pos> result;
        const std::pair<int, int> dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (const auto& i : dir) {
            Pos MaJiao{x + i.first, y + i.second};
            if (Algorithms::isValid(MaJiao) && !Algorithms::exists(MaJiao)) {
                Pos des[2] = {{MaJiao.first + i.first ? i.first : 1,
                               MaJiao.second + i.second ? i.second : 1},
                              {MaJiao.first + i.first ? i.first : -1,
                               MaJiao.second + i.second ? i.second : -1}};
                if (Algorithms::isValid(des[0]) &&
                    !Algorithms::isFriend(des[0], side()))
                    result.emplace_back(des[0]);
                if (Algorithms::isValid(des[1]) &&
                    !Algorithms::isFriend(des[1], side()))
                    result.emplace_back(des[1]);
            }
        }
        for (auto i = result.begin(); i != result.end();) {
            auto board_info = MainUI::getBoard()->find();
            board_info.remove_if(
                [&](const std::pair<Pos, Piece::PieceType>& info) -> bool {
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
        // finish your code here
        return false;
        //
    }
};

#endif  // MA_H
