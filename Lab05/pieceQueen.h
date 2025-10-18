/***********************************************************************
 * Header File:
 *    QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The queen piece
 ************************************************************************/

#pragma once

#include "piece.h"
#include "position.h"
#include <set>

class Queen : public Piece
{
public:
    // Constructor
    Queen(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
    Queen(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}

    // Overridden behavior
    PieceType getType() const { return QUEEN; }
    void display(ogstream* pgout) const;
    void getMoves(std::set<Move>& moves, const Board& board) const; // no override!
};
