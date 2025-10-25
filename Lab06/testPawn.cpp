/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>
#include <set>
using namespace std;

/* -------------------------------------------------
 * Local helpers (same style we used for other pieces)
 * ------------------------------------------------- */
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


/*************************************
 * GET MOVES Simple White
 * White pawn in the middle of the board: b4b5
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5     .               5
 * 4    (p)              4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleWhite()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("b4"), true /*white*/);
    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 1);
    assertUnit(hasSimple(moves, Position("b4"), Position("b5"), true));

    // TEARDOWN
}

/*************************************
 * GET MOVES Simple Black
 * Black pawn in the middle of the board: b4b3
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("b4"), false /*black*/);
    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 1);
    assertUnit(hasSimple(moves, Position("b4"), Position("b3"), false));

    // TEARDOWN
}

/*************************************
 * GET MOVES Initial Advance White
 * White pawn initial advance: b2b3, b2b4
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("b2"), true /*white*/);
    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 2);
    assertUnit(hasSimple(moves, Position("b2"), Position("b3"), true));
    assertUnit(hasSimple(moves, Position("b2"), Position("b4"), true));

    // TEARDOWN
}

/*************************************
 * GET MOVES Initial Advance Black
 * Black pawn initial advance: c7c6, c7c5
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("c7"), false /*black*/);
    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 2);
    assertUnit(hasSimple(moves, Position("c7"), Position("c6"), false));
    assertUnit(hasSimple(moves, Position("c7"), Position("c5"), false));

    // TEARDOWN
}

/*************************************
 * GET MOVES Capture White
 * Double capture with b7 blocked: b6a7p, b6c7p
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("b6"), true /*white*/);
    // b7 blocked so no straight move
    board.board[1][6] = new Pawn(Position("b7"), true);
    // two enemy targets
    board.board[0][6] = new Pawn(Position("a7"), false);
    board.board[2][6] = new Pawn(Position("c7"), false);

    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(hasCapture(moves, Position("b6"), Position("a7"), true, PAWN));
    assertUnit(hasCapture(moves, Position("b6"), Position("c7"), true, PAWN));
    // no straight-forward because blocked
    assertUnit(!hasSimple(moves, Position("b6"), Position("b7"), true));

    // TEARDOWN
    delete board.board[1][6];
    delete board.board[0][6];
    delete board.board[2][6];
    board.board[1][6] = board.board[0][6] = board.board[2][6] = nullptr;
}

/*************************************
 * GET MOVES Capture Black
 * Double capture with b5 blocked: b6a5p, b6c5p
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("b6"), false /*black*/);
    // block straight-forward (to b5)
    board.board[1][4] = new Pawn(Position("b5"), false);
    // two enemy targets
    board.board[0][4] = new Pawn(Position("a5"), true);
    board.board[2][4] = new Pawn(Position("c5"), true);

    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(hasCapture(moves, Position("b6"), Position("a5"), false, PAWN));
    assertUnit(hasCapture(moves, Position("b6"), Position("c5"), false, PAWN));
    assertUnit(!hasSimple(moves, Position("b6"), Position("b5"), false));

    // TEARDOWN
    delete board.board[1][4];
    delete board.board[0][4];
    delete board.board[2][4];
    board.board[1][4] = board.board[0][4] = board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES Enpassant White
 * Enpassant with b6 blocked: b5a6E, b5c6E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
    // SETUP
    Board board(nullptr, true);
    board.numMoves = 20; // simulate current ply

    Pawn  p(Position("b5"), true /*white*/);

    // b6 blocked so there is no straight-forward
    board.board[1][5] = new Pawn(Position("b6"), false);

    // enemy pawns on a5 and c5 that "just" moved two squares
    Pawn* a5 = new Pawn(Position("a5"), false);
    Pawn* c5 = new Pawn(Position("c5"), false);
    a5->setLastMove(board.numMoves - 1); a5->nMoves = 1;
    c5->setLastMove(board.numMoves - 1); c5->nMoves = 1;

    board.board[0][4] = a5;
    board.board[2][4] = c5;

    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    // if your Pawn::getMoves supports en passant using move history,
    // both diagonal “E” captures should be present; and b6 is blocked.
    assertUnit(!hasSimple(moves, Position("b5"), Position("b6"), true));
    assertUnit(hasCapture(moves, Position("b5"), Position("a6"), true, PAWN));
    assertUnit(hasCapture(moves, Position("b5"), Position("c6"), true, PAWN));

    // TEARDOWN
    delete board.board[1][5];
    delete board.board[0][4];
    delete board.board[2][4];
    board.board[1][5] = board.board[0][4] = board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES Enpassant Black
 * Enpassant with f3 blocked: f4g3E, f4e3E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
    // SETUP
    Board board(nullptr, true);
    board.numMoves = 30;

    Pawn  p(Position("f4"), false /*black*/);

    // f3 blocked so there is no straight-forward
    board.board[5][2] = new Pawn(Position("f3"), false);

    // enemy pawns that "just" moved two squares: e4 and g4
    Pawn* e4 = new Pawn(Position("e4"), true);
    Pawn* g4 = new Pawn(Position("g4"), true);
    e4->setLastMove(board.numMoves - 1); e4->nMoves = 1;
    g4->setLastMove(board.numMoves - 1); g4->nMoves = 1;

    board.board[4][3] = e4;
    board.board[6][3] = g4;

    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(!hasSimple(moves, Position("f4"), Position("f3"), false));
    assertUnit(hasCapture(moves, Position("f4"), Position("e3"), false, PAWN));
    assertUnit(hasCapture(moves, Position("f4"), Position("g3"), false, PAWN));

    // TEARDOWN
    delete board.board[5][2];
    delete board.board[4][3];
    delete board.board[6][3];
    board.board[5][2] = board.board[4][3] = board.board[6][3] = nullptr;
}

