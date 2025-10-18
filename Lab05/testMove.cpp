/***********************************************************************
 * Header File:
 *    TEST MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    test the Move class
 ************************************************************************/

#include "testMove.h"
#include "move.h"
#include <cassert>
using namespace std;

/*************************************
 * Constructor : default
 * Input:
 * Output: source=INVALID
 *         dest  =INVALID
 **************************************/
void TestMove::constructor_default()
{
	Move m;
	assertUnit(!m.source.isValid());
	assertUnit(!m.dest.isValid());
	assertUnit(m.moveType == Move::MOVE_ERROR);
	assertUnit(m.capture == SPACE);
	assertUnit(m.promote == SPACE);
}

/*************************************
 * CONSTRUCTOR : standard string move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::constructString_simple()
{
	Move m;
	m.read("e5e6");

	assertUnit(m.source.getCol() == 4);
	assertUnit(m.source.getRow() == 4);
	assertUnit(m.dest.getCol() == 4);
	assertUnit(m.dest.getRow() == 5);
	assertUnit(m.moveType == Move::MOVE);
}

/*************************************
 * READ simple move
 * Input:  e5d6
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 **************************************/
void TestMove::read_simple()
{
	Move m;
	m.read("e5d6");

	assertUnit(m.source.getCol() == 4);
	assertUnit(m.source.getRow() == 4);
	assertUnit(m.dest.getCol() == 3);
	assertUnit(m.dest.getRow() == 5);
	assertUnit(m.moveType == Move::MOVE);
	assertUnit(m.capture == SPACE);
}

/*************************************
 * READ capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::read_capture()
{
	Move m;
	m.read("e5d6r");

	assertUnit(m.source.getCol() == 4);
	assertUnit(m.source.getRow() == 4);
	assertUnit(m.dest.getCol() == 3);
	assertUnit(m.dest.getRow() == 5);
	assertUnit(m.capture == ROOK);
	assertUnit(m.moveType == Move::MOVE);
}

/*************************************
 * READ enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::read_enpassant()
{
	Move m;
	m.read("e5f6E");

	assertUnit(m.source.getCol() == 4);
	assertUnit(m.source.getRow() == 4);
	assertUnit(m.dest.getCol() == 5);
	assertUnit(m.dest.getRow() == 5);
	assertUnit(m.moveType == Move::ENPASSANT);
	assertUnit(m.capture == PAWN);
}

/*************************************
 * READ king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::read_castleKing()
{
	Move m;
	m.read("e1g1c");

	assertUnit(m.source.getCol() == 4);
	assertUnit(m.source.getRow() == 0);
	assertUnit(m.dest.getCol() == 6);
	assertUnit(m.dest.getRow() == 0);
	assertUnit(m.moveType == Move::CASTLE_KING);
}

/*************************************
 * READ queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::read_castleQueen()
{
	Move m;
	m.read("e1c1C");

	assertUnit(m.source.getCol() == 4);
	assertUnit(m.source.getRow() == 0);
	assertUnit(m.dest.getCol() == 2);
	assertUnit(m.dest.getRow() == 0);
	assertUnit(m.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * ASSIGN simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::assign_simple()
{
	Move m;
	Position src(4, 4);
	Position dst(4, 5);
	m.assignSimple(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::MOVE);
}

/*************************************
 * ASSIGN capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::assign_capture()
{
	Move m;
	Position src(4, 4);
	Position dst(3, 5);
	m.assignCapture(src, dst, ROOK);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.capture == ROOK);
	assertUnit(m.moveType == Move::MOVE);
}

/*************************************
 * ASSIGN enpassant move
 * Input:  e5d6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::assign_enpassant()
{
	Move m;
	Position src(4, 4);
	Position dst(5, 5);
	m.assignEnPassant(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::ENPASSANT);
	assertUnit(m.capture == PAWN);
}

/*************************************
 * ASSIGN king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::assign_castleKing()
{
	Move m;
	Position src(4, 0);
	Position dst(6, 0);
	m.assignCastleKing(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::CASTLE_KING);
}

/*************************************
 * ASSIGN queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::assign_castleQueen()
{
	Move m;
	Position src(4, 0);
	Position dst(2, 0);
	m.assignCastleQueen(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * GET TEXT simple move
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 * Input:  e5e6
 **************************************/
