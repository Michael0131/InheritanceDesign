/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#include "position.h"
#include <iostream>
using namespace std;

/******************************************
 * POSITION INSERTION OPERATOR
 ******************************************/
ostream& operator<<(ostream& out, const Position& rhs)
{
    if (rhs.isInvalid())
        out << "--";
    else
        out << (char)('a' + rhs.getCol())
        << (char)('1' + rhs.getRow());
    return out;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream& operator>>(istream& in, Position& rhs)
{
    string s;
    in >> s;

    if (s.size() == 2 && s[0] >= 'a' && s[0] <= 'h' &&
        s[1] >= '1' && s[1] <= '8')
        rhs.set(s[0] - 'a', s[1] - '1');
    else
        rhs.setInvalid();

    return in;
}
