/***********************************************************************
 * Source File:
 *    PIECE ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The Rook class implementation
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"

 /**********************************************
  * ROOK : DISPLAY
  **********************************************/
void Rook::display(ogstream* pgout) const
{
    pgout->drawRook(position, !isWhite());
}

/**********************************************
 * ROOK : GET MOVES
 **********************************************/
void Rook::getMoves(set<Move>& moves, const Board& board) const
{
    static const Delta directions[4] =
    {
       {  1,  0 },  // up
       { -1,  0 },  // down
       {  0,  1 },  // right
       {  0, -1 }   // left
    };

    for (auto d : directions)
    {
        Position dest = position + d;

        while (dest.isValid())
        {
            const Piece* target = board.board[dest.getCol()][dest.getRow()];

            // Empty square
            if (target == nullptr)
            {
                Move m;
                m.assignSimple(position, dest);
                m.setWhiteMove(fWhite);
                moves.insert(m);
            }
            else
            {
                // Friendly piece — stop, no move
                if (target->isWhite() == fWhite)
                    break;

                // Enemy piece — capture, then stop
                Move m;
                m.assignCapture(position, dest, target->getType());
                m.setWhiteMove(fWhite);
                moves.insert(m);
                break;
            }

            dest += d;
        }
    }
}

