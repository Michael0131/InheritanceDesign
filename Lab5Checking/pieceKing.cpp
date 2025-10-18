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

 /***************************************************
  * KING : DISPLAY
  ***************************************************/
void King::display(ogstream* pgout) const
{
    pgout->drawKing(position, !isWhite());
}

/***************************************************
 * KING : GET MOVES
 * Return all possible one-square moves and valid castling options.
 ***************************************************/
void King::getMoves(set<Move>& moves, const Board& board) const
{
    static const int MOVE_OFFSETS[8][2] = {
        {  1,  0 }, {  1,  1 }, {  0,  1 }, { -1,  1 },
        { -1,  0 }, { -1, -1 }, {  0, -1 }, {  1, -1 }
    };

    int col = position.getCol();
    int row = position.getRow();

    /* ------------------------------------------
     * 1️⃣  Regular single-square king moves
     * ------------------------------------------ */
    for (auto& offset : MOVE_OFFSETS)
    {
        Position destination(col + offset[0], row + offset[1]);
        if (!destination.isValid())
            continue;

        const Piece& occupant = board[destination];

        // cannot capture friendly pieces
        if (occupant.getType() != SPACE && occupant.isWhite() == fWhite)
            continue;

        Move move;
        if (occupant.getType() == SPACE)
            move.assignSimple(position, destination);
        else
            move.assignCapture(position, destination, occupant.getType());

        move.setWhiteMove(fWhite);
        moves.insert(move);
    }

    /* ------------------------------------------
     * 2️⃣  Castling (only if king hasn’t moved)
     * ------------------------------------------ */
    if (isMoved())
        return;

    // === King-side castle ===
    {
        Position rookPosition(7, row);
        const Piece& rook = board[rookPosition];

        if (rook.getType() == ROOK && rook.isWhite() == fWhite && !rook.isMoved())
        {
            bool isPathClearForCastle = true;

            // Check all squares between king and rook (f1, g1 or f8, g8)
            for (int c = col + 1; c < 7; ++c)
            {
                if (board[Position(c, row)].getType() != SPACE)
                {
                    isPathClearForCastle = false;
                    break;
                }
            }

            if (isPathClearForCastle)
            {
                Move castleMove;
                castleMove.assignCastleKing(position, Position(col + 2, row));
                castleMove.setWhiteMove(fWhite);
                moves.insert(castleMove);
            }
        }
    }

    // === Queen-side castle ===
    {
        Position rookPosition(0, row);
        const Piece& rook = board[rookPosition];

        if (rook.getType() == ROOK && rook.isWhite() == fWhite && !rook.isMoved())
        {
            bool isPathClearForCastle = true;

            // Check all squares between king and rook (b1, c1, d1 or b8, c8, d8)
            for (int c = col - 1; c > 0; --c)
            {
                if (board[Position(c, row)].getType() != SPACE)
                {
                    isPathClearForCastle = false;
                    break;
                }
            }

            if (isPathClearForCastle)
            {
                Move castleMove;
                castleMove.assignCastleQueen(position, Position(col - 2, row));
                castleMove.setWhiteMove(fWhite);
                moves.insert(castleMove);
            }
        }
    }
}
