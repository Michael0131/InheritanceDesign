/***********************************************************************
 * Header File:
 *    PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The pawn class
 ************************************************************************/

#pragma once

#include "piece.h"
#include "move.h"
#include "board.h"
#include "uiDraw.h"
#include <set>

class Pawn : public Piece
{
public:
    Pawn() : Piece(Position(), true) {}
    Pawn(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}

    PieceType getType() const override { return PAWN; }
    void display(ogstream* pgout) const override
    {
        pgout->drawPawn(position, !isWhite());
    }

    void getMoves(std::set<Move>& moves, const Board& board) const;
};
