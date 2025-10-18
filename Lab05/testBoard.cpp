/***********************************************************************
 * Source File:
 *    TEST BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for board
 ************************************************************************/


#include "testBoard.h"
#include "position.h"
#include "piece.h"
#include "board.h"
#include <cassert>
#include <iostream>
using namespace std;




/********************************************************
 *    e5c6
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6       .             6       6       n             6
 * 5          (n)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_knightMove()
{  // SETUP
   Move e5c6;
   e5c6.source.set(4, 4);
   e5c6.dest.set(2,5);
   e5c6.capture = SPACE;
   e5c6.promote = SPACE;
   e5c6.isWhite = true;
   e5c6.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, KNIGHT);
   board.board[2][5] = new PieceSpy(2, 5, false /*isWhite*/, SPACE);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5c6);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(KNIGHT == (board.board[2][5])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[2][5];
   delete board.board[4][4];
   board.board[2][5] = board.board[4][4] = nullptr;
}

 /********************************************************
 *    e5c6r
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7       R             7       7                     7
 * 6                     6       6       n             6
 * 5          (n)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_knightAttack()
{  // SETUP
   Move e5c6r;
   e5c6r.source.set(4,4);
   e5c6r.dest.set(2,5);
   e5c6r.capture = ROOK;
   e5c6r.promote = SPACE;
   e5c6r.isWhite = true;
   e5c6r.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, KNIGHT);
   board.board[2][5] = new PieceSpy(2, 5, false /*isWhite*/, ROOK);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5c6r);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(KNIGHT == (board.board[2][5])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[2][5];
   delete board.board[4][4];
   board.board[2][5] = board.board[4][4] = nullptr;
}



