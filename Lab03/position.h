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

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
    friend class PositionTest;
public:

    //
    // Ticket 1: Core
    //

    // Copy constructor
    Position(const Position& rhs) { colRow = rhs.colRow; }

    // Default constructor sets invalid
    Position() : colRow(0xFF) {}

    // Validity checks
    bool isInvalid() const { return (colRow & 0x88) != 0 || colRow == 0xff; }
    bool isValid()   const { return !isInvalid(); }
    void setValid() { if (isInvalid()) colRow = 0x00; }
    void setInvalid() { colRow = 0xff; }

    // Comparisons
    bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
    bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
    bool operator != (const Position& rhs) const { return colRow != rhs.colRow; }

    // Assignment
    const Position& operator = (const Position& rhs)
    {
        colRow = rhs.colRow;
        return *this;
    }

    //
    // Location-based interface: location = 0..63 (row-major order)
    //
    Position(int location)
    {
        if (location < 0 || location >= 64)
            colRow = 0xFF;  // invalid
        else
        {
            int row = location / 8;
            int col = location % 8;
            colRow = (uint8_t)((col << 4) | row);
        }
    }

    int getLocation() const
    {
        if (isInvalid())
            return -1;   // invalid sentinel
        return getRow() * 8 + getCol();
    }

    void setLocation(int location)
    {
        if (location < 0 || location >= 64)
            colRow = 0xFF;  // mark invalid
        else
        {
            int row = location / 8;
            int col = location % 8;
            colRow = (uint8_t)((col << 4) | row);
        }
    }

    //
    // Row/Col-based interface
    //
    Position(int c, int r)
    {
        if (c < 0 || c >= 8 || r < 0 || r >= 8)
            colRow = 0xFF;  // invalid
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
        if (r < 0 || r >= 8)
        {
            colRow = 0xFF;  // invalid row
            return;
        }
        colRow = (uint8_t)((getCol() << 4) | r);
    }

    void setCol(int c)
    {
        if (c < 0 || c >= 8)
        {
            colRow = 0xFF;  // invalid col
            return;
        }
        colRow = (uint8_t)((c << 4) | getRow());
    }

    void set(int c, int r)
    {
        // Standard setter: invalidate if out of range
        if (c < 0 || c >= 8 || r < 0 || r >= 8)
        {
            colRow = 0xFF;  // invalid
            return;
        }
        colRow = (uint8_t)((c << 4) | r);
    }

    //
    // Ticket 2: Text-based interface
    //

    // Construct from "a1" style strings
    Position(const char* s)
    {
        if (!s || s[0] < 'a' || s[0] > 'h' || s[1] < '1' || s[1] > '8')
        {
            colRow = 0xFF;
        }
        else
        {
            int c = s[0] - 'a';
            int r = s[1] - '1';
            colRow = (uint8_t)((c << 4) | r);
        }
    }

    const Position& operator = (const char* rhs)
    {
        *this = Position(rhs);
        return *this;
    }

    const Position& operator = (const string& rhs)
    {
        *this = Position(rhs.c_str());
        return *this;
    }

    //
    // Pixels: interface to screen coordinates
    //
    int getX() const
    {
        return (int)((double)getCol() * getSquareWidth() + getSquareWidth());
    }

    int getY() const
    {
        return (int)((double)getRow() * getSquareHeight() + getSquareHeight());
    }

    void setXY(double x, double y)
    {
        // Compute column using board padding convention (-1)
        int c = (int)(x / getSquareWidth()) - 1;

        // If column is off-board, whole position is invalid
        if (c < 0 || c >= 8)
        {
            colRow = 0xFF;
            return;
        }

        // Compute tentative row from pixel y (top-origin to board rows)
        int r = 8 - (int)(y / getSquareHeight());

        // If Y is out of range, keep the computed column but mark the row nibble invalid (0xF)
        if (r < 0 || r > 7)
        {
            colRow = (uint8_t)((c << 4) | 0x0F); // e.g., col=3 -> 0x3F
            return;
        }

        // Normal in-bounds case
        set(c, r);
    }

    double getSquareWidth()  const { return squareWidth; }
    double getSquareHeight() const { return squareHeight; }
    void setBoardWidthHeight(int widthBoard, int heightBoard)
    {
        if (widthBoard < 0 || heightBoard < 0)
            return;
        squareWidth = (double)widthBoard / 10.0; // 8 squares + 2 spaces
        squareHeight = (double)heightBoard / 10.0;
    }

    //
    // Ticket 3: Movement with deltas
    //

    // Construct by offsetting another position
    Position(const Position& rhs, const Delta& delta)
    {
        int newCol = rhs.getCol() + delta.dCol;
        int newRow = rhs.getRow() + delta.dRow;
        set(newCol, newRow);
    }

    void adjustRow(int dRow)
    {
        set(getCol(), getRow() + dRow);
    }

    void adjustCol(int dCol)
    {
        set(getCol() + dCol, getRow());
    }

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


ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);
