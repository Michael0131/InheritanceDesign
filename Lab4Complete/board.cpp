/***********************************************************************
 * Source File:
 *    BOARD 
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include <cassert>
using namespace std;

/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;

   //white knights
   board[1][0] = new Knight(1, 0, false); //b1
   board[6][0] = new Knight(6, 0, false); //g1

   //black knights
   board[1][7] = new Knight(1, 7, true); //b8
   board[6][7] = new Knight(6, 7, true); //g8

}

// we really REALLY need to delete this.
static Space gSpace(0,0);

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
    int c = pos.getCol();
    int r = pos.getRow();

    if (c < 0 || c > 7 || r < 0 || r > 7)
        return gSpace;

    Piece* p = board[c][r];
    return (p ? *p : gSpace);
}
Piece& Board::operator [] (const Position& pos)
{
    int c = pos.getCol();
    int r = pos.getRow();

    if (c < 0 || c > 7 || r < 0 || r > 7)
        return gSpace;

    Piece* p = board[c][r];
    return (p ? *p : gSpace);
}

/***********************************************
 * BOARD : DISPLAY
 * Draw the board with all the pieces
 ***********************************************/
void Board::display(const Position& posHover, const Position& posSelect) const
{
    assert(pgout);

    // draw the base chessboard
    pgout->drawBoard();

    // Draw all pieces on the board if they exist
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            if (board[c][r])
                board[c][r]->display(pgout);
        }
    }

    // Optionally highlight selection / hover
    if (posSelect.isValid())
        pgout->drawSelected(posSelect);

    if (posHover.isValid())
        pgout->drawHover(posHover);
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
    for (int c = 0; c < 8; ++c)
    {
        for (int r = 0; r < 8; ++r)
            board[c][r] = nullptr;

        if (!noreset)
        {
            reset(false);
        }
    }

}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
    for (int c = 0; c < 8; ++c)
    {
        for (int r = 0; r < 8; ++r)
        {
            delete board[c][r];
            board[c][r] = nullptr;

        }

    }

}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{
    for (int c = 0; c < 8; ++c)
    {
        for (int r = 0; r < 8; ++r)
        {
            assert(c >= 0 && c < 8 && r >= 0 && r < 8);

        }

    }

}



/**********************************************
 * BOARD : MOVE
 * Execute a move according to the contained instructions
 *********************************************/
void Board::move(const Move& move)
{
    Position src = move.source;
    Position dst = move.dest;

    // Ensure both are valid
    if (!src.isValid() || !dst.isValid())
        return;

    Piece* pSrc = board[src.getCol()][src.getRow()];
    Piece* pDst = board[dst.getCol()][dst.getRow()];


    // Move pointer from src to dest
    board[dst.getCol()][dst.getRow()] = pSrc;
    board[src.getCol()][src.getRow()] = new Space(src.getCol(), src.getRow());

    // Update the piece’s internal position
    if (pSrc)
        pSrc->setPosition(dst);

    // Increment move counter
    numMoves++;
}



/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 **********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
    pSpace = new Space(0, 0);

    for (int c = 0; c < 8; ++c)
        for (int r = 0; r < 8; ++r)
            board[c][r] = nullptr;
}

BoardEmpty::~BoardEmpty()
{
    delete pSpace;
    pSpace = nullptr;
}


// LAB 3 EXTRA FUNCTIONS
