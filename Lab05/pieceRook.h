/***********************************************************************
 * Header File:
 *    ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The ROOK class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * ROOK
  * The rook piece (moves horizontally or vertically)
  ***************************************************/
class Rook : public Piece
{
public:
    // Constructors
    Rook(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
    Rook(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
    ~Rook() {}

    // Type
    virtual PieceType getType() const { return ROOK; }

    // Display
    virtual void display(ogstream* pgout) const;

    // Moves
    virtual void getMoves(set<Move>& moves, const Board& board) const;
};
