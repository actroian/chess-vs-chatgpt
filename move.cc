#include "move.h"
#include "board.h"

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

void NormalMove::move(Board& board) const {
    board.placePiece(end.first, end.second, std::move(board.at(start.first, start.second)));
    board.removePiece(start.first, start.second);
}

void NormalMove::undo(Board& board) const {
    board.placePiece(start.first, start.second, std::move(board.at(end.first, end.second)));
    if (captured_piece != '\0') {
        // Restore the captured piece
        board.placePiece(end.first, end.second, std::make_unique<Piece>(captured_piece));
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

void CastleMove::move(Board& board) const {
    board.placePiece(end.first, end.second, std::move(board.at(start.first, start.second)));
    board.removePiece(start.first, start.second);
    board.placePiece(rookend.first, rookend.second, std::move(board.at(rookstart.first, rookstart.second)));
    board.removePiece(rookstart.first, rookstart.second);
}

void CastleMove::undo(Board& board) const {
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

void EnpassantMove::move(Board& board) const {
    board.placePiece(end.first, end.second, std::move(board.at(start.first, start.second)));
    board.removePiece(start.first, start.second);
    board.removePiece(captured_position.first, captured_position.second);
}

void EnpassantMove::undo(Board& board) const {
    board.placePiece(start.first, start.second, std::move(board.at(end.first, end.second)));
    if (captured_piece != '\0') {
        board.placePiece(captured_position.first, captured_position.second, std::make_unique<Piece>(captured_piece));
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
