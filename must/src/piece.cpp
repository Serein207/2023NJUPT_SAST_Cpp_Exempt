#include "piece.h"
#include "board.h"
#include "algorithms.h"

using Type = Piece::PieceType;

const std::map<Type, wchar_t> Piece::dict = {
    { Type::RED_SHUAI, L'帥' },
    { Type::BLACK_JIANG, L'將' },
    { Type::RED_SHI, L'仕' },
    { Type::BLACK_SHI, L'士' },
    { Type::RED_XIANG, L'相' },
    { Type::BLACK_XIANG, L'象' },
    { Type::RED_MA, L'馬' },
    { Type::BLACK_MA, L'馬' },
    { Type::RED_JU, L'車' },
    { Type::BLACK_JU, L'車' },
    { Type::RED_PAO, L'炮' },
    { Type::BLACK_PAO, L'炮' },
    { Type::RED_BING, L'兵' },
    { Type::BLACK_ZU, L'卒' }
};

bool Piece::noThreat(int x2, int y2) const {
    auto board_info = MainUI::getBoard()->find();
    board_info.remove_if([&](const std::pair<Pos, Piece::PieceType>& info)->bool {
        return info.first == std::make_pair(x, y) || info.first == std::make_pair(x2, y2);
    });
    board_info.emplace_back(std::make_pair(x2, y2), type);
    return !Algorithms::isCheck(board_info, side());
}
