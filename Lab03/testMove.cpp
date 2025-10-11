/***********************************************************************
 * Source File:
 *    TEST MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    test the Move class
 ************************************************************************/

#include "testMove.h"
#include "move.h"
#include <cassert>

 /*************************************
  * Constructor : default
  * Input:  (none)
  * Output: source=INVALID
  *         dest  =INVALID
  *         type  =MOVE_ERROR
  *         capture=SPACE
  *         promote=SPACE
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
 * Input : source=e5 (4,4)
 *         dest  =e6 (4,5)
 *         type  =MOVE
 * Output: fields initialized correctly
 **************************************/
void TestMove::constructString_simple()
{
	Position src(4, 4); // e5
	Position dst(4, 5); // e6
	Move m(src, dst, Move::MOVE);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::MOVE);
}

/*************************************
 * READ simple move
 * Input : "e5e6"
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::read_simple()
{
	Move m;
	m.read("e5e6");

	assertUnit(m.source == Position(4, 4));
	assertUnit(m.dest == Position(4, 5));
	assertUnit(m.moveType == Move::MOVE);
	assertUnit(m.capture == SPACE);
}

/*************************************
 * READ capture move
 * Input : "e5d6r"
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::read_capture()
{
	Move m;
	m.read("e5d6r");

	assertUnit(m.source == Position(4, 4));
	assertUnit(m.dest == Position(3, 5));
	assertUnit(m.moveType == Move::MOVE);
	assertUnit(m.capture == ROOK);
}

/*************************************
 * READ en passant move
 * Input : "e5f6E"
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 **************************************/
void TestMove::read_enpassant()
{
	Move m;
	m.read("e5f6E");

	assertUnit(m.source == Position(4, 4));
	assertUnit(m.dest == Position(5, 5));
	assertUnit(m.moveType == Move::ENPASSANT);
	assertUnit(m.capture == PAWN);
}

/*************************************
 * READ king side castle
 * Input : "e1g1c"
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::read_castleKing()
{
	Move m;
	m.read("e1g1c");

	assertUnit(m.source == Position(4, 0));
	assertUnit(m.dest == Position(6, 0));
	assertUnit(m.moveType == Move::CASTLE_KING);
}

/*************************************
 * READ queen side castle
 * Input : "e1c1C"
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::read_castleQueen()
{
	Move m;
	m.read("e1c1C");

	assertUnit(m.source == Position(4, 0));
	assertUnit(m.dest == Position(2, 0));
	assertUnit(m.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * ASSIGN simple move
 * Input : e5→e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::assign_simple()
{
	Move m;
	Position src(4, 4), dst(4, 5);
	m.assignSimple(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::MOVE);
}

/*************************************
 * ASSIGN capture move
 * Input : e5→d6 capture rook
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::assign_capture()
{
	Move m;
	Position src(4, 4), dst(3, 5);
	m.assignCapture(src, dst, ROOK);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::MOVE);
	assertUnit(m.capture == ROOK);
}

/*************************************
 * ASSIGN en passant move
 * Input : e5→f6 en passant
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 **************************************/
void TestMove::assign_enpassant()
{
	Move m;
	Position src(4, 4), dst(5, 5);
	m.assignEnPassant(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::ENPASSANT);
	assertUnit(m.capture == PAWN);
}

/*************************************
 * ASSIGN king side castle
 * Input : e1→g1
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::assign_castleKing()
{
	Move m;
	Position src(4, 0), dst(6, 0);
	m.assignCastleKing(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::CASTLE_KING);
}

/*************************************
 * ASSIGN queen side castle
 * Input : e1→c1
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::assign_castleQueen()
{
	Move m;
	Position src(4, 0), dst(2, 0);
	m.assignCastleQueen(src, dst);

	assertUnit(m.source == src);
	assertUnit(m.dest == dst);
	assertUnit(m.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * GET TEXT simple move
 * Input : e5→e6
 * Output: "e5e6"
 **************************************/
void TestMove::getText_simple()
{
	Position src(4, 4), dst(4, 5);
	Move m(src, dst, Move::MOVE);

	assertUnit(m.getText() == "e5e6");
}

/*************************************
 * GET TEXT capture
 * Input : e5→e6 capture rook
 * Output: "e5e6r"
 **************************************/