/********************************************************
 *   a2a3
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3   .                 3       3   p                 3
 * 2  (p)                2       2   .                 2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnSimple()
{
	// SETUP
	Move a2a3;
	a2a3.source.set(0, 1);  // a2
	a2a3.dest.set(0, 2);    // a3
	a2a3.capture = SPACE;
	a2a3.promote = SPACE;
	a2a3.isWhite = true;
	a2a3.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 5;
	board.board[0][1] = new PieceSpy(0, 1, true, PAWN);   // white pawn at a2
	board.board[0][2] = new PieceSpy(0, 2, false, SPACE); // empty square at a3
	PieceSpy::reset();

	// EXERCISE
	board.move(a2a3);

	// VERIFY
	assertUnit(6 == board.numMoves);                                  // incremented
	assertUnit(SPACE == board.board[0][1]->getType());                // source cleared
	assertUnit(PAWN == board.board[0][2]->getType());                 // pawn moved
	assertUnit(PieceSpy::numConstruct == 0);                          // no temp objects
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][1];
	delete board.board[0][2];
	board.board[0][1] = board.board[0][2] = nullptr;
}


/********************************************************
 *     a6b7r
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7     R               7       7    (p)              7
 * 6  (p)                6       6   .                 6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnCapture()
{
	// SETUP
	Move a6b7r;
	a6b7r.source.set(0, 5);  // a6
	a6b7r.dest.set(1, 6);    // b7
	a6b7r.capture = ROOK;
	a6b7r.promote = SPACE;
	a6b7r.isWhite = true;
	a6b7r.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 10;

	// Place a white pawn at a6 and a black rook at b7
	board.board[0][5] = new PieceSpy(0, 5, true, PAWN);   // source: pawn
	board.board[1][6] = new PieceSpy(1, 6, false, ROOK);  // destination: enemy rook
	PieceSpy::reset();

	// EXERCISE
	board.move(a6b7r);

	// VERIFY
	assertUnit(11 == board.numMoves);                      // move count incremented
	assertUnit(SPACE == board.board[0][5]->getType());     // source cleared
	assertUnit(PAWN == board.board[1][6]->getType());      // pawn replaced rook
	assertUnit(PieceSpy::numConstruct == 0);               // no temp construction
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][5];
	delete board.board[1][6];
	board.board[0][5] = board.board[1][6] = nullptr;
}


/********************************************************
 *    e2e4
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4           .         4  -->  4          (p)        4
 * 3                     3       3                     3
 * 2          (p)        2       2           .         2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnDouble()
{
	// SETUP
	Move e2e4;
	e2e4.source.set(4, 1);  // e2
	e2e4.dest.set(4, 3);    // e4
	e2e4.capture = SPACE;
	e2e4.promote = SPACE;
	e2e4.isWhite = true;
	e2e4.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 5;

	// Place a white pawn on e2, and make e4 empty
	board.board[4][1] = new PieceSpy(4, 1, true, PAWN);
	board.board[4][3] = new PieceSpy(4, 3, false, SPACE);
	PieceSpy::reset();

	// EXERCISE
	board.move(e2e4);

	// VERIFY
	assertUnit(6 == board.numMoves);                      // move count incremented
	assertUnit(SPACE == board.board[4][1]->getType());    // e2 cleared
	assertUnit(PAWN == board.board[4][3]->getType());     // pawn now on e4
	assertUnit(PieceSpy::numConstruct == 0);              // no copies or deletes
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][1];
	delete board.board[4][3];
	board.board[4][1] = board.board[4][3] = nullptr;
}


/********************************************************
*     a5b6E
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6     .               6       6     p               6
 * 5  (p)P               5       5   . .               5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnEnpassant()
{
	// SETUP
	Move a5b6E;
	a5b6E.source.set(0, 4);   // a5 (white pawn)
	a5b6E.dest.set(1, 5);     // b6 (target square)
	a5b6E.capture = PAWN;
	a5b6E.promote = SPACE;
	a5b6E.isWhite = true;
	a5b6E.moveType = Move::ENPASSANT;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 9;

	// White pawn on a5
	board.board[0][4] = new PieceSpy(0, 4, true, PAWN);
	// Black pawn that just moved two spaces and can be captured via en-passant (on b5)
	board.board[1][4] = new PieceSpy(1, 4, false, PAWN);
	// Destination square (b6) is empty
	board.board[1][5] = new PieceSpy(1, 5, false, SPACE);

	PieceSpy::reset();

	// EXERCISE
	board.move(a5b6E);

	// VERIFY
	assertUnit(10 == board.numMoves);                        // incremented move count
	assertUnit(SPACE == board.board[0][4]->getType());       // a5 now empty
	assertUnit(PAWN == board.board[1][5]->getType());        // pawn moved to b6
	assertUnit(SPACE == board.board[1][4]->getType());       // captured pawn removed (b5)
	assertUnit(PieceSpy::numConstruct == 0);                 // no unwanted constructions
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	/*cout << board.board[1][4]->getType() << endl;*/

	cout << a5b6E.isEnPassant() << endl;

	// TEARDOWN
	delete board.board[0][4];
	delete board.board[1][4];
	delete board.board[1][5];
	board.board[0][4] = board.board[1][4] = board.board[1][5] = nullptr;
}


/********************************************************
 *    a7a8Q
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8   .                 8       8  (r)                8
 * 7  (p)                7       7   .                 7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnPromotion()
{
	// SETUP
	Move a7a8Q;
	a7a8Q.source.set(0, 6);   // a7
	a7a8Q.dest.set(0, 7);     // a8
	a7a8Q.capture = SPACE;
	a7a8Q.promote = QUEEN;    // promote to queen
	a7a8Q.isWhite = true;
	a7a8Q.moveType = Move::MOVE;  // normal move type

	Board board(nullptr, true /* noreset */);
	board.numMoves = 4;

	// White pawn on a7
	board.board[0][6] = new PieceSpy(0, 6, true, PAWN);
	// Destination square (a8) empty initially
	board.board[0][7] = new PieceSpy(0, 7, false, SPACE);

	PieceSpy::reset();

	// EXERCISE
	board.move(a7a8Q);

	// VERIFY
	assertUnit(5 == board.numMoves);                        // move counter incremented
	assertUnit(SPACE == board.board[0][6]->getType());      // old square now empty
	assertUnit(QUEEN == board.board[0][7]->getType());      // pawn promoted to queen
	assertUnit(board.board[0][7]->isWhite());               // still white
	assertUnit(PieceSpy::numConstruct == 0);                // no unexpected object creation
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][6];
	delete board.board[0][7];
	board.board[0][6] = board.board[0][7] = nullptr;
}


