/***********************************************************************
 * Source File:
 *    TEST ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the rook
 ************************************************************************/

#include "testRook.h"
#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>
#include <set>
using namespace std;

/***************************************************
 * DummyPiece
 * Simple stand-in for real pieces used in testing.
 ***************************************************/
class DummyPiece : public Piece
{
public:
    DummyPiece(const Position& pos, bool white, PieceType t = PAWN)
        : Piece(pos, white), t(t) {
    }
    virtual PieceType getType() const override { return t; }
    virtual void getMoves(set<Move>&, const Board&) const {}
    virtual void display(ogstream*) const override {}

private:
    PieceType t;
};

/***************************************************
 * Helper functions
 ***************************************************/
static bool hasSimple(const set<Move>& moves,
    const Position& from,
    const Position& to,
    bool isWhite)
{
    Move m;
    m.assignSimple(from, to);
    m.setWhiteMove(isWhite);
    return moves.find(m) != moves.end();
}

static bool hasCapture(const set<Move>& moves,
    const Position& from,
    const Position& to,
    bool isWhite,
    PieceType captured)
{
    Move m;
    m.assignCapture(from, to, captured);
    m.setWhiteMove(isWhite);
    return moves.find(m) != moves.end();
}

/*************************************
 * getMoves_blocked
 *************************************/
void TestRook::getMoves_blocked()
{
    // SETUP
    Board board(nullptr, true /* noreset */);
    Rook rook(Position("d2"), true);

    // Surround rook with friendly pawns
    board.board[3][3] = new DummyPiece(Position("d3"), true);
    board.board[3][1] = new DummyPiece(Position("d1"), true);
    board.board[2][2] = new DummyPiece(Position("c2"), true);
    board.board[4][2] = new DummyPiece(Position("e2"), true);

    set<Move> moves;
    rook.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.empty());

    // TEARDOWN
    delete board.board[3][3];
    delete board.board[3][1];
    delete board.board[2][2];
    delete board.board[4][2];
    board.board[3][3] = board.board[3][1] = board.board[2][2] = board.board[4][2] = nullptr;
}

/*************************************
 * getMoves_slideToEnd
 *************************************/
void TestRook::getMoves_slideToEnd()
{
    Board board(nullptr, true);
    Rook rook(Position("d2"), true);
    set<Move> moves;

    rook.getMoves(moves, board);

    // Should have 14 moves: 7 vertical + 7 horizontal
    assertUnit(moves.size() == 14);

    // Spot-check endpoints
    assertUnit(hasSimple(moves, Position("d2"), Position("d8"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("d1"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("a2"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("h2"), true));
}

/*************************************
 * getMoves_slideToBlock
 *************************************/
void TestRook::getMoves_slideToBlock()
{
    Board board(nullptr, true);
    Rook rook(Position("d2"), true);

    // Friendly pieces at ends
    board.board[3][7] = new DummyPiece(Position("d8"), true);
    board.board[3][1] = new DummyPiece(Position("d1"), true);
    board.board[0][2] = new DummyPiece(Position("a2"), true);
    board.board[7][2] = new DummyPiece(Position("h2"), true);

    set<Move> moves;
    rook.getMoves(moves, board);

    // Up: can move to d3..d7, but not d8
    assertUnit(!hasSimple(moves, Position("d2"), Position("d8"), true));
    for (int r = 3; r <= 7; ++r)
        assertUnit(hasSimple(moves, Position("d2"), Position(3, r), true));

    // Down: blocked at d1
    assertUnit(!hasSimple(moves, Position("d2"), Position("d1"), true));

    // Left: c2, b2 ok; not a2
    assertUnit(hasSimple(moves, Position("d2"), Position("c2"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("b2"), true));
    assertUnit(!hasSimple(moves, Position("d2"), Position("a2"), true));

    // Right: e2, f2, g2 ok; not h2
    assertUnit(hasSimple(moves, Position("d2"), Position("e2"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("f2"), true));
    assertUnit(hasSimple(moves, Position("d2"), Position("g2"), true));
    assertUnit(!hasSimple(moves, Position("d2"), Position("h2"), true));

    // TEARDOWN
    delete board.board[3][7];
    delete board.board[3][1];
    delete board.board[0][2];
    delete board.board[7][2];
    board.board[3][7] = board.board[3][1] = board.board[0][2] = board.board[7][2] = nullptr;
}

/*************************************
 * getMoves_slideToCapture
 *************************************/
void TestRook::getMoves_slideToCapture()
{
    Board board(nullptr, true);
    Rook rook(Position("d2"), true);

    // Enemy pawns at ends
    board.board[3][7] = new DummyPiece(Position("d8"), false);
    board.board[3][1] = new DummyPiece(Position("d1"), false);
    board.board[0][2] = new DummyPiece(Position("a2"), false);
    board.board[7][2] = new DummyPiece(Position("h2"), false);

    set<Move> moves;
    rook.getMoves(moves, board);

    // Capture tests
    assertUnit(hasCapture(moves, Position("d2"), Position("d8"), true, PAWN));
    assertUnit(hasCapture(moves, Position("d2"), Position("d1"), true, PAWN));
    assertUnit(hasCapture(moves, Position("d2"), Position("a2"), true, PAWN));
    assertUnit(hasCapture(moves, Position("d2"), Position("h2"), true, PAWN));

    // TEARDOWN
    delete board.board[3][7];
    delete board.board[3][1];
    delete board.board[0][2];
    delete board.board[7][2];
    board.board[3][7] = board.board[3][1] = board.board[0][2] = board.board[7][2] = nullptr;
}

/*************************************
 * getType
 *************************************/
void TestRook::getType()
{
    Rook r(Position("a1"), true);
    assertUnit(r.getType() == ROOK);
}
