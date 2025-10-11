/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and the state of the board
 ************************************************************************/

#include "board.h"
#include "position.h"
#include "piece.h"
#include <cassert>
using namespace std;

// A single global Space used when a slot is empty or out of range.
static Space space;

/***********************************************
 * BOARD : CONSTRUCTOR
 ***********************************************/
Board::Board()
{
    numMoves = 0;
    for (int c = 0; c < 8; ++c)
        for (int r = 0; r < 8; ++r)
            board[c][r] = nullptr;
}

/***********************************************
 * BOARD : DESTRUCTOR
 *
 * Do not delete board[c][r] here. Unit tests may place stack-allocated
 * Piece doubles into board[][] and expect no ownership/deletion.
 ***********************************************/
Board::~Board()
{
    for (int c = 0; c < 8; ++c)
        for (int r = 0; r < 8; ++r)
            board[c][r] = nullptr;
}

/***********************************************
 * BOARD : FETCH (const)
 *
 * IMPORTANT: Do not require pos.isValid(). The tests pass in subclasses
 * of Position that override getCol()/getRow() without touching colRow.
 * We only trust the virtual getters and bounds-check the indices.
 ***********************************************/
const Piece& Board::operator[](const Position& pos) const
{
    int c = pos.getCol();
    int r = pos.getRow();
    if (c < 0 || c > 7 || r < 0 || r > 7)
        return space;

    Piece* p = board[c][r];
    return p ? *p : space;
}

/***********************************************
 * BOARD : FETCH/SET (non-const)
 *
 * Returns a reference to the piece residing at board[col][row] if present,
 * otherwise returns a reference to the global Space. We do NOT allocate
 * new objects here; pointer identity must be preserved for the tests.
 ***********************************************/
Piece& Board::operator[](const Position& pos)
{
    int c = pos.getCol();
    int r = pos.getRow();
    if (c < 0 || c > 7 || r < 0 || r > 7)
        return space;

    Piece* p = board[c][r];
    return p ? *p : space;
}

/**********************************************
 * BOARD EMPTY
 * (Used by some unit tests as an always-empty board)
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr)
{
    pSpace = new Space;
    // Ensure the inherited board is nulled
    for (int c = 0; c < 8; ++c)
        for (int r = 0; r < 8; ++r)
            board[c][r] = nullptr;
}

BoardEmpty::~BoardEmpty()
{
    delete pSpace;
}
