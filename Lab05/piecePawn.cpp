/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The pawn class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "move.h"
#include "uiDraw.h"
#include <cassert>

 /***************************************************
  * PAWN : GET MOVES
  * Return all possible moves for the pawn
  ***************************************************/
void Pawn::getMoves(std::set<Move>& moves, const Board& board) const
{
    int dir = (isWhite() ? 1 : -1);   // white goes up, black down
    int row = position.getRow();
    int col = position.getCol();

    // 1. Forward move
    Position oneForward(col, row + dir);
    if (oneForward.isValid() && board[oneForward].getType() == SPACE)
    {
        Move m;
        m.assignSimple(position, oneForward);
        m.setWhiteMove(isWhite());
        moves.insert(m);

        // 2. Two-square move (only from starting rank)
        bool startRow = (isWhite() && row == 1) || (!isWhite() && row == 6);
        if (startRow)
        {
            Position twoForward(col, row + 2 * dir);
            if (twoForward.isValid() && board[twoForward].getType() == SPACE)
            {
                Move m2;
                m2.assignSimple(position, twoForward);
                m2.setWhiteMove(isWhite());
                moves.insert(m2);
            }
        }
    }

    // 3. Diagonal captures
    for (int dc = -1; dc <= 1; dc += 2)
    {
        Position diag(col + dc, row + dir);
        if (!diag.isValid())
            continue;

        const Piece& target = board[diag];
        if (target.getType() != SPACE && target.isWhite() != isWhite())
        {
            Move m;
            m.assignCapture(position, diag, target.getType());
            m.setWhiteMove(isWhite());
            moves.insert(m);
        }
    }

    // 4. En passant — skipped (depends on Board::getLastMove)
    // Safe placeholder, no errors if Board doesn’t track move history.
    // Future extension could add logic here when Board supports it.
}