/********************************************************
 *    e5a5
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5   .      (r)        5       5  (r)      .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_rookSlide()
{
	// SETUP
	Move e5a5;
	e5a5.source.set(4, 4);   // e5
	e5a5.dest.set(0, 4);     // a5
	e5a5.capture = SPACE;
	e5a5.promote = SPACE;
	e5a5.isWhite = true;
	e5a5.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 11;

	// Rook on e5
	board.board[4][4] = new PieceSpy(4, 4, true, ROOK);
	// Destination a5 empty
	board.board[0][4] = new PieceSpy(0, 4, false, SPACE);

	// Clear intermediate squares
	for (int c = 1; c < 4; ++c)
		board.board[c][4] = new PieceSpy(c, 4, false, SPACE);

	PieceSpy::reset();

	// EXERCISE
	board.move(e5a5);

	// VERIFY
	assertUnit(12 == board.numMoves);                       // move counter incremented
	assertUnit(SPACE == board.board[4][4]->getType());      // source e5 now empty
	assertUnit(ROOK == board.board[0][4]->getType());       // rook now at destination a5
	assertUnit(board.board[0][4]->isWhite());               // still white rook
	assertUnit(PieceSpy::numConstruct == 0);                // no extra creations
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	for (int c = 0; c <= 4; ++c)
	{
		delete board.board[c][4];
		board.board[c][4] = nullptr;
	}
}


/********************************************************
 *    e5a5b
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5   B      (r)        5       5  (r)      .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_rookAttack()
{
	// SETUP
	Move e5a5b;
	e5a5b.source.set(4, 4);   // e5 (rook)
	e5a5b.dest.set(0, 4);     // a5 (capture target)
	e5a5b.capture = BISHOP;
	e5a5b.promote = SPACE;
	e5a5b.isWhite = true;
	e5a5b.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 13;

	// Destination a5 has a black bishop
	board.board[0][4] = new PieceSpy(0, 4, false, BISHOP);
	// Rook at e5 (white)
	board.board[4][4] = new PieceSpy(4, 4, true, ROOK);

	// Clear intermediate squares (b5, c5, d5)
	for (int c = 1; c < 4; ++c)
		board.board[c][4] = new PieceSpy(c, 4, false, SPACE);

	PieceSpy::reset();

	// EXERCISE
	board.move(e5a5b);

	// VERIFY
	assertUnit(14 == board.numMoves);                      // move count incremented
	assertUnit(SPACE == board.board[4][4]->getType());     // e5 now empty
	assertUnit(ROOK == board.board[0][4]->getType());      // rook moved to a5
	assertUnit(board.board[0][4]->isWhite());              // still white rook
	assertUnit(PieceSpy::numConstruct == 0);               // no extra constructions
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	for (int c = 0; c <= 4; ++c)
	{
		delete board.board[c][4];
		board.board[c][4] = nullptr;
	}
}



/********************************************************
 *    e5g3
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (b)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3               .     3       3               b     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_bishopSlide()
{
	// SETUP
	Move e5g3;
	e5g3.source.set(4, 4);   // e5 (bishop)
	e5g3.dest.set(6, 2);     // g3
	e5g3.capture = SPACE;
	e5g3.promote = SPACE;
	e5g3.isWhite = true;
	e5g3.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 21;

	// Bishop at e5 (white)
	board.board[4][4] = new PieceSpy(4, 4, true, BISHOP);

	// Destination square (g3) is empty
	board.board[6][2] = new PieceSpy(6, 2, false, SPACE);

	// Clear path: f4 (5,3)
	board.board[5][3] = new PieceSpy(5, 3, false, SPACE);

	PieceSpy::reset();

	// EXERCISE
	board.move(e5g3);

	// VERIFY
	assertUnit(22 == board.numMoves);                     // move count incremented
	assertUnit(SPACE == board.board[4][4]->getType());    // e5 now empty
	assertUnit(BISHOP == board.board[6][2]->getType());   // bishop moved to g3
	assertUnit(board.board[6][2]->isWhite());             // still white bishop
	assertUnit(PieceSpy::numConstruct == 0);              // no unnecessary constructions
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][4];
	delete board.board[5][3];
	delete board.board[6][2];
	board.board[4][4] = board.board[5][3] = board.board[6][2] = nullptr;
}


/********************************************************
 *    e5g3q
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (b)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3               Q     3       3               b     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_bishopAttack()
{
	// SETUP
	Move e5g3q;
	e5g3q.source.set(4, 4);   // e5 (bishop)
	e5g3q.dest.set(6, 2);     // g3
	e5g3q.capture = QUEEN;    // capturing a black queen
	e5g3q.promote = SPACE;
	e5g3q.isWhite = true;
	e5g3q.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 23;

	// Bishop at e5 (white)
	board.board[4][4] = new PieceSpy(4, 4, true, BISHOP);

	// Path square f4 (5,3)
	board.board[5][3] = new PieceSpy(5, 3, false, SPACE);

	// Destination square g3 (black queen)
	board.board[6][2] = new PieceSpy(6, 2, false, QUEEN);

	PieceSpy::reset();

	// EXERCISE
	board.move(e5g3q);

	// VERIFY
	assertUnit(24 == board.numMoves);                     // move count incremented
	assertUnit(SPACE == board.board[4][4]->getType());    // e5 now empty
	assertUnit(BISHOP == board.board[6][2]->getType());   // bishop occupies g3
	assertUnit(board.board[6][2]->isWhite());             // still white
	assertUnit(PieceSpy::numConstruct == 0);              // no new constructions
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][4];
	delete board.board[5][3];
	delete board.board[6][2];
	board.board[4][4] = board.board[5][3] = board.board[6][2] = nullptr;
}

/********************************************************
 *    e5g3
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (q)        5       5                     5
 * 4                     4  -->  4           .         4
 * 3                .    3       3               q     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_queenSlide()
{
	// SETUP
	Move e5g3;
	e5g3.source.set(4, 4);   // e5
	e5g3.dest.set(6, 2);     // g3
	e5g3.capture = SPACE;    // no capture
	e5g3.promote = SPACE;
	e5g3.isWhite = true;
	e5g3.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 25;

	// Place a white queen at e5
	board.board[4][4] = new PieceSpy(4, 4, true, QUEEN);

	// Path square f4 (5,3) is empty
	board.board[5][3] = new PieceSpy(5, 3, false, SPACE);

	// Destination g3 (6,2) is empty
	board.board[6][2] = new PieceSpy(6, 2, false, SPACE);

	PieceSpy::reset();

	// EXERCISE
	board.move(e5g3);

	// VERIFY
	assertUnit(26 == board.numMoves);                      // move count increments
	assertUnit(SPACE == board.board[4][4]->getType());     // e5 is empty
	assertUnit(QUEEN == board.board[6][2]->getType());     // queen moved to g3
	assertUnit(board.board[6][2]->isWhite());              // queen still white
	assertUnit(PieceSpy::numConstruct == 0);               // no new objects created
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][4];
	delete board.board[5][3];
	delete board.board[6][2];
	board.board[4][4] = board.board[5][3] = board.board[6][2] = nullptr;
}


/********************************************************
*    e5a5b
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
* |                     |       |                     |
* 8                     8       8                     8
* 7                     7       7                     7
* 6                     6       6                     6
* 5   B      (q)        5       5  (q)      .         5
* 4                     4  -->  4                     4
* 3                     3       3                     3
* 2                     2       2                     2
* 1                     1       1                     1
* |                     |       |                     |
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
********************************************************/
void TestBoard::move_queenAttack()
{
	// SETUP
	Move e5a5b;
	e5a5b.source.set(4, 4);   // e5
	e5a5b.dest.set(0, 4);     // a5
	e5a5b.capture = BISHOP;   // capturing a bishop
	e5a5b.promote = SPACE;
	e5a5b.isWhite = true;
	e5a5b.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 27;

	// White queen at e5
	board.board[4][4] = new PieceSpy(4, 4, true, QUEEN);

	// Path squares (d5, c5, b5) are empty
	board.board[3][4] = new PieceSpy(3, 4, false, SPACE);
	board.board[2][4] = new PieceSpy(2, 4, false, SPACE);
	board.board[1][4] = new PieceSpy(1, 4, false, SPACE);

	// Destination a5 (0,4) has a black bishop
	board.board[0][4] = new PieceSpy(0, 4, false, BISHOP);

	PieceSpy::reset();

	// EXERCISE
	board.move(e5a5b);

	// VERIFY
	assertUnit(28 == board.numMoves);                      // move counter increments
	assertUnit(SPACE == board.board[4][4]->getType());     // e5 is now empty
	assertUnit(QUEEN == board.board[0][4]->getType());     // queen moved to a5
	assertUnit(board.board[0][4]->isWhite());              // queen is still white
	assertUnit(PieceSpy::numConstruct == 0);               // no new constructions
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][4];
	delete board.board[3][4];
	delete board.board[2][4];
	delete board.board[1][4];
	delete board.board[0][4];
	board.board[4][4] = board.board[3][4] =
		board.board[2][4] = board.board[1][4] =
		board.board[0][4] = nullptr;
}


/********************************************************
 *  e1f1
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1          (k).       1       1           . k       1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingMove()
{
	// SETUP
	Move e1f1;
	e1f1.source.set(4, 0);  // e1
	e1f1.dest.set(5, 0);    // f1
	e1f1.capture = SPACE;
	e1f1.promote = SPACE;
	e1f1.isWhite = true;
	e1f1.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 11;

	// White king at e1
	board.board[4][0] = new PieceSpy(4, 0, true, KING);
	// Destination square f1 empty
	board.board[5][0] = new PieceSpy(5, 0, false, SPACE);

	PieceSpy::reset();

	// EXERCISE
	board.move(e1f1);

	// VERIFY
	assertUnit(12 == board.numMoves);                     // move counter increments
	assertUnit(SPACE == board.board[4][0]->getType());    // e1 now empty
	assertUnit(KING == board.board[5][0]->getType());     // f1 now has king
	assertUnit(board.board[5][0]->isWhite());             // king remains white
	assertUnit(PieceSpy::numConstruct == 0);              // no unwanted memory operations
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][0];
	delete board.board[5][0];
	board.board[4][0] = board.board[5][0] = nullptr;
}


/********************************************************
 *    e1f1r
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1          (k)R       1       1           . k       1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingAttack()
{
	// SETUP
	Move e1f1r;
	e1f1r.source.set(4, 0);  // e1
	e1f1r.dest.set(5, 0);    // f1
	e1f1r.capture = ROOK;
	e1f1r.promote = SPACE;
	e1f1r.isWhite = true;
	e1f1r.moveType = Move::MOVE;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 12;

	// White king at e1
	board.board[4][0] = new PieceSpy(4, 0, true, KING);
	// Black rook at f1 (capture target)
	board.board[5][0] = new PieceSpy(5, 0, false, ROOK);

	PieceSpy::reset();

	// EXERCISE
	board.move(e1f1r);

	// VERIFY
	assertUnit(13 == board.numMoves);                     // move count increments
	assertUnit(SPACE == board.board[4][0]->getType());    // e1 now empty
	assertUnit(KING == board.board[5][0]->getType());     // f1 now has the king
	assertUnit(board.board[5][0]->isWhite());             // king remains white
	assertUnit(PieceSpy::numConstruct == 0);              // no unexpected memory ops
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][0];
	delete board.board[5][0];
	board.board[4][0] = board.board[5][0] = nullptr;
}

/********************************************************
 *    e1g1c
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1          (k). . r   1       1           . r k .   1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingShortCastle()
{
	// SETUP
	Move e1g1c;
	e1g1c.source.set(4, 0);     // e1
	e1g1c.dest.set(6, 0);       // g1
	e1g1c.capture = SPACE;
	e1g1c.promote = SPACE;
	e1g1c.isWhite = true;
	e1g1c.moveType = Move::CASTLE_KING;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 20;

	// White king and rook
	board.board[4][0] = new PieceSpy(4, 0, true, KING);  // e1 king
	board.board[5][0] = new PieceSpy(5, 0, true, SPACE); // f1 empty
	board.board[6][0] = new PieceSpy(6, 0, true, SPACE); // g1 empty
	board.board[7][0] = new PieceSpy(7, 0, true, ROOK);  // h1 rook

	PieceSpy::reset();

	// EXERCISE
	board.move(e1g1c);

	// VERIFY
	assertUnit(21 == board.numMoves);                    // move count increments
	assertUnit(SPACE == board.board[4][0]->getType());   // e1 now empty
	assertUnit(KING == board.board[6][0]->getType());    // king moved to g1
	assertUnit(ROOK == board.board[5][0]->getType());    // rook moved to f1
	assertUnit(SPACE == board.board[7][0]->getType());   // h1 now empty
	assertUnit(board.board[6][0]->isWhite());            // king is white
	assertUnit(board.board[5][0]->isWhite());            // rook is white
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[4][0];
	delete board.board[5][0];
	delete board.board[6][0];
	delete board.board[7][0];
	board.board[4][0] = board.board[5][0] = board.board[6][0] = board.board[7][0] = nullptr;
}



/********************************************************
 *    e1c1C
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1   r . . .(k)        1       1   . . k r .         1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingLongCastle()
{
	// SETUP
	Move e1c1C;
	e1c1C.source.set(4, 0);     // e1
	e1c1C.dest.set(2, 0);       // c1
	e1c1C.capture = SPACE;
	e1c1C.promote = SPACE;
	e1c1C.isWhite = true;
	e1c1C.moveType = Move::CASTLE_QUEEN;

	Board board(nullptr, true /*noreset*/);
	board.numMoves = 30;

	// White king and rook for long castle
	board.board[0][0] = new PieceSpy(0, 0, true, ROOK);  // a1 rook
	board.board[1][0] = new PieceSpy(1, 0, true, SPACE); // b1 empty
	board.board[2][0] = new PieceSpy(2, 0, true, SPACE); // c1 empty
	board.board[3][0] = new PieceSpy(3, 0, true, SPACE); // d1 empty
	board.board[4][0] = new PieceSpy(4, 0, true, KING);  // e1 king

	PieceSpy::reset();

	// EXERCISE
	board.move(e1c1C);

	// VERIFY
	assertUnit(31 == board.numMoves);                    // move count increments
	assertUnit(SPACE == board.board[4][0]->getType());   // e1 now empty
	assertUnit(KING == board.board[2][0]->getType());    // king moved to c1
	assertUnit(ROOK == board.board[3][0]->getType());    // rook moved to d1
	assertUnit(SPACE == board.board[0][0]->getType());   // a1 now empty
	assertUnit(board.board[2][0]->isWhite());            // king is white
	assertUnit(board.board[3][0]->isWhite());            // rook is white
	assertUnit(PieceSpy::numConstruct == 0);
	assertUnit(PieceSpy::numCopy == 0);
	assertUnit(PieceSpy::numDelete == 0);
	assertUnit(PieceSpy::numAssign == 0);
	assertUnit(PieceSpy::numMove == 0);

	// TEARDOWN
	delete board.board[0][0];
	delete board.board[1][0];
	delete board.board[2][0];
	delete board.board[3][0];
	delete board.board[4][0];
	board.board[0][0] = board.board[1][0] = board.board[2][0] = board.board[3][0] = board.board[4][0] = nullptr;
}




