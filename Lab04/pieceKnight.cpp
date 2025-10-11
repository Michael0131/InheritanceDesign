/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The knight class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>


/***************************************************
  * KNIGHT : DISPLAY
  * Draw the knight on the board.
  ***************************************************/
void Knight::display(ogstream* pgout) const
{
    if (pgout)
        pgout->drawKnight(position, fWhite);
}



/**********************************************
 * KNIGHT : GET MOVES
 * Return all possible L-shaped moves for the knight.
 *********************************************/
 /**********************************************
  * KNIGHT : GET MOVES
  * Return all possible L-shaped moves for the knight.
  *********************************************/
void Knight::getMoves(set<Move>& moves, const Board& board) const
{
    static const int OFFSETS[8][2] = {
        {  1,  2 }, {  2,  1 },
        {  2, -1 }, {  1, -2 },
        { -1, -2 }, { -2, -1 },
        { -2,  1 }, { -1,  2 }
    };

    int c0 = position.getCol();
    int r0 = position.getRow();

    for (int i = 0; i < 8; ++i)
    {
        int c = c0 + OFFSETS[i][0];
        int r = r0 + OFFSETS[i][1];
        Position dest(c, r);
        int testColVal = dest.getCol();
        int testRowVal = dest.getRow();
        if (!dest.isValid())
            continue;

        const Piece& target = board[dest.getLocation()];
       
        if (target.getType() != SPACE && target.isWhite() == fWhite)
            continue;

        Move m;
        if (target.getType() == SPACE)
            m.assignSimple(position, dest);
        else
            m.assignCapture(position, dest, target.getType());

        m.setWhiteMove(fWhite);
        moves.insert(m);
        std::cout << moves.size();

    }
    

}

