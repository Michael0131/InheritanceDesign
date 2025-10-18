/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "testQueen.h"
#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>
#include <set>
using namespace std;

/* ------------------------------------------------------------
   Local test helpers
------------------------------------------------------------ */

// Minimal concrete piece to use as blocker or capture target.
class DummyPiece : public Piece
{
public:
    DummyPiece(const Position& p, bool isWhite, PieceType t = PAWN)
        : Piece(p, isWhite), t(t) {
    }
    PieceType getType() const { return t; }
    void getMoves(set<Move>&, const Board&) const {}
    void display(ogstream*) const {}

private:
    PieceType t;
};

// Helper: check if a simple move exists
static bool hasSimple(const set<Move>& moves,
    const Position& from,
    const Position& to,
    bool isWhite)
{
    Move m;
    m.assignSimple(from, to);
    m.setWhiteMove(isWhite);
    return moves.count(m) == 1;
}

// Helper: check if a capture move exists
static bool hasCapture(const set<Move>& moves,
    const Position& from,
    const Position& to,
    bool isWhite,
    PieceType captured)
{
    Move m;
    m.assignCapture(from, to, captured);
    m.setWhiteMove(isWhite);
    return moves.count(m) == 1;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3     p p p           3
 * 2     p(q)p           2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_blocked()
{
    Board board(nullptr, true);
    Queen queen(Position("d2"), true);

    // Friendly pieces block all 8 directions
    board.board[3][3] = new DummyPiece(Position("d3"), true);
    board.board[3][1] = new DummyPiece(Position("d1"), true);
    board.board[2][2] = new DummyPiece(Position("c2"), true);
    board.board[4][2] = new DummyPiece(Position("e2"), true);
    board.board[2][3] = new DummyPiece(Position("c3"), true);
    board.board[4][3] = new DummyPiece(Position("e3"), true);
    board.board[2][1] = new DummyPiece(Position("c1"), true);
    board.board[4][1] = new DummyPiece(Position("e1"), true);

    set<Move> moves;
    queen.getMoves(moves, board);

    // Should have no legal moves
    assertUnit(moves.empty());

    // cleanup
    for (int c = 2; c <= 4; ++c)
        for (int r = 1; r <= 3; ++r)
            if (board.board[c][r])
            {
                delete board.board[c][r];
                board.board[c][r] = nullptr;
            }
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToEnd()
{
    Board board(nullptr, true);
    Queen queen(Position("d2"), true);
    set<Move> moves;

    queen.getMoves(moves, board);

    // A queen can move like rook + bishop = 27 total moves
    assertUnit(moves.size() == 27);

    // spot-check
    assertUnit(hasSimple(moves, Position("d2"), Position("d8"), true)); // up
    assertUnit(hasSimple(moves, Position("d2"), Position("a5"), true)); // diag up-left
    assertUnit(hasSimple(moves, Position("d2"), Position("h6"), true)); // diag up-right
    assertUnit(hasSimple(moves, Position("d2"), Position("a2"), true)); // left
    assertUnit(hasSimple(moves, Position("d2"), Position("h2"), true)); // right
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToBlock()
{
    Board board(nullptr, true);
    Queen queen(Position("d2"), true);

    // Friendly blockers at each “end”
    board.board[3][7] = new DummyPiece(Position("d8"), true);
    board.board[3][1] = new DummyPiece(Position("d1"), true);
    board.board[0][2] = new DummyPiece(Position("a2"), true);
    board.board[7][2] = new DummyPiece(Position("h2"), true);
    board.board[0][5] = new DummyPiece(Position("a5"), true);
    board.board[6][5] = new DummyPiece(Position("g5"), true);
    board.board[0][0] = new DummyPiece(Position("a1"), true);
    board.board[6][0] = new DummyPiece(Position("g1"), true);

    set<Move> moves;
    queen.getMoves(moves, board);

    // End squares are blocked, but path squares before are valid
    assertUnit(!hasSimple(moves, Position("d2"), Position("d8"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("d7"), true));
    assertUnit(!hasSimple(moves, Position("d2"), Position("a2"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("b2"), true));
    assertUnit(!hasSimple(moves, Position("d2"), Position("a5"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("b4"), true));
    assertUnit(!hasSimple(moves, Position("d2"), Position("g5"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("f4"), true));

    // cleanup
    int coords[8][2] = { {3,7},{3,1},{0,2},{7,2},{0,5},{6,5},{0,0},{6,0} };
    for (auto& xy : coords)
    {
        delete board.board[xy[0]][xy[1]];
        board.board[xy[0]][xy[1]] = nullptr;
    }
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToCapture()
{
    Board board(nullptr, true);
    Queen queen(Position("d2"), true);

    // Enemy pieces at ends
    board.board[3][7] = new DummyPiece(Position("d8"), false);
    board.board[3][1] = new DummyPiece(Position("d1"), false);
    board.board[0][2] = new DummyPiece(Position("a2"), false);
    board.board[7][2] = new DummyPiece(Position("h2"), false);
    board.board[0][5] = new DummyPiece(Position("a5"), false);
    board.board[6][5] = new DummyPiece(Position("g5"), false);
    board.board[0][0] = new DummyPiece(Position("a1"), false);
    board.board[6][0] = new DummyPiece(Position("g1"), false);

    set<Move> moves;
    queen.getMoves(moves, board);

    // Each end square should be included as a CAPTURE
    assertUnit(hasCapture(moves, Position("d2"), Position("d8"), true, PAWN));
    assertUnit(hasCapture(moves, Position("d2"), Position("a2"), true, PAWN));
    assertUnit(hasCapture(moves, Position("d2"), Position("g5"), true, PAWN));
    assertUnit(hasCapture(moves, Position("d2"), Position("a5"), true, PAWN));

    // cleanup
    int coords[8][2] = { {3,7},{3,1},{0,2},{7,2},{0,5},{6,5},{0,0},{6,0} };
    for (auto& xy : coords)
    {
        delete board.board[xy[0]][xy[1]];
        board.board[xy[0]][xy[1]] = nullptr;
    }
}

/*************************************
 * GET TYPE : queen
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{
    Queen q(Position("a1"), true);
    assertUnit(q.getType() == QUEEN);
}
