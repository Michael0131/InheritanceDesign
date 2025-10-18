/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include <cassert>
#include <iostream>
#include <cctype>
using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move()
{
    source.setInvalid();
    dest.setInvalid();
    promote = SPACE;
    capture = SPACE;
    moveType = MOVE_ERROR;
    isWhite = true;
    text = "";
}

/***************************************************
 * MOVE : CONSTRUCTOR WITH POSITIONS
 ***************************************************/
Move::Move(const Position& src, const Position& dst, MoveType mt)
{
    assign(src, dst, mt);
}

/***************************************************
 * ASSIGN
 ***************************************************/
void Move::assign(const Position& src, const Position& dst, MoveType mt)
{
    source = src;
    dest = dst;
    moveType = mt;
    promote = SPACE;
    capture = SPACE;
    text = "";
    
    
    if (mt == ENPASSANT)
    {
        enPassant = true;
    }
}

/***************************************************
 * ASSIGN SIMPLE
 ***************************************************/
void Move::assignSimple(const Position& src, const Position& dst)
{
    assign(src, dst, MOVE);
}

/***************************************************
 * ASSIGN CAPTURE
 ***************************************************/
void Move::assignCapture(const Position& src, const Position& dst, PieceType cap)
{
    assign(src, dst, MOVE);
    capture = cap;
}

/***************************************************
 * ASSIGN EN PASSANT
 ***************************************************/
void Move::assignEnPassant(const Position& src, const Position& dst)
{
    assign(src, dst, ENPASSANT);
    capture = PAWN;
}

/***************************************************
 * ASSIGN CASTLE KING
 ***************************************************/
void Move::assignCastleKing(const Position& src, const Position& dst)
{
    assign(src, dst, CASTLE_KING);
    capture = SPACE;
}

/***************************************************
 * ASSIGN CASTLE QUEEN
 ***************************************************/
void Move::assignCastleQueen(const Position& src, const Position& dst)
{
    assign(src, dst, CASTLE_QUEEN);
    capture = SPACE;
}

/***************************************************
 * OPERATOR ==
 ***************************************************/
bool Move::operator==(const Move& rhs) const
{
    return (source == rhs.source &&
        dest == rhs.dest &&
        moveType == rhs.moveType &&
        capture == rhs.capture &&
        promote == rhs.promote);
}

/***************************************************
 * OPERATOR !=
 ***************************************************/
bool Move::operator!=(const Move& rhs) const
{
    return !(*this == rhs);
}

/***************************************************
 * OPERATOR <
 * Needed for std::set sorting (by destination location).
 ***************************************************/
bool Move::operator<(const Move& rhs) const
{
    return dest < rhs.dest;
}

/***************************************************
 * LETTER FROM PIECE TYPE
 ***************************************************/
char Move::letterFromPieceType(PieceType pt) const
{
    switch (pt)
    {
    case SPACE:  return ' ';
    case PAWN:   return 'p';
    case BISHOP: return 'b';
    case KNIGHT: return 'n';
    case ROOK:   return 'r';
    case QUEEN:  return 'q';
    case KING:   return 'k';
    default:     return '?';
    }
}

/***************************************************
 * PIECE TYPE FROM LETTER
 ***************************************************/
PieceType Move::pieceTypeFromLetter(char letter) const
{
    switch (tolower(letter))
    {
    case ' ': return SPACE;
    case 'p': return PAWN;
    case 'b': return BISHOP;
    case 'n': return KNIGHT;
    case 'r': return ROOK;
    case 'q': return QUEEN;
    case 'k': return KING;
    default:  return SPACE;
    }
}

/***************************************************
 * READ FROM STRING
 ***************************************************/
void Move::read(const string& s)
{
    text = s;
    source.setInvalid();
    dest.setInvalid();
    promote = SPACE;
    capture = SPACE;
    moveType = MOVE;

    if (s.size() < 4)
    {
        moveType = MOVE_ERROR;
        return;
    }

    // interpret “e2e4” style moves
    source = Position(s[0] - 'a', s[1] - '1');
    dest = Position(s[2] - 'a', s[3] - '1');

    if (s.size() == 5)
    {
        char c = s[4];
        switch (c)
        {
        case 'E': moveType = ENPASSANT;    capture = PAWN;  break;
        case 'c': moveType = CASTLE_KING;  capture = SPACE; break;
        case 'C': moveType = CASTLE_QUEEN; capture = SPACE; break;
        default:  capture = pieceTypeFromLetter(c);         break;
        }
    }
}

/***************************************************
 * CONVERT TO STRING
 ***************************************************/
string Move::getText() const
{
    if (!source.isValid() || !dest.isValid())
        return "";

    string s;
    s.push_back('a' + source.getCol());
    s.push_back('1' + source.getRow());
    s.push_back('a' + dest.getCol());
    s.push_back('1' + dest.getRow());

    switch (moveType)
    {
    case ENPASSANT:
        s.push_back('E');
        break;
    case CASTLE_KING:
        s.push_back('c');
        break;
    case CASTLE_QUEEN:
        s.push_back('C');
        break;
    default:
        if (capture != SPACE)
            s.push_back(letterFromPieceType(capture));
        break;
    }

    return s;
}
