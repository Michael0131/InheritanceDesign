/***********************************************************************
 * Source File:
 *    PIECE
 * Author:
 *    <your name here>
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#include "position.h"  // for POSITION
#include "piece.h"     // for all the PIECE class definitions
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "board.h"     // for BOARD
#include "uiDraw.h"    // for draw*()
#include <cassert>     // because we are paranoid
using namespace std;


/************************************************
 * PIECE : ASSIGN
 ***********************************************/
const Piece& Piece::operator = (const Piece& rhs)
{
	if (this != &rhs)
	{
		this->fWhite = rhs.fWhite;
		this->lastMove = rhs.lastMove;
		this->nMoves = rhs.nMoves;
		this->position = rhs.position;
	}
	return *this;
}

/************************************************
 * PIECE : GET MOVES
 * Iterate through the moves decorator to allow a piece to move
 ***********************************************/
void Piece::getMoves(set <Move>& movesSet, const Board& board) const
{

}


/**********************************************
 * PIECE : CONSTRUCTORS / DESTRUCTOR
 **********************************************/
Piece::Piece(const Position& pos, bool isWhite)
{
	position = pos;
	fWhite = isWhite;
	nMoves = 0;
	lastMove = 0;
}

Piece::Piece(int c, int r, bool isWhite)
{
	position = Position(c, r);
	fWhite = isWhite;
	nMoves = 0;
	lastMove = 0;
}

Piece::Piece(const Piece& piece)
{
	position = piece.position;
	fWhite = piece.fWhite;
	nMoves = piece.nMoves;
	lastMove = piece.lastMove;
}

Piece::~Piece()
{
	// nothing to clean up
}

/**********************************************
 * PIECE : SET LAST MOVE
 **********************************************/
void Piece::setLastMove(int currentMove)
{
	lastMove = currentMove;
	nMoves++;
}


/************************************************
 * OPERATOR ==
 * Compare piece type to a given piece.
 ***********************************************/
bool Piece::operator==(PieceType pt) const
{
	return getType() == pt;
}

/************************************************
 * OPERATOR !=
 * Compare piece is not of the same type to a given piece.
 ***********************************************/
bool Piece::operator!=(PieceType pt) const
{
	return getType() != pt;
}

/************************************************
 * IS WHITE
 * Check to see if piece is white.
 ***********************************************/
bool Piece::isWhite() const
{
	return fWhite;
}

/************************************************
 * IS MOVED
 * Check to see if piece has moved at least 1 in the game.
 ***********************************************/
bool Piece::isMoved() const
{
	return nMoves > 0;
}

/************************************************
 * GET N MOVES
 * get the number of moves
 ***********************************************/
int Piece::getNMoves() const
{
	return nMoves;
}

/************************************************
 * DECREMENT NUMBER OF MOVES
 ***********************************************/
void Piece::decrementNMoves()
{
	if (nMoves > 0)
	{
		nMoves--;
	}
}

/************************************************
 * GET POSITION
 ***********************************************/
const Position& Piece::getPosition() const
{
	return position;
}

/************************************************
 * JUST MOVED
 ***********************************************/
bool Piece::justMoved(int currentMove) const
{
	return lastMove + 1 == currentMove;
}

