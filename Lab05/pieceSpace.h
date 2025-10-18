/***********************************************************************
 * Header File:
 *    SPACE
 * Author:
 *    <your name here> 
 * Summary:
 *    The space
 ************************************************************************/

#pragma once

#include "piece.h"

class TestSpace;

 /***************************************************
  * SPACES
  * A space is a trivial piece
  ***************************************************/
class Space : public Piece
{
	friend TestSpace;
public:
	Space(int c, int r) : Piece(Position(c, r), true) {}
	~Space() {}
	PieceType getType() const override { return SPACE; }
	void display(ogstream* pgout) const override {}
};