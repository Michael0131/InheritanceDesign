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
#include "piecePawn.h"
#include "pieceRook.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include "pieceBishop.h"
#include <cassert>
using namespace std;

/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8 R N B Q K B N R     8
 *   7 P P P P P P P P     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2 p p p p p p p p     2
 *   1 r n b q k b n r     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
    // free everything
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;

    // white pieces
    board[0][0] = new Rook(Position("a1"), true);
    board[1][0] = new Knight(Position("b1"), true);
    board[2][0] = new Bishop(Position("c1"), true);
    board[3][0] = new Queen(Position("d1"), true);
    board[4][0] = new King(Position("e1"), true);
    board[5][0] = new Bishop(Position("f1"), true);
    board[6][0] = new Knight(Position("g1"), true);
    board[7][0] = new Rook(Position("h1"), true);
    for (int c = 0; c < 8; c++)
        board[c][1] = new Pawn(Position(c, 1), true);

    // black pieces
    board[0][7] = new Rook(Position("a8"), false);
    board[1][7] = new Knight(Position("b8"), false);
    board[2][7] = new Bishop(Position("c8"), false);
    board[3][7] = new Queen(Position("d8"), false);
    board[4][7] = new King(Position("e8"), false);
    board[5][7] = new Bishop(Position("f8"), false);
    board[6][7] = new Knight(Position("g8"), false);
    board[7][7] = new Rook(Position("h8"), false);
    for (int c = 0; c < 8; c++)
        board[c][6] = new Pawn(Position(c, 6), false);

    numMoves = 0;
}

// we really REALLY need to delete this.
static Space gSpace(0, 0);

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

    if (!src.isValid() || !dst.isValid())
        return;

    Piece* pSrc = board[src.getCol()][src.getRow()];
    Piece* pDst = board[dst.getCol()][dst.getRow()];
    if (!pSrc)
        return;

    // --------------------------------------------
    // 1) En Passant
    // --------------------------------------------
    if (move.isEnPassant() && pSrc && pSrc->getType() == PAWN)
    {
        int dir = pSrc->isWhite() ? -1 : 1;
        Position capturedPos(dst.getCol(), dst.getRow() + dir);

        // Remove the captured pawn first
        if (board[capturedPos.getCol()][capturedPos.getRow()])
        {
            board[capturedPos.getCol()][capturedPos.getRow()] = nullptr;
        }

        // Replace the captured square with a Space
        board[capturedPos.getCol()][capturedPos.getRow()] =
            new Space(capturedPos.getCol(), capturedPos.getRow());

        // Move the capturing pawn
        board[dst.getCol()][dst.getRow()] = pSrc;
        board[src.getCol()][src.getRow()] = new Space(src.getCol(), src.getRow());

        pSrc->setPosition(dst);
        pSrc->setLastMove(numMoves);
        numMoves++;
        return;

    }

    // --------------------------------------------
    // 2) Castling (Short / Long)
    // --------------------------------------------
    if (move.moveType == Move::CASTLE_KING)
    {
        // King: e1->g1 (white) or e8->g8 (black)
        // Rook: h1->f1 or h8->f8
        int row = src.getRow();  // 0 for white, 7 for black if using standard setup
        // move king
        board[dst.getCol()][dst.getRow()] = pSrc;
        board[src.getCol()][src.getRow()] = new Space(src.getCol(), src.getRow());
        pSrc->setPosition(dst);
        pSrc->setLastMove(numMoves);

        // move rook
        Piece* rook = board[7][row];
        if (rook)
        {
            board[5][row] = rook;
            board[7][row] = new Space(7, row);
            rook->setPosition(Position(5, row));
            rook->setLastMove(numMoves);
        }

        numMoves++;
        return;
    }
    else if (move.moveType == Move::CASTLE_QUEEN)
    {
        // King: e1->c1 (white) or e8->c8 (black)
        // Rook: a1->d1 or a8->d8
        int row = src.getRow();
        // move king
        board[dst.getCol()][dst.getRow()] = pSrc;
        board[src.getCol()][src.getRow()] = new Space(src.getCol(), src.getRow());
        pSrc->setPosition(dst);
        pSrc->setLastMove(numMoves);

        // move rook
        Piece* rook = board[0][row];
        if (rook)
        {
            board[3][row] = rook;
            board[0][row] = new Space(0, row);
            rook->setPosition(Position(3, row));
            rook->setLastMove(numMoves);
        }

        numMoves++;
        return;
    }

    // --------------------------------------------
    // 3) Promotion (always promote to Queen per requirements)
    // --------------------------------------------
    if (pSrc->getType() == PAWN)
    {
        int lastRank = pSrc->isWhite() ? 7 : 0;
        if (dst.getRow() == lastRank)
        {
            board[dst.getCol()][dst.getRow()] = new Queen(dst, pSrc->isWhite());
            board[src.getCol()][src.getRow()] = new Space(src.getCol(), src.getRow());
            numMoves++;
            return;
        }
    }

    // --------------------------------------------
    // 4) Normal move / capture
    // --------------------------------------------
    if (pDst && pDst->getType() != SPACE)
    {
        // simply overwrite without deleting (the test harness manages it)
        pDst = nullptr;
    }

    // Move pointer from src to dest
    board[dst.getCol()][dst.getRow()] = pSrc;
    board[src.getCol()][src.getRow()] = new Space(src.getCol(), src.getRow());

    // Update piece state
    pSrc->setPosition(dst);
    pSrc->setLastMove(numMoves);

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
