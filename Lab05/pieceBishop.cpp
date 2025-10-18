/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The Bishop class - generates all legal diagonal moves
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>

 /***************************************************
  * BISHOP : DISPLAY
  * Draw the bishop on the board.
  ***************************************************/
void Bishop::display(ogstream* pgout) const
{
    // ask the drawing system to render this piece
    pgout->drawBishop(position, !isWhite());
}

/***************************************************
 * BISHOP : GET MOVES
 * Return all possible diagonal moves for the bishop.
 ***************************************************/
void Bishop::getMoves(set<Move>& moves, const Board& board) const
{
    static const int DIRECTIONS[4][2] = {
        {  1,  1 },   // up-right
        {  1, -1 },   // down-right
        { -1, -1 },   // down-left
        { -1,  1 }    // up-left
    };

    int c0 = position.getCol();
    int r0 = position.getRow();

    for (int d = 0; d < 4; ++d)
    {
        int c = c0 + DIRECTIONS[d][0];
        int r = r0 + DIRECTIONS[d][1];

        // Keep moving diagonally until we hit a blocker or board edge
        while (Position(c, r).isValid())
        {
            Position dest(c, r);
            const Piece& target = board[dest.getLocation()];

            // Blocked by friendly piece — stop
            if (target.getType() != SPACE && target.isWhite() == fWhite)
                break;

            Move m;
            if (target.getType() == SPACE)
                m.assignSimple(position, dest);
            else
                m.assignCapture(position, dest, target.getType());

            m.setWhiteMove(fWhite);
            moves.insert(m);

            // Stop if capture; bishop can’t jump
            if (target.getType() != SPACE)
                break;

            // Continue further diagonally
            c += DIRECTIONS[d][0];
            r += DIRECTIONS[d][1];
        }
    }
}