void TestMove::getText_capture()
{
	Position src(4, 4), dst(4, 5);
	Move m;
	m.assignCapture(src, dst, ROOK);

	assertUnit(m.getText() == "e5e6r");
}

/*************************************
 * GET TEXT en passant
 * Input : e5→f6 en passant
 * Output: "e5f6E"
 **************************************/
void TestMove::getText_enpassant()
{
	Position src(4, 4), dst(5, 5);
	Move m;
	m.assignEnPassant(src, dst);

	assertUnit(m.getText() == "e5f6E");
}

/*************************************
 * GET TEXT king side castle
 * Input : e1→g1
 * Output: "e1g1c"
 **************************************/
void TestMove::getText_castleKing()
{
	Position src(4, 0), dst(6, 0);
	Move m;
	m.assignCastleKing(src, dst);

	assertUnit(m.getText() == "e1g1c");
}

/*************************************
 * GET TEXT queen side castle
 * Input : e1→c1
 * Output: "e1c1C"
 **************************************/
void TestMove::getText_castleQueen()
{
	Position src(4, 0), dst(2, 0);
	Move m;
	m.assignCastleQueen(src, dst);

	assertUnit(m.getText() == "e1c1C");
}

/*************************************
 * LETTER FROM PIECE TYPE
 **************************************/
void TestMove::letterFromPieceType_space()
{
	Move m;
	assertUnit(m.letterFromPieceType(SPACE) == ' ');
}
void TestMove::letterFromPieceType_pawn()
{
	Move m;
	assertUnit(m.letterFromPieceType(PAWN) == 'p');
}
void TestMove::letterFromPieceType_bishop()
{
	Move m;
	assertUnit(m.letterFromPieceType(BISHOP) == 'b');
}
void TestMove::letterFromPieceType_knight()
{
	Move m;
	assertUnit(m.letterFromPieceType(KNIGHT) == 'n');
}
void TestMove::letterFromPieceType_rook()
{
	Move m;
	assertUnit(m.letterFromPieceType(ROOK) == 'r');
}
void TestMove::letterFromPieceType_queen()
{
	Move m;
	assertUnit(m.letterFromPieceType(QUEEN) == 'q');
}
void TestMove::letterFromPieceType_king()
{
	Move m;
	assertUnit(m.letterFromPieceType(KING) == 'k');
}

/*************************************
 * PIECE TYPE FROM LETTER
 **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('p') == PAWN);
}
void TestMove::pieceTypeFromLetter_bishop()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('b') == BISHOP);
}
void TestMove::pieceTypeFromLetter_knight()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('n') == KNIGHT);
}
void TestMove::pieceTypeFromLetter_rook()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('r') == ROOK);
}
void TestMove::pieceTypeFromLetter_queen()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('q') == QUEEN);
}
void TestMove::pieceTypeFromLetter_king()
{
	Move m;
	assertUnit(m.pieceTypeFromLetter('k') == KING);
}

/*************************************
 * EQUAL - NOT
 * Input : b2b4 vs b2b5
 * Output: false
 **************************************/
void TestMove::equal_not()
{
	Move m1, m2;
	m1.read("b2b4");
	m2.read("b2b5");
	assertUnit(!(m1 == m2));
	assertUnit(m1 != m2);
}

/*************************************
 * EQUAL - EQUALS
 * Input : b2b4 vs b2b4
 * Output: true
 **************************************/
void TestMove::equal_equals()
{
	Move m1, m2;
	m1.read("b2b4");
	m2.read("b2b4");
	assertUnit(m1 == m2);
	assertUnit(!(m1 != m2));
}

/*************************************
 * LESS THAN
 * Note: compare by destination position
 **************************************/
void TestMove::lessthan_lessthan()
{
	Move m1, m2;
	m1.read("b2b2");
	m2.read("b2b4");
	assertUnit(m1 < m2); // b2 < b4
}
void TestMove::lessthan_equals()
{
	Move m1, m2;
	m1.read("b2b4");
	m2.read("b2b4");
	assertUnit(!(m1 < m2));
}
void TestMove::lessthan_greaterthan()
{
	Move m1, m2;
	m1.read("b2b4");
	m2.read("b2b2");
	assertUnit(!(m1 < m2));
}
