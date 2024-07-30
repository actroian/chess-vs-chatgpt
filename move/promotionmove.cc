#include "promotionmove.h"
using namespace std;

PromotionMove::PromotionMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const char promotion_piece, char captured_piece)
    : Move{start, end, captured_piece}, promotion_piece{promotion_piece} {}

bool PromotionMove::move(unique_ptr<Board>& board, Player* movingplayer, Player* opponent, bool isPromotionMove) const {
    string promotion;
    if(isPromotionMove && !movingplayer->isABot()) {
        promotion = getInput("pawn promotion", validPromotions);
    }
    else{
        promotion = "Q";
    }
    promotion = movingplayer->isP1() ? toupper(promotion[0]) : tolower(promotion[0]);
    board->placePiece(end.first, end.second, board->createPiece(promotion, end));
    board->removePiece(start.first, start.second);
    if(isPromotionMove)cout << "Pawn promoted to " << promotion << endl;
    return true;
}

void PromotionMove::undo(Board& board) {
    board.removePiece(end.first, end.second);
    board.placePiece(start.first, start.second, make_unique<Pawn>(start.first, start.second, board, promotion_piece != tolower(promotion_piece)));
    if(captured_piece != '\0'){
        string piece = string{captured_piece};
        board.placePiece(end.first, end.second, board.createPiece(piece, end));
    }
}

bool PromotionMove::operator==(const Move& other) const {
    const PromotionMove* o = dynamic_cast<const PromotionMove*>(&other);
    return o && Move::operator==(other) && promotion_piece == o->promotion_piece;
}

bool PromotionMove::operator!=(const Move& other) const {
    return !(*this == other);
}

