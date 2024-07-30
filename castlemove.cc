#include "castlemove.h"
using namespace std;

CastleMove::CastleMove(const std::pair<int, int>& start, const std::pair<int, int>& end, const std::pair<int, int>& rookstart, const std::pair<int, int>& rookend)
    : Move(start, end), rookstart(rookstart), rookend(rookend) {}

bool CastleMove::move(unique_ptr<Board>& board, Player* movingplayer, Player* opponent, bool isPromotionMove) const {
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

std::unique_ptr<Move> CastleMove::clone() const {
  return std::make_unique<CastleMove>(*this);
}