/********************************************************
 *        +---a-b-c-d-e-f-g-h---+
 *        |                     |
 *        8   R N B Q K B N R   8
 *        7   P P P P P P P P   7
 *        6                     6
 *        5                     5
 *   -->  4                     4
 *        3                     3
 *        2   p p p p p p p p   2
 *        1   r n b q k b n r   1
 *        |                     |
 *        +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::construct_default()
{
	// SETUP
	PieceSpy::reset();

	// EXERCISE
	Board board(nullptr /* no graphics stream */);

	// VERIFY
	// White back rank
	assertUnit(board.board[0][0]->getType() == ROOK);
	assertUnit(board.board[1][0]->getType() == KNIGHT);
	assertUnit(board.board[2][0]->getType() == BISHOP);
	assertUnit(board.board[3][0]->getType() == QUEEN);
	assertUnit(board.board[4][0]->getType() == KING);
	assertUnit(board.board[5][0]->getType() == BISHOP);
	assertUnit(board.board[6][0]->getType() == KNIGHT);
	assertUnit(board.board[7][0]->getType() == ROOK);

	// White pawns
	for (int c = 0; c < 8; c++)
		assertUnit(board.board[c][1]->getType() == PAWN);

	// Black pawns
	for (int c = 0; c < 8; c++)
		assertUnit(board.board[c][6]->getType() == PAWN);

	// Black back rank
	assertUnit(board.board[0][7]->getType() == ROOK);
	assertUnit(board.board[1][7]->getType() == KNIGHT);
	assertUnit(board.board[2][7]->getType() == BISHOP);
	assertUnit(board.board[3][7]->getType() == QUEEN);
	assertUnit(board.board[4][7]->getType() == KING);
	assertUnit(board.board[5][7]->getType() == BISHOP);
	assertUnit(board.board[6][7]->getType() == KNIGHT);
	assertUnit(board.board[7][7]->getType() == ROOK);

	// Empty middle of the board
	for (int r = 2; r <= 5; r++)
		for (int c = 0; c < 8; c++)
			assertUnit(board.board[c][r] == nullptr);

	// Confirm move counter initialized
	assertUnit(board.numMoves == 0);

	// Confirm colors: bottom pieces white, top pieces black
	for (int c = 0; c < 8; c++)
	{
		assertUnit(board.board[c][0]->isWhite() == true);
		assertUnit(board.board[c][1]->isWhite() == true);
		assertUnit(board.board[c][6]->isWhite() == false);
		assertUnit(board.board[c][7]->isWhite() == false);
	}

	// TEARDOWN
	board.free();
}