void TestMove::getText_simple()
{
	Move m;
	Position src(4, 4);
	Position dst(4, 5);
	m.assignSimple(src, dst);
	assertUnit(m.getText() == "e5e6");
}

/*************************************
 * GET TEXT capture
 * Input : source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 * Input:  e5d6r
 **************************************/
void TestMove::getText_capture()
{
	Move m;
	Position src(4, 4);
	Position dst(3, 5);
	m.assignCapture(src, dst, ROOK);
	assertUnit(m.getText() == "e5d6r");
}

/*************************************
 * GET TEXT en passant
 * Input : source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 * Input:  e5f6E
 **************************************/
void TestMove::getText_enpassant()
{
	Move m;
	Position src(4, 4);
	Position dst(5, 5);
	m.assignEnPassant(src, dst);
	assertUnit(m.getText() == "e5f6E");
}

/*************************************
 * GET TEXT king side castle
 * Input : source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 * Input:  e1g1c
 **************************************/
void TestMove::getText_castleKing()
{
	Move m;
	Position src(4, 0);
	Position dst(6, 0);
	m.assignCastleKing(src, dst);
	assertUnit(m.getText() == "e1g1c");
}

/*************************************
 * GET TEXT queen side castle
 * Input : source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 * Input:  e1c1C
 **************************************/
void TestMove::getText_castleQueen()
{
	Move m;
	Position src(4, 0);
	Position dst(2, 0);
	m.assignCastleQueen(src, dst);
	assertUnit(m.getText() == "e1c1C");
}

/*************************************
 * LETTER FROM PIECE TYPE space
 * Input :  SPACE
 * Output:  ' '
 **************************************/
void TestMove::letterFromPieceType_space()
{
	Move m;
	assertUnit(m.letterFromPieceType(SPACE) == ' ');
}

/*************************************
 * LETTER FROM PIECE TYPE pawn
 * Input : PAWN
 * Output:  'p'
 **************************************/
void TestMove::letterFromPieceType_pawn()
{
	Move m;
	assertUnit(m.letterFromPieceType(PAWN) == 'p');
}

/*************************************
 * LETTER FROM PIECE TYPE bishop
 * Input : BISHOP
 * Output:  'b'
 **************************************/
void TestMove::letterFromPieceType_bishop()
{
	Move m;
	assertUnit(m.letterFromPieceType(BISHOP) == 'b');
}

/*************************************
 * LETTER FROM PIECE TYPE knight
 * Input : KNIGHT
 * Output:  'n'
 **************************************/
void TestMove::letterFromPieceType_knight()
{
	Move m;
	assertUnit(m.letterFromPieceType(KNIGHT) == 'n');
}

/*************************************
 * LETTER FROM PIECE TYPE rook
 * Input : ROOK
 * Output:  'r'
 **************************************/
void TestMove::letterFromPieceType_rook()
{
	Move m;
	assertUnit(m.letterFromPieceType(ROOK) == 'r');
}

/*************************************
 * LETTER FROM PIECE TYPE queen
 * Input : QUEEN
 * Output:  'q'
 **************************************/
void TestMove::letterFromPieceType_queen()
{
	Move m;
	assertUnit(m.letterFromPieceType(QUEEN) == 'q');
}

/*************************************
 * LETTER FROM PIECE TYPE king
 * Input : KING
 * Output:  'k'
 **************************************/
void TestMove::letterFromPieceType_king()
{
	Move m;
	assertUnit(m.letterFromPieceType(KING) == 'k');
}

/*************************************
 * PIECE TYPE FROM LETTER pawn
 * Input : 'p'
 * Output:  PAWN
 **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('p') == PAWN);
}

/*************************************
 * PIECE TYPE FROM LETTER bishop
 * Input : 'b'
 * Output:  BISHOP
 **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('b') == BISHOP);
}

/*************************************
 * PIECE TYPE FROM LETTER knight
 * Input : 'n'
 * Input:  KNIGHT
 **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('n') == KNIGHT);
}

/*************************************
 * PIECE TYPE FROM LETTER rook
 * Input : 'r'
 * Input:  ROOK
 **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('r') == ROOK);
}

/*************************************
 * PIECE TYPE FROM LETTER queen
 * Input : 'q'
 * Input:  QUEEN
 **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('q') == QUEEN);
}

/*************************************
 * PIECE TYPE FROM LETTER king
 * Input : 'k'
 * Input:  KING
 **************************************/
void TestMove::pieceTypeFromLetter_king()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('k') == KING);
}
