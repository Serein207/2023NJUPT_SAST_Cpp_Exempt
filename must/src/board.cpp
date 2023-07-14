#include "board.h"
#include "algorithms.h"
#include "jiang_shuai.h"
#include "pao.h"
#include "shi.h"
#include "xiang.h"
#include "ju.h"
#include "bing_zu.h"
#include "ma.h"

using Type = Piece::PieceType;

const std::vector<Pos> Board::JiuGongGe[2] = {
    { {4, 10}, {5, 10}, {6, 10}, {4, 9}, {5, 9}, {6, 9}, {4, 8}, {5, 8}, {6, 8} },
    { {4, 1}, {5, 1}, {6, 1}, {4, 2}, {5, 2}, {6, 2}, {4, 3}, {5, 3}, {6, 3} }
};
std::map<Pos, std::shared_ptr<Piece>> Board::pieces;
std::map<Pos, Cell*> Board::cells;

void Board::judgeStatus() {
    checked[!side()] = Algorithms::isCheck(!side());
    checked[side()] = Algorithms::isCheck(side());
    if (Algorithms::isStalemate(!side()))
        return emit win(side());
    if (Algorithms::isStalemate(side()))
        return emit win(!side());
}

Board::Board(bool side, Cell** cells) : SIDE(side) {
    for (int i = 0; i < 10 * 9; i++) {
        auto& cell = cells[i];
        this->cells.emplace(std::piecewise_construct, std::tuple(cell->x, cell->y), std::tuple(cell));
    }
    static std::map<Type, Constructor> factory = {
        //请将nullptr替换为'new ClassName(x, y, side)'，请正确设置派生类构造函数参数
        { Type::JIANG_SHUAI, [](int x, int y, bool side)->const std::shared_ptr<Piece> { return std::make_shared<Jiang_Shuai>(x, y, side); } },
        { Type::SHI, [](int x, int y, bool side)->const std::shared_ptr<Piece> { return std::make_shared<Shi>(x, y, side); } },
        { Type::XIANG, [](int x, int y, bool side)->const std::shared_ptr<Piece> { return std::make_shared<Xiang>(x, y, side); } },
        { Type::MA, [](int x, int y, bool side)->const std::shared_ptr<Piece> { return std::make_shared<Ma>(x, y, side); } },
        { Type::JU, [](int x, int y, bool side)->const std::shared_ptr<Piece> { return std::make_shared<Ju>(x, y, side); } },
        { Type::PAO, [](int x, int y, bool side)->const std::shared_ptr<Piece> { return std::make_shared<Pao>(x, y, side); } },
        { Type::BING_ZU, [](int x, int y, bool side)->const std::shared_ptr<Piece> { return std::make_shared<Bing_Zu>(x, y, side); } }
    };
    if (SIDE) {
        setPieces(factory);
        for (const auto& [pos, piece] : pieces)
            this->cells[pos]->change(piece.get());
    }
}

void Board::setPieces(const std::map<Type, Constructor> & factory) {
    static std::list<std::pair<Pos, Type>> piece_list = {
        { { 1, 1 }, Type::RED_JU },
        { { 2, 1 }, Type::RED_MA },
        { { 3, 1 }, Type::RED_XIANG },
        { { 4, 1 }, Type::RED_SHI },
        { { 5, 1 }, Type::RED_SHUAI },
        { { 6, 1 }, Type::RED_SHI },
        { { 7, 1 }, Type::RED_XIANG },
        { { 8, 1 }, Type::RED_MA },
        { { 9, 1 }, Type::RED_JU },
        { { 2, 3 }, Type::RED_PAO },
        { { 8, 3 }, Type::RED_PAO },
        { { 1, 4 }, Type::RED_BING },
        { { 3, 4 }, Type::RED_BING },
        { { 5, 4 }, Type::RED_BING },
        { { 7, 4 }, Type::RED_BING },
        { { 9, 4 }, Type::RED_BING },
        { { 1, 10 }, Type::BLACK_JU },
        { { 2, 10 }, Type::BLACK_MA },
        { { 3, 10 }, Type::BLACK_XIANG },
        { { 4, 10 }, Type::BLACK_SHI },
        { { 5, 10 }, Type::BLACK_JIANG },
        { { 6, 10 }, Type::BLACK_SHI },
        { { 7, 10 }, Type::BLACK_XIANG },
        { { 8, 10 }, Type::BLACK_MA },
        { { 9, 10 }, Type::BLACK_JU },
        { { 2, 8 }, Type::BLACK_PAO },
        { { 8, 8 }, Type::BLACK_PAO },
        { { 1, 7 }, Type::BLACK_ZU },
        { { 3, 7 }, Type::BLACK_ZU },
        { { 5, 7 }, Type::BLACK_ZU },
        { { 7, 7 }, Type::BLACK_ZU },
        { { 9, 7 }, Type::BLACK_ZU }
    };

    for (const auto& [pos, type] : piece_list)
        pieces.emplace(pos, factory.at(removeSide(type))(pos.first, pos.second, side() == getSide(type)));
}

void Board::move(const Pos from, const Pos to) {
    const auto& piece = pieces.at(from);
    piece->move(to.first, to.second);
    auto& cell_from = cells.at(from);
    cell_from->change(nullptr);
    auto& cell_to = cells.at(to);
    cell_to->change(piece.get());
    if (pieces.count(to)) {
        pieces.erase(to);
    }
    pieces.emplace(to, pieces.at(from));
    pieces.erase(from);
    judgeStatus();
}

bool Board::isYourTurn() const {
    return MainUI::isYourTurn(side());
}

void Board::onClick(int x, int y) {
    std::lock_guard guard(lock);
    static Piece const* selected = nullptr;
    if (!isYourTurn()){
        return;
    }
    const auto pos = std::make_pair(x,y);
    if (pieces.count(pos)) {
        const auto& piece = pieces.at(pos);
        if (piece->side() == side()) {
            selected = piece.get();
            cells.at(pos)->select();
            return;
        }
    }
    if (!selected)
        return;
    if (selected->isValidMove(x, y)) {
        move(selected->pos(), pos);
        cells.at(pos)->fineMove();
        selected = nullptr;
        MainUI::reverse();
    } else
        cells.at(pos)->wrongMove();
}

const std::list<std::pair<Pos, Piece::PieceType>> Board::find(int x, int y, int side) const {
    std::list<std::pair<Pos, Piece::PieceType>> result;
    for (const auto& [pos, piece] : pieces)
        if ((x == -1 || x == pos.first) && (y == -1 || y == pos.second) && (side == -1 || side == piece->side()))
            result.push_back(std::make_pair(pos, piece->type));
    return result;
}
