#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "board.h"
#include "mainui.h"

//工具类
class Algorithms {
public:
    //判断僵局(无子可走)
    static bool isStalemate(bool side) {
        auto result = MainUI::getBoard()->find(-1, -1, side);
        for (const auto& [pos, type] : result) {
            auto piece = MainUI::getBoard()->pieces.at(pos);
            if (!piece->getPossibleMoves().empty())
                return false;
        }
        return true;
    }

    //Piece::noThreat和Algorithms::isCheck的推荐辅助函数，输出side一方是否被将军
    static inline bool isCheck(const std::list<std::pair<Pos, Piece::PieceType>>& pieces, bool side) {
        for(auto i : pieces){
            if(getSide(i.second) == !side){
                std::shared_ptr<Piece> temp = createTempPiece(i.first,i.second);
                if(temp->isThreat(pieces))
                    return true;
            }
        }
        return false;
    }

    static inline bool isCheck(bool side) {
        auto list = MainUI::getBoard()->find();
        return isCheck(list,side);
    }

    static inline bool isFriend(const Pos& pos, bool side) {
        return MainUI::getBoard()->pieces.count(pos) ? MainUI::getBoard()->pieces.at(pos)->side() == side : false;
    }

    static inline bool exists(const Pos& pos) {
        return MainUI::getBoard()->pieces.count(pos);
    }

    static inline bool isValid(const Pos& pos) {
        return pos.first >= 1 && pos.first <= 9 && pos.second >= 1 && pos.first <= 10;
    }
    //H abbr.Horizontal
    static inline unsigned countHBetween(int y, int xmin, int xmax, const std::list<std::pair<Pos, Piece::PieceType>>& pieces) {
        unsigned count = 0;
        for (const auto& i : pieces)
            if (i.first.second == y && i.first.first > xmin && i.first.first < xmax)
                count++;
        return count;
    }
    //V abbr.vertical
    static inline unsigned countVBetween(int x, int ymin, int ymax, const std::list<std::pair<Pos, Piece::PieceType>>& pieces) {
        unsigned count = 0;
        for (const auto& i : pieces)
            if (i.first.first == x && i.first.second > ymin && i.first.second < ymax)
                count++;
        return count;
    }

    static inline unsigned countBetween(const Pos& a, const Pos& b, const std::list<std::pair<Pos, Piece::PieceType>>& pieces = MainUI::getBoard()->find()) {
        if (a.first == b.first)
            return countVBetween(a.first, std::min(a.second, b.second), std::max(a.second, b.second), pieces);
        else if (a.second == b.second)
            return countHBetween(a.second, std::min(a.first, b.first), std::max(a.first, b.first), pieces);
        return -1;
    }

    static std::shared_ptr<Piece> createTempPiece(const Pos& pos, Piece::PieceType type);

    inline static Pos findJiangShuai(bool side, const std::list<std::pair<Pos, Piece::PieceType>>& pieces) {
        auto jiang_shuai = std::find_if(pieces.begin(), pieces.end(), [=](const std::pair<Pos, Piece::PieceType>& piece)->bool {
            return piece.second == (!side ? Piece::PieceType::RED_SHUAI : Piece::PieceType::BLACK_JIANG);
        });
        return jiang_shuai->first;
    }
};

#endif // ALGORITHMS_H
