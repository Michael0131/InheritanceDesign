/***********************************************************************
 * Header File:
 *    KING
 * Author:
 *    <your name here>
 * Summary:
 *    The King class
 ************************************************************************/

#pragma once

#include "piece.h"
#include <set>

class King : public Piece
{
public:
	King(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
	PieceType getType() const override { return KING; }
	void display(ogstream* pgout) const override;
	void getMoves(std::set<Move>& moves, const Board& board) const override;
};
