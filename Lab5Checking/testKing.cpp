/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceKing.h"
#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>
#include <set>
using namespace std;

/* ---------- Local test helpers ---------- */

// Dummy piece (for blocking/capturing)
class DummyPiece : public Piece
{
public:
    DummyPiece(const Position& p, bool w, PieceType t = PAWN)
        : Piece(p, w), t(t) {
    }
    PieceType getType() const override { return t; }
    void display(ogstream*) const override {}
    void getMoves(set<Move>&, const Board&) const override {}
private:
    PieceType t;
};

// helpers
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

static bool hasCastle(const set<Move>& moves,
    const Position& from,
    const Position& to,
    bool isWhite,
    bool isKingSide)
{
    Move m;
    if (isKingSide)
        m.assignCastleKing(from, to);
    else
        m.assignCastleQueen(from, to);

    m.setWhiteMove(isWhite);
    return moves.count(m) == 1;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blocked()
{
    Board board(nullptr, true);
    King king(Position("d5"), true);

    const char* pos[] = { "c6","d6","e6","c5","e5","c4","d4","e4" };
    for (const char* p : pos)
        board.board[Position(p).getCol()][Position(p).getRow()] = new DummyPiece(Position(p), true, PAWN);

    set<Move> moves;
    king.getMoves(moves, board);

    assertUnit(moves.empty());

    for (const char* p : pos)
    {
        auto& cell = board.board[Position(p).getCol()][Position(p).getRow()];
        delete cell;
        cell = nullptr;
    }
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
    Board board(nullptr, true);
    King king(Position("d5"), true);

    const char* pos[] = { "c6","d6","e6","c5","e5","c4","d4","e4" };
    for (const char* p : pos)
        board.board[Position(p).getCol()][Position(p).getRow()] = new DummyPiece(Position(p), false, PAWN);

    set<Move> moves;
    king.getMoves(moves, board);

    assertUnit(moves.size() == 8);
    for (const char* p : pos)
        assertUnit(hasCapture(moves, Position("d5"), Position(p), true, PAWN));

    for (const char* p : pos)
    {
        auto& cell = board.board[Position(p).getCol()][Position(p).getRow()];
        delete cell;
        cell = nullptr;
    }
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
    Board board(nullptr, true);
    King king(Position("d5"), true);
    set<Move> moves;
    
    king.getMoves(moves, board);

    const char* pos[] = { "c6","d6","e6","c5","e5","c4","d4","e4" };
    assertUnit(moves.size() == 8);
    for (const char* p : pos)
        assertUnit(hasSimple(moves, Position("d5"), Position(p), true));
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
    Board board(nullptr, true);
    King king(Position("b1"), true);
    set<Move> moves;

    king.setLastMove(1); // king already moved

    king.getMoves(moves, board);

    const char* valid[] = { "a1","a2","b2","c1","c2" };
    assertUnit(moves.size() == 5);
    for (const char* p : valid)
        assertUnit(hasSimple(moves, Position("b1"), Position(p), true));
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
    Board board(nullptr, true);
    King king(Position("e1"), true);
    Rook leftR(Position("a1"), true);
    Rook rightR(Position("h1"), true);

    board.board[0][0] = &leftR;
    board.board[7][0] = &rightR;

    set<Move> moves;
    king.getMoves(moves, board);

    // King-side and queen-side castle
    assertUnit(hasCastle(moves, Position("e1"), Position("g1"), true, true));
    assertUnit(hasCastle(moves, Position("e1"), Position("c1"), true, false));

    board.board[0][0] = board.board[7][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{
    Board board(nullptr, true);
    King king(Position("e8"), false);
    Rook leftR(Position("a8"), false);
    Rook rightR(Position("h8"), false);

    board.board[0][7] = &leftR;
    board.board[7][7] = &rightR;

    set<Move> moves;
    king.getMoves(moves, board);

    assertUnit(hasCastle(moves, Position("e8"), Position("g8"), false, true));
    assertUnit(hasCastle(moves, Position("e8"), Position("c8"), false, false));

    board.board[0][7] = board.board[7][7] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
    Board board(nullptr, true);
    King king(Position("e1"), true);
    king.setLastMove(1); // king already moved
    Rook leftR(Position("a1"), true);
    Rook rightR(Position("h1"), true);

    board.board[0][0] = &leftR;
    board.board[7][0] = &rightR;

    set<Move> moves;
    king.getMoves(moves, board);

    assertUnit(!hasCastle(moves, Position("e1"), Position("g1"), true, true));
    assertUnit(!hasCastle(moves, Position("e1"), Position("c1"), true, false));

    board.board[0][0] = board.board[7][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
    Board board(nullptr, true);
    King king(Position("e1"), true);
    Rook leftR(Position("a1"), true);
    leftR.setLastMove(1);
    Rook rightR(Position("h1"), true);
    rightR.setLastMove(2);

    board.board[0][0] = &leftR;
    board.board[7][0] = &rightR;

    set<Move> moves;
    king.getMoves(moves, board);

    assertUnit(!hasCastle(moves, Position("e1"), Position("g1"), true, true));
    assertUnit(!hasCastle(moves, Position("e1"), Position("c1"), true, false));

    board.board[0][0] = board.board[7][0] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
    King k(Position("a1"), true);
    assertUnit(k.getType() == KING);
}