/********************************************************
 * CREATE DUMMY BOARD
 ********************************************************/
void TestBoard::createDummyBoard(Board& board)
{
	// Clear out any existing pieces
	for (int c = 0; c < 8; c++)
	{
		for (int r = 0; r < 8; r++)
		{
			if (board.board[c][r])
			{
				delete board.board[c][r];
				board.board[c][r] = nullptr;
			}
		}
	}
	board.numMoves = 0;

	// VERIFY that the board is empty
	for (int c = 0; c < 8; c++)
		for (int r = 0; r < 8; r++)
			assertUnit(board.board[c][r] == nullptr);
}

/********************************************************
 * GET CURRENT MOVE TESTS
 ********************************************************/
void TestBoard::getCurrentMove_initial()
{
	Board board;
	board.numMoves = 0;
	assertUnit(board.getCurrentMove() == 0);
}

void TestBoard::getCurrentMove_second()
{
	Board board;
	board.numMoves = 1;
	assertUnit(board.getCurrentMove() == 1);
}

void TestBoard::getCurrentMove_middleWhite()
{
	Board board;
	board.numMoves = 10;
	assertUnit(board.getCurrentMove() == 10);
}

void TestBoard::getCurrentMove_middleBlack()
{
	Board board;
	board.numMoves = 11;
	assertUnit(board.getCurrentMove() == 11);
}

