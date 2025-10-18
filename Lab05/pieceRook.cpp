/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    Implementation of the Rook chess piece.
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"
#include <set>
#include <cassert>
using namespace std;

/***************************************************
 * ROOK : DISPLAY
 * Draw the rook on the board.
 ***************************************************/
void Rook::display(ogstream* pgout) const
{
    pgout->drawRook(position, !isWhite());
}

/***************************************************
 * ROOK : GET MOVES
 * Generate all legal rook moves (vertical and horizontal slides).
 ***************************************************/
void Rook::getMoves(set<Move>& moves, const Board& board) const
{
    static const int DIRECTIONS[4][2] = {
        {  0,  1 },  // up
        {  0, -1 },  // down
        { -1,  0 },  // left
        {  1,  0 }   // right
    };

    int c0 = position.getCol();
    int r0 = position.getRow();

    for (int i = 0; i < 4; ++i)
    {
        int dc = DIRECTIONS[i][0];
        int dr = DIRECTIONS[i][1];

        int c = c0 + dc;
        int r = r0 + dr;

        // slide in direction until blocked
        while (c >= 0 && c < 8 && r >= 0 && r < 8)
        {
            Position dest(c, r);
            const Piece& target = board[dest.getLocation()];

            // empty square → valid simple move
            if (target.getType() == SPACE)
            {
                Move m;
                m.assignSimple(position, dest);
                m.setWhiteMove(fWhite);
                moves.insert(m);
            }
            else
            {
                // occupied → stop sliding after this square
                if (target.isWhite() != fWhite)
                {
                    // enemy → capture allowed
                    Move m;
                    m.assignCapture(position, dest, target.getType());
                    m.setWhiteMove(fWhite);
                    moves.insert(m);
                }
                // break regardless of color
                break;
            }

            // keep going in same direction
            c += dc;
            r += dr;
        }
    }
}
