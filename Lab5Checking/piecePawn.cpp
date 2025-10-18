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

    // 4. En Passant
    for (int dc = -1; dc <= 1; dc += 2)
    {
        Position side(col + dc, row);
        Position captureSq(col + dc, row + dir);

        if (!side.isValid() || !captureSq.isValid())
            continue;

        // look at adjacent pawn using safe getter
        const Piece* adjPiece = board.getPiecePtr(side.getCol(), side.getRow());
        const Piece& destPiece = board[captureSq];

        // must be pawn of opposite color
        const Pawn* adjPawn = dynamic_cast<const Pawn*>(adjPiece);
        if (!adjPawn)
            continue;

        if (adjPawn->getType() == PAWN && adjPawn->isWhite() != isWhite())
        {
            // must have just moved two squares
            if (adjPawn->getNumMoves() == 1 &&
                adjPawn->getLastMove() == board.getNumMoves() - 1)
            {
                // ensure the capture square is empty
                if (destPiece.getType() == SPACE)
                {
                    Move m;
                    m.assignCapture(position, captureSq, PAWN);
                    m.setWhiteMove(isWhite());
                    m.setEnPassant(true);    // mark special capture
                    moves.insert(m);
                }
            }
        }
    }

    // 5. Promotion
    int finalRank = isWhite() ? 7 : 0;
    if (row + dir == finalRank)
    {
        // Forward promotion (if empty)
        Position promoForward(col, row + dir);
        if (promoForward.isValid() && board[promoForward].getType() == SPACE)
        {
            Move m;
            m.assignSimple(position, promoForward);
            m.setWhiteMove(isWhite());
            m.setPromotion(true);
            moves.insert(m);
        }

        // Diagonal promotions (captures)
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
                m.setPromotion(true);
                moves.insert(m);
            }
        }
    }
}
