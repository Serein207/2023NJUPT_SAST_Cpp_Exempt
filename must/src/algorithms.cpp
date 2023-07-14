#include "algorithms.h"

#include "bing_zu.h"
#include "pao.h"
#include "ju.h"
#include "ma.h"
#include "shi.h"
#include "xiang.h"
#include "jiang_shuai.h"

std::shared_ptr<Piece> Algorithms::createTempPiece(const Pos& pos, Piece::PieceType type) {
    auto side = Piece::getSide(type);
    switch(removeSide(type)) {
    case Piece::PieceType::BING_ZU:{
        return std::make_shared<Bing_Zu>(pos.first, pos.second, side);
    }break;
    case Piece::PieceType::JIANG_SHUAI:{
        return std::make_shared<Jiang_Shuai>(pos.first, pos.second, side);
    }break;
    case Piece::PieceType::PAO:{
        return std::make_shared<Pao>(pos.first, pos.second, side);
    }break;
    case Piece::PieceType::JU:{
        return std::make_shared<Ju>(pos.first, pos.second, side);
    }break;
    case Piece::PieceType::SHI:{
        return std::make_shared<Shi>(pos.first, pos.second, side);
    }break;
    case Piece::PieceType::XIANG:{
        return std::make_shared<Xiang>(pos.first, pos.second, side);
    }break;
    case Piece::PieceType::MA:{
        return std::make_shared<Ma>(pos.first, pos.second, side);
    }break;
    }
};