/********************************************************
 * WHITE TURN TESTS
 ********************************************************/
void TestBoard::whiteTurn_initial()
{
	Board board;
	board.numMoves = 0;
	assertUnit(board.whiteTurn() == true);
}

void TestBoard::whiteTurn_second()
{
	Board board;
	board.numMoves = 1;
	assertUnit(board.whiteTurn() == false);
}

void TestBoard::whiteTurn_middleWhite()
{
	Board board;
	board.numMoves = 10;
	assertUnit(board.whiteTurn() == true);
}

void TestBoard::whiteTurn_middleBlack()
{
	Board board;
	board.numMoves = 11;
	assertUnit(board.whiteTurn() == false);
}

/********************************************************
 * FETCH TESTS
 ********************************************************/
void TestBoard::fetch_a1()
{
	Board board(nullptr, true /*noreset*/);
	board.board[0][0] = new PieceSpy(0, 0, false, ROOK);

	const Piece& p = *board.board[0][0]; // ✅ dereference safely
	assertUnit(p.getType() == ROOK);

	delete board.board[0][0];
	board.board[0][0] = nullptr;
}

void TestBoard::fetch_h8()
{
	Board board(nullptr, true /*noreset*/);
	board.board[7][7] = new PieceSpy(7, 7, true, KING);

	const Piece& p = *board.board[7][7];
	assertUnit(p.getType() == KING);

	delete board.board[7][7];
	board.board[7][7] = nullptr;
}

