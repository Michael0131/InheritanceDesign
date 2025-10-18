/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    <your name here>
 * Summary:
 *    The King class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"
#include <set>
#include <iostream>

 /***************************************************
  * KING : DISPLAY
  ***************************************************/
void King::display(ogstream* pgout) const
{
    pgout->drawKing(position, !isWhite());
}

/***************************************************
 * KING : GET MOVES
 * Return all possible one-square moves and castling options.
 ***************************************************/
void King::getMoves(set<Move>& moves, const Board& board) const
{
    static const int OFFSETS[8][2] = {
       { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 },
       { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }
    };

    int c0 = position.getCol();
    int r0 = position.getRow();

    // 1️⃣ — Regular one-square moves
    for (auto& o : OFFSETS)
    {
        Position dest(c0 + o[0], r0 + o[1]);
        if (!dest.isValid())
            continue;

        const Piece& target = board[dest];
        if (target.getType() != SPACE && target.isWhite() == fWhite)
            continue;

        Move m;
        if (target.getType() == SPACE)
            m.assignSimple(position, dest);
        else
            m.assignCapture(position, dest, target.getType());
        m.setWhiteMove(fWhite);
        moves.insert(m);
    }

    // 2️⃣ — Castling (only if king has not moved)
    if (!isMoved())
    {
        // King-side castle: move 2 columns to the right
        Move mKing;
        mKing.assignCastleKing(position, Position(c0 + 2, r0));
        mKing.setWhiteMove(fWhite);
        moves.insert(mKing);

        // Queen-side castle: move 2 columns to the left
        Move mQueen;
        mQueen.assignCastleQueen(position, Position(c0 - 2, r0));
        mQueen.setWhiteMove(fWhite);
        moves.insert(mQueen);
    }
}
