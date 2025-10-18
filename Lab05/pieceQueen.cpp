/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The queen piece implementation
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"

 /***************************************************
  * QUEEN : DISPLAY
  * Draw the queen on the board.
  ***************************************************/
void Queen::display(ogstream* pgout) const
{
    pgout->drawQueen(position, !isWhite());
}

/***************************************************
 * QUEEN : GET MOVES
 * Return all possible moves for the queen.
 ***************************************************/
void Queen::getMoves(set<Move>& moves, const Board& board) const
{
    // Directions (8): rook + bishop
    static const int DIRECTIONS[8][2] =
    {
        {  1,  0 },  // right
        { -1,  0 },  // left
        {  0,  1 },  // up
        {  0, -1 },  // down
        {  1,  1 },  // up-right
        { -1,  1 },  // up-left
        {  1, -1 },  // down-right
        { -1, -1 }   // down-left
    };

    int c0 = position.getCol();
    int r0 = position.getRow();

    // Scan each direction until blocked
    for (auto& dir : DIRECTIONS)
    {
        int c = c0 + dir[0];
        int r = r0 + dir[1];

        while (Position(c, r).isValid())
        {
            Position dest(c, r);
            const Piece& target = board[dest];

            // same color piece = stop
            if (target.getType() != SPACE && target.isWhite() == fWhite)
                break;

            Move m;
            if (target.getType() == SPACE)
                m.assignSimple(position, dest);
            else
            {
                m.assignCapture(position, dest, target.getType());
                moves.insert(m);
                break; // stop after capture
            }

            m.setWhiteMove(fWhite);
            moves.insert(m);

            // advance further in this direction
            c += dir[0];
            r += dir[1];
        }
    }
}
