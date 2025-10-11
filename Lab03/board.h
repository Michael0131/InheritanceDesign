/***********************************************************************
 * Header File:
 *    BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and the state of the board
 ************************************************************************/

#pragma once

#include <cassert>
#include "move.h"   // Because we return a set of Move

class ogstream;
class TestPawn;
class TestKnight;
class TestBishop;
class TestRook;
class TestQueen;
class TestKing;
class TestBoard;
class Position;
class Piece;

/***************************************************
 * BOARD
 * The game board
 **************************************************/
class Board
{
    friend TestPawn;
    friend TestKnight;
    friend TestBishop;
    friend TestRook;
    friend TestQueen;
    friend TestKing;
    friend TestBoard;

public:
    Board();
    virtual ~Board();

    // getters
    virtual int  getCurrentMove() const { return numMoves; }
    virtual bool whiteTurn()      const { return (numMoves % 2) == 0; }
    virtual void display(const Position& posHover, const Position& posSelect) const {}

    // fetch
    virtual const Piece& operator [] (const Position& pos) const;

    // setters
    virtual void move(const Move& move) { ++numMoves; }
    virtual Piece& operator [] (const Position& pos);

protected:
    int numMoves{ 0 };
    Piece* board[8][8];    // the board of chess pieces
};

/***************************************************
 * BOARD DUMMY BOARD
 * A board double that does nothing but assert. Will need this for unit tests.
 **************************************************/
class BoardDummy : public Board
{
    friend TestBoard;
public:
    BoardDummy() {}
    ~BoardDummy() {}

    void display(const Position& posHover,
        const Position& posSelect) const {
        assert(false);
    }
    void move(const Move& move) { assert(false); }
    int  getCurrentMove() const { assert(false); return 0; }
    bool whiteTurn()      const { assert(false); return false; }
    Piece& operator [] (const Position& pos)
    {
        assert(false);
        throw true;
    }
    const Piece& operator [] (const Position& pos) const
    {
        assert(false);
        throw true;
    }
};

/***************************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 **************************************************/
class BoardEmpty : public BoardDummy
{
    friend TestBoard;
public:
    Piece* pSpace;

    BoardEmpty();
    ~BoardEmpty();

    const Piece& operator [] (const Position& pos) const
    {
        // Note: these tests pass a Position subclass that guarantees
        // 0<=col,row<=7 via virtual getters, so just bounds-check.
        int c = pos.getCol();
        int r = pos.getRow();
        if (c < 0 || c > 7 || r < 0 || r > 7)
            return *pSpace;

        if (board[c][r])
            return *(board[c][r]);
        else
            return *pSpace;
    }
};