/*************************************
 * GET MOVES Enpassant Denied
 * Enpassant: b6 is blocked with black pawn
 *            pawn at a5 moved twice
 *            pawn at c5 moved two turns ago
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6     P               6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantDenied()
{
    // SETUP
    Board board(nullptr, true);
    board.numMoves = 40;

    Pawn  p(Position("b5"), true /*white*/);

    // b6 blocked
    board.board[1][5] = new Pawn(Position("b6"), false);

    // a5 enemy moved twice (nMoves=2) last turn -> not eligible EP
    Pawn* a5 = new Pawn(Position("a5"), false);
    a5->nMoves = 2;
    a5->setLastMove(board.numMoves - 1);

    // c5 enemy moved two turns ago -> not eligible EP
    Pawn* c5 = new Pawn(Position("c5"), false);
    c5->nMoves = 1;
    c5->setLastMove(board.numMoves - 2);

    board.board[0][4] = a5;
    board.board[2][4] = c5;

    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(!hasCapture(moves, Position("b5"), Position("a6"), true, PAWN));
    assertUnit(!hasCapture(moves, Position("b5"), Position("c6"), true, PAWN));
    assertUnit(!hasSimple(moves, Position("b5"), Position("b6"), true)); // blocked

    // TEARDOWN
    delete board.board[1][5];
    delete board.board[0][4];
    delete board.board[2][4];
    board.board[1][5] = board.board[0][4] = board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES Promotion White
 * Promotion white pawn b7 can capture two pawns: a8 and c8.
 *          It can also move into b8. All three are promoted to queen:
 *          b7a8pQ, b7b8Q, b7c8pQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("b7"), true /*white*/);
    board.board[0][7] = new Pawn(Position("a8"), false);
    board.board[2][7] = new Pawn(Position("c8"), false);
    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY (we only check destinations here; promotion letter handled elsewhere)
    assertUnit(hasSimple(moves, Position("b7"), Position("b8"), true));
    assertUnit(hasCapture(moves, Position("b7"), Position("a8"), true, PAWN));
    assertUnit(hasCapture(moves, Position("b7"), Position("c8"), true, PAWN));

    // TEARDOWN
    delete board.board[0][7];
    delete board.board[2][7];
    board.board[0][7] = board.board[2][7] = nullptr;
}

/*************************************
 * GET MOVES Promotion Black
 * Promotion: black pawn e2 can capture two rooks: d1 and f1.
 *            It can also move into e1. All three are promoted to queen:
 *            e2d1rQ, e2e1Q, e2f1rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         r . r       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
    // SETUP
    Board board(nullptr, true);
    Pawn  p(Position("e2"), false /*black*/);
    // use pawns as targets; type checking uses PAWN capture
    board.board[3][0] = new Pawn(Position("d1"), true);
    board.board[5][0] = new Pawn(Position("f1"), true);
    set<Move> moves;

    // EXERCISE
    p.getMoves(moves, board);

    // VERIFY
    assertUnit(hasSimple(moves, Position("e2"), Position("e1"), false));
    assertUnit(hasCapture(moves, Position("e2"), Position("d1"), false, PAWN));
    assertUnit(hasCapture(moves, Position("e2"), Position("f1"), false, PAWN));

    // TEARDOWN
    delete board.board[3][0];
    delete board.board[5][0];
    board.board[3][0] = board.board[5][0] = nullptr;
}

/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
    // SETUP / EXERCISE
    Pawn p(Position("a2"), true);

    // VERIFY
    assertUnit(p.getType() == PAWN);

    // TEARDOWN
}
