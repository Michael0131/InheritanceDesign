/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type

class TestMove;
class TestBoard;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
	enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

	friend TestMove;
	friend TestBoard;

	// constructors
	Move();
	Move(const Position& src, const Position& dst, MoveType mt = MOVE);

	//
	// Ticket 4: assignment helpers
	//
	void assign(const Position& src, const Position& dst, MoveType mt = MOVE);
	void assignSimple(const Position& src, const Position& dst);
	void assignCapture(const Position& src, const Position& dst, PieceType cap);
	void assignEnPassant(const Position& src, const Position& dst);
	void assignCastleKing(const Position& src, const Position& dst);
	void assignCastleQueen(const Position& src, const Position& dst);

	//
	// Ticket 5: string I/O + comparisons
	//
	void read(const std::string& s);       // parse from string
	std::string getText() const;           // output as string

	bool operator==(const Move& rhs) const;
	bool operator!=(const Move& rhs) const;
	bool operator<(const Move& rhs) const;

private:
	//
	// Piece ? letter conversions
	//
	char letterFromPieceType(PieceType pt) const;
	PieceType pieceTypeFromLetter(char letter) const;

	//
	// Data members
	//
	Position  source;    // where the move originated from
	Position  dest;      // where the move finished
	PieceType promote;   // piece to be promoted to
	PieceType capture;   // did a capture happen this move?
	MoveType  moveType;  // what type of move is this?
	bool      isWhite;   // whose turn is it anyway?
	std::string text;    // what is the textual version of the move?
};
