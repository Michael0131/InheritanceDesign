/***********************************************************************
 * Header File:
 *    BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The Bishop class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * BISHOP
  * The Bishop piece
  ***************************************************/
class Bishop : public Piece
{
public:
    // Constructors
    Bishop(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
    Bishop(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
    ~Bishop() {}

    PieceType getType() const { return BISHOP; }
    void getMoves(set<Move>& moves, const Board& board) const;
    void display(ogstream* pgout) const;
};
