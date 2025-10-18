/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/

#include "testBishop.h"
#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>
#include <set>
using namespace std;

/*************************************
 * Bishop blocked by friendly pieces
 *************************************/
void TestBishop::getMoves_blocked()
{
    // SETUP
    Board board(nullptr, true);
    Bishop bishop(Position(4, 1), true); // e2
    set<Move> moves;

    // block diagonals with friendly pawns
    board.board[3][2] = new PieceSpy(3, 2, true, PAWN); // d3
    board.board[5][2] = new PieceSpy(5, 2, true, PAWN); // f3
    board.board[3][0] = new PieceSpy(3, 0, true, PAWN); // d1
    board.board[5][0] = new PieceSpy(5, 0, true, PAWN); // f1

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 0);

    // TEARDOWN
    delete board.board[3][2];
    delete board.board[5][2];
    delete board.board[3][0];
    delete board.board[5][0];
}

/*************************************
 * Bishop slides freely to edges
 *************************************/
void TestBishop::getMoves_slideToEnd()
{
    // SETUP
    Board board(nullptr, true);
    Bishop bishop(Position(4, 1), true); // e2
    set<Move> moves;

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY
    // Bishop at e2 should have 9 valid diagonal moves
    assertUnit(moves.size() == 9);

    bool found = false;
    for (const Move& m : moves)
    {
        const Position& dest = m.getDest();
        if (dest.getCol() == 0 && dest.getRow() == 5) // a6
            found = true;
    }
    assertUnit(found);
}

/*************************************
 * Bishop slides until blocked by allies
 *************************************/
void TestBishop::getMoves_slideToBlock()
{
    // SETUP
    Board board(nullptr, true);
    Bishop bishop(Position(4, 1), true); // e2
    set<Move> moves;

    // Friendly blockers
    board.board[6][3] = new PieceSpy(6, 3, true, PAWN); // g4
    board.board[2][3] = new PieceSpy(2, 3, true, PAWN); // c4

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY — can move until just before allies
    assertUnit(moves.size() > 0);

    // none should land on c4 or g4
    for (const Move& m : moves)
    {
        const Position& d = m.getDest();
        assertUnit(!(d.getCol() == 2 && d.getRow() == 3));
        assertUnit(!(d.getCol() == 6 && d.getRow() == 3));
    }

    // TEARDOWN
    delete board.board[6][3];
    delete board.board[2][3];
}

/*************************************
 * Bishop can capture enemies diagonally
 *************************************/
void TestBishop::getMoves_slideToCapture()
{
    // SETUP
    Board board(nullptr, true);
    Bishop bishop(Position(4, 1), true); // e2
    set<Move> moves;

    // Enemy pieces on diagonals
    board.board[6][3] = new PieceSpy(6, 3, false, PAWN); // g4
    board.board[2][3] = new PieceSpy(2, 3, false, PAWN); // c4

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY — both captures should be possible
    bool c4Found = false, g4Found = false;
    for (const Move& m : moves)
    {
        const Position& d = m.getDest();
        if (d.getCol() == 2 && d.getRow() == 3) c4Found = true;
        if (d.getCol() == 6 && d.getRow() == 3) g4Found = true;
    }
    assertUnit(c4Found && g4Found);

    // TEARDOWN
    delete board.board[6][3];
    delete board.board[2][3];
}

/*************************************
 * getType() returns correct enum
 *************************************/
void TestBishop::getType()
{
    Bishop bishop(Position(4, 1), true);
    assertUnit(bishop.getType() == BISHOP);
}
