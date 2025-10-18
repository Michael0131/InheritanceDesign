/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default
const int OFFSET_BOARD = 50;   // boarder between the board and the edge of screen

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
    int dRow;
    int dCol;
};

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1,  0 };
const Delta SUB_C = { 0, -1 };


class PositionTest;
class TestKnight;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
    friend class PositionTest;
    friend class TestKnight;
public:
    // Copy constructor
    Position(const Position& rhs) { colRow = rhs.colRow; }

    // Default constructor (invalid)
    Position() : colRow(0xFF) {}

    // Validity
    bool isInvalid() const
    {
        if (colRow == 0xFF)
            return true;

        int c = (colRow & 0xF0) >> 4;
        int r = (colRow & 0x0F);
        return (c < 0 || c >= 8 || r < 0 || r >= 8);
    }
    bool isValid()   const { return !isInvalid(); }
    void setValid() { if (isInvalid()) colRow = 0x00; }
    void setInvalid() { colRow = 0xFF; }

    // Comparison
    bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
    bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
    bool operator != (const Position& rhs) const { return colRow != rhs.colRow; }

    // Assignment
    const Position& operator = (const Position& rhs)
    {
        colRow = rhs.colRow;
        return *this;
    }

    // Location-based
    Position(int location)
    {
        if (location < 0 || location >= 64)
            colRow = 0xFF;
        else
        {
            int r = location / 8;
            int c = location % 8;
            colRow = (uint8_t)((c << 4) | r);
        }
    }

    int getLocation() const
    {
        if (isInvalid()) return -1;
        return getRow() * 8 + getCol();
    }

    void setLocation(int location)
    {
        if (location < 0 || location >= 64)
            colRow = 0xFF;
        else
        {
            int r = location / 8;
            int c = location % 8;
            colRow = (uint8_t)((c << 4) | r);
        }
    }

    // Row / Col
    Position(int c, int r)
    {
        if (c < 0 || c >= 8 || r < 0 || r >= 8)
            colRow = 0xFF;
        else
            colRow = (uint8_t)((c << 4) | r);
    }

    virtual int getCol() const
    {
        if (isInvalid()) return -1;
        return (colRow & 0xF0) >> 4;
    }

    virtual int getRow() const
    {
        if (isInvalid()) return -1;
        return (colRow & 0x0F);
    }

    void setRow(int r)
    {
        if (r < 0 || r >= 8) { colRow = 0xFF; return; }
        colRow = (uint8_t)((getCol() << 4) | r);
    }

    void setCol(int c)
    {
        if (c < 0 || c >= 8) { colRow = 0xFF; return; }
        colRow = (uint8_t)((c << 4) | getRow());
    }

    void set(int c, int r)
    {
        if (c < 0 || c >= 8 || r < 0 || r >= 8)
            colRow = 0xFF;
        else
            colRow = (uint8_t)((c << 4) | r);
    }

    // Text form
    Position(const char* s)
    {
        if (!s || s[0] < 'a' || s[0] > 'h' || s[1] < '1' || s[1] > '8')
            colRow = 0xFF;
        else
        {
            int c = s[0] - 'a';
            int r = s[1] - '1';
            colRow = (uint8_t)((c << 4) | r);
        }
    }

    const Position& operator=(const char* rhs)
    {
        *this = Position(rhs);
        return *this;
    }

    const Position& operator=(const string& rhs)
    {
        *this = Position(rhs.c_str());
        return *this;
    }

    // Pixels
    int getX() const { return (int)((double)getCol() * getSquareWidth() + getSquareWidth()); }
    int getY() const { return (int)((double)getRow() * getSquareHeight() + getSquareHeight()); }

    void setXY(double x, double y)
    {
        int c = (int)(x / getSquareWidth()) - 1;
        if (c < 0 || c >= 8)
        {
            colRow = 0xFF;
            return;
        }

        int r = 8 - (int)(y / getSquareHeight());
        if (r < 0 || r > 7)
        {
            colRow = (uint8_t)((c << 4) | 0x0F);
            return;
        }

        set(c, r);
    }

    double getSquareWidth()  const { return squareWidth; }
    double getSquareHeight() const { return squareHeight; }
    void setBoardWidthHeight(int widthBoard, int heightBoard)
    {
        if (widthBoard < 0 || heightBoard < 0)
            return;
        squareWidth = (double)widthBoard / 10.0;
        squareHeight = (double)heightBoard / 10.0;
    }

    // Delta movement
    Position(const Position& rhs, const Delta& delta)
    {
        int nc = rhs.getCol() + delta.dCol;
        int nr = rhs.getRow() + delta.dRow;
        set(nc, nr);
    }

    void adjustRow(int dRow) { set(getCol(), getRow() + dRow); }
    void adjustCol(int dCol) { set(getCol() + dCol, getRow()); }

    const Position& operator += (const Delta& rhs)
    {
        set(getCol() + rhs.dCol, getRow() + rhs.dRow);
        return *this;
    }

    Position operator + (const Delta& rhs) const
    {
        return Position(getCol() + rhs.dCol, getRow() + rhs.dRow);
    }

private:
    void set(uint8_t colRowNew) { colRow = colRowNew; }

    uint8_t colRow;
    static double squareWidth;
    static double squareHeight;
};


// Stream operators
ostream& operator<<(ostream& out, const Position& pos);
istream& operator>>(istream& in, Position& pos);
