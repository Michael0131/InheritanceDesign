/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The queen class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"
#include <set>
#include <iostream>
using namespace std;

/***************************************************
 * QUEEN : DISPLAY
 * Draw the queen on the board.
 ***************************************************/
void Queen::display(ogstream* pgout) const
{
    // ask the drawing system to render this piece
    pgout->drawQueen(position, !isWhite());
}

/***************************************************
 * QUEEN : GET MOVES
 * Generate all legal moves (rook + bishop style)
 ***************************************************/
void Queen::getMoves(set<Move>& moves, const Board& board) const
{
    // All 8 possible direction vectors for a queen
    static const int DIRECTIONS[8][2] = {
       { 1, 0 },   // right
       { -1, 0 },  // left
       { 0, 1 },   // up
       { 0, -1 },  // down
       { 1, 1 },   // up-right
       { -1, 1 },  // up-left
       { 1, -1 },  // down-right
       { -1, -1 }  // down-left
    };

    int c0 = position.getCol();
    int r0 = position.getRow();

    // Explore all 8 directions
    for (int i = 0; i < 8; ++i)
    {
        int dc = DIRECTIONS[i][0];
        int dr = DIRECTIONS[i][1];
        int c = c0 + dc;
        int r = r0 + dr;

        // Continue sliding until blocked or off board
        while (Position(c, r).isValid())
        {
            Position dest(c, r);
            const Piece& target = board[dest.getLocation()];

            // Stop if it's a friendly piece
            if (target.getType() != SPACE && target.isWhite() == fWhite)
                break;

            Move m;

            if (target.getType() == SPACE)
            {
                // simple move
                m.assignSimple(position, dest);
            }
            else
            {
                // capture move
                m.assignCapture(position, dest, target.getType());
                m.setWhiteMove(fWhite);
                moves.insert(m);
                break;  // can't move past capture
            }

            m.setWhiteMove(fWhite);
            moves.insert(m);

            // Continue in same direction
            c += dc;
            r += dr;
        }
    }
}