void TestBoard::fetch_a8()
{
	Board board(nullptr, true /*noreset*/);
	board.board[0][7] = new PieceSpy(0, 7, false, ROOK);

	const Piece& p = *board.board[0][7];
	assertUnit(p.getType() == ROOK);

	delete board.board[0][7];
	board.board[0][7] = nullptr;
}

/********************************************************
 * SET TESTS
 ********************************************************/
void TestBoard::set_a1()
{
	Board board(nullptr, true /*noreset*/);
	Piece* rook = new PieceSpy(0, 0, false, ROOK);

	board.board[0][0] = rook; // ✅ direct pointer assignment
	assertUnit(board.board[0][0] != nullptr);
	assertUnit(board.board[0][0]->getType() == ROOK);

	delete board.board[0][0];
	board.board[0][0] = nullptr;
}

void TestBoard::set_h8()
{
	Board board(nullptr, true /*noreset*/);
	Piece* king = new PieceSpy(7, 7, true, KING);

	board.board[7][7] = king; // ✅
	assertUnit(board.board[7][7] != nullptr);
	assertUnit(board.board[7][7]->getType() == KING);

	delete board.board[7][7];
	board.board[7][7] = nullptr;
}

void TestBoard::set_a8()
{
	Board board(nullptr, true /*noreset*/);
	Piece* rook = new PieceSpy(0, 7, false, ROOK);

	board.board[0][7] = rook; // ✅
	assertUnit(board.board[0][7] != nullptr);
	assertUnit(board.board[0][7]->getType() == ROOK);

	delete board.board[0][7];
	board.board[0][7] = nullptr;
}
