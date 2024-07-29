#include "move.h"
#include "board.h"
using namespace std;

Move::Move(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece)
    : start(start), end(end), captured_piece(captured_piece) {}

Move::~Move() {}

bool Move::operator==(const Move& other) const {
    return start == other.start && end == other.end && captured_piece == other.captured_piece;
}

bool Move::operator!=(const Move& other) const {
    return !(*this == other);
}

NormalMove::NormalMove(const std::pair<int, int>& start, const std::pair<int, int>& end, char captured_piece)
    : Move(start, end, captured_piece) {}

bool NormalMove::move(unique_ptr<Board>& board, Player* p1, Player* p2) const {
    board->placePiece(end.first, end.second, std::move(board->at(start.first, start.second)));
    board->removePiece(start.first, start.second);
    if(p1->kingInCheck(board, p1, p2)){
        return false;
    }
    return true;
}

void NormalMove::undo(Board& board) {
    board.placePiece(start.first, start.second, std::move(board.at(end.first, end.second)));
    if (captured_piece != '\0') {
        string piece = string{captured_piece};
        board.placePiece(end.first, end.second, board.createPiece(piece, end));
    } else {
        board.removePiece(end.first, end.second);
    }
}

bool NormalMove::operator==(const Move& other) const {
    return Move::operator==(other);
}

bool NormalMove::operator!=(const Move& other) const {
    return !(*this == other);
}

CastleMove::CastleMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& rookstart, const std::pair<int, int>& rookend)
    : Move(start, end), rookstart(rookstart), rookend(rookend) {}

bool CastleMove::move(unique_ptr<Board>& board, Player* movingplayer, Player* opponent) const {
    if (start.second <= end.second) {
        for (int i = start.second; i < end.second - 1; ++i) {
            board->placePiece(start.first, i + 1, std::move(board->at(start.first, i)));
            board->removePiece(start.first, i);
            if (movingplayer->kingInCheck(board, movingplayer, opponent)) {
                board->placePiece(end.first, end.second, std::move(board->at(start.first, i + 1)));
                board->removePiece(start.first, i + 1);
                board->placePiece(rookend.first, rookend.second, std::move(board->at(rookstart.first, rookstart.second)));
    board->removePiece(rookstart.first, rookstart.second);
                return false;
            }
        }
        board->placePiece(end.first, end.second, std::move(board->at(start.first, end.second - 1)));
        board->removePiece(start.first, end.second - 1);
    } else {
        for (int i = start.second; i > end.second + 1; --i) {
            board->placePiece(start.first, i - 1, std::move(board->at(start.first, i)));
            board->removePiece(start.first, i);
            if (movingplayer->kingInCheck(board, movingplayer, opponent)) {
                board->placePiece(end.first, end.second, std::move(board->at(start.first, i - 1)));
                board->removePiece(start.first, i - 1);
board->placePiece(rookend.first, rookend.second, std::move(board->at(rookstart.first, rookstart.second)));
    board->removePiece(rookstart.first, rookstart.second);
                return false;
            }
        }
        board->placePiece(end.first, end.second, std::move(board->at(start.first, end.second + 1)));
        board->removePiece(start.first, end.second + 1);
    }

    board->placePiece(rookend.first, rookend.second, std::move(board->at(rookstart.first, rookstart.second)));
    board->removePiece(rookstart.first, rookstart.second);
    return true;
}

void CastleMove::undo(Board& board) {
    board.placePiece(start.first, start.second, std::move(board.at(end.first, end.second)));
    board.placePiece(rookstart.first, rookstart.second, std::move(board.at(rookend.first, rookend.second)));
    board.removePiece(end.first, end.second);
    board.removePiece(rookend.first, rookend.second);
}

bool CastleMove::operator==(const Move& other) const {
    const CastleMove* o = dynamic_cast<const CastleMove*>(&other);
    return o && Move::operator==(other) && rookstart == o->rookstart && rookend == o->rookend;
}

bool CastleMove::operator!=(const Move& other) const {
    return !(*this == other);
}

EnpassantMove::EnpassantMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& captured_position, char captured_piece)
    : Move(start, end, captured_piece), captured_position(captured_position) {}

bool EnpassantMove::move(unique_ptr<Board>& board, Player* movingplayer, Player* opponent) const {
    board->placePiece(end.first, end.second, std::move(board->at(start.first, start.second)));
    board->removePiece(start.first, start.second);
    board->removePiece(captured_position.first, captured_position.second);
    if(movingplayer->kingInCheck(board, movingplayer, opponent)){
        // Undo the move if it puts the king in check
        board->placePiece(start.first, start.second, std::move(board->at(end.first, end.second)));
        if (captured_piece != '\0') {
            string piece = string{captured_piece};
            board->placePiece(captured_position.first, captured_position.second, board->createPiece(piece, captured_position));
        }
        return false;
    }
    return true;
}

void EnpassantMove::undo(Board& board) {
    board.placePiece(start.first, start.second, std::move(board.at(end.first, end.second)));
    if (captured_piece != '\0') {
        string piece = string{captured_piece};
        board.placePiece(captured_position.first, captured_position.second, board.createPiece(piece, captured_position));
    }
    board.removePiece(end.first, end.second);
}

bool EnpassantMove::operator==(const Move& other) const {
    const EnpassantMove* o = dynamic_cast<const EnpassantMove*>(&other);
    return o && Move::operator==(other) && captured_position == o->captured_position;
}

bool EnpassantMove::operator!=(const Move& other) const {
    return !(*this == other);
}

PromotionMove::PromotionMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const char promotion_piece, char captured_piece)
    : Move{start, end, captured_piece}, promotion_piece{promotion_piece} {}

bool PromotionMove::move(unique_ptr<Board>& board, Player* movingplayer, Player* opponent) const {
    string promotion = getInput("pawn promotion", validPromotions);
    promotion = movingplayer->isP1() ? toupper(promotion[0]) : tolower(promotion[0]);
    board->placePiece(end.first, end.second, board->createPiece(promotion, end));
    board->removePiece(start.first, start.second);
    cout << "Pawn promoted to " << promotion << endl;
    return true;
}

void PromotionMove::undo(Board& board) {
    board.removePiece(end.first, end.second);
    board.placePiece(start.first, start.second, make_unique<Pawn>(start.first, start.second, board, promotion_piece != tolower(promotion_piece)));
}

bool PromotionMove::operator==(const Move& other) const {
    const PromotionMove* o = dynamic_cast<const PromotionMove*>(&other);
    return o && Move::operator==(other) && promotion_piece == o->promotion_piece;
}

bool PromotionMove::operator!=(const Move& other) const {
    return !(*this == other);
}
