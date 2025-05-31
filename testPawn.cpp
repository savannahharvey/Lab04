/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>



 /*************************************
  * GET MOVES TEST Simple
  * White pawn in the middle of the board move forward one space: b4 --> b5
  *
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5     .               5
  * 4    (p)              4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x13;
   pawn.nMoves = 1;
   board.board[1][3] = &pawn;

   set <Move> moves;
   Move b4b5;

   b4b5.source.colRow = 0x13;
   b4b5.dest.colRow = 0x14;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);  // 1 move
   assertUnit(moves.find(b4b5) != moves.end());

   // TEARDOWN
   board.board[1][3] = nullptr;
}

/*************************************
 * GET MOVES TEST Simple
 * Black pawn in the middle of the board move forward one space: b4 --> b3
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = false;
   pawn.position.colRow = 0x13;
   pawn.nMoves = 1;
   board.board[1][3] = &pawn;

   set <Move> moves;
   Move b4b3;

   b4b3.source.colRow = 0x13;
   b4b3.dest.colRow = 0x12;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);  // 1 move
   assertUnit(moves.find(b4b3) != moves.end());

   // TEARDOWN
   board.board[1][3] = nullptr;
}


/*************************************
 * GET MOVES TEST InitialAdvance
 * White pawn initial advance: b2 --> b4 as well as b2 --> b3
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x11;
   pawn.nMoves = 0;
   board.board[1][1] = &pawn;

   set <Move> moves;
   Move b2b3, b2b4;

   b2b3.source.colRow = b2b4.source.colRow = 0x11;
   b2b3.dest.colRow = 0x12;
   b2b4.dest.colRow = 0x13;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 move
   assertUnit(moves.find(b2b3) != moves.end());
   assertUnit(moves.find(b2b4) != moves.end());

   // TEARDOWN
   board.board[1][1] = nullptr;
}

/*************************************
 * GET MOVES TEST InitialAdvance
 * Black pawn initial advance: c7 --> c5 as well as c7 --> c5
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = false;
   pawn.position.colRow = 0x26;
   pawn.nMoves = 0;
   board.board[2][6] = &pawn;

   set <Move> moves;
   Move c7c6, c7c5;

   c7c6.source.colRow = c7c5.source.colRow = 0x26;
   c7c6.dest.colRow = 0x25;
   c7c5.dest.colRow = 0x24;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 move
   assertUnit(moves.find(c7c6) != moves.end());
   assertUnit(moves.find(c7c5) != moves.end());

   // TEARDOWN
   board.board[2][6] = nullptr;
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move white pawn b6 and capture two: a7 and c7. b7 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x15;
   pawn.nMoves = 1;
   board.board[1][5] = &pawn;
   
   Black P(PAWN);
   
   board.board[0][6] = board.board[1][6] = board.board[2][6] = &P;
   
   set <Move> moves;
   Move b6a7p, b6c7p;

   b6a7p.source.colRow = b6c7p.source.colRow = 0x15;
   b6a7p.capture = b6c7p.capture = PAWN;
   b6a7p.dest.colRow = 0x06;
   b6c7p.dest.colRow = 0x26;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 move
   assertUnit(moves.find(b6a7p) != moves.end());
   assertUnit(moves.find(b6c7p) != moves.end());

   // TEARDOWN
   board.board[0][6] = board.board[1][6] = board.board[2][6] = nullptr;
                       board.board[1][5] = nullptr;
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move black pawn b6 and capture two: a5 and c5. b5 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = false;
   pawn.position.colRow = 0x15;
   pawn.nMoves = 1;
   board.board[1][5] = &pawn;
   
   White P(PAWN);
   
   board.board[0][4] = board.board[1][4] = board.board[2][4] = &P;
   
   set <Move> moves; // b6 and capture two: a5 and c5
   Move b6a5p, b6c5p;

   b6a5p.source.colRow = b6c5p.source.colRow = 0x15;
   b6a5p.capture = b6c5p.capture = PAWN;
   b6a5p.dest.colRow = 0x04;
   b6c5p.dest.colRow = 0x24;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 move
   assertUnit(moves.find(b6a5p) != moves.end());
   assertUnit(moves.find(b6c5p) != moves.end());

   // TEARDOWN
                       board.board[1][5] = nullptr;
   board.board[0][4] = board.board[1][4] = board.board[2][4] = nullptr;
}

/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant: white b5 can capture a5 and c5. Note that b6 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{  // SETUP
   BoardEmpty board;
   board.moveNumber = 2;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x14;
   pawn.nMoves = 1;
   board.board[1][4] = &pawn;
   
   Black pawnL(PAWN);
   pawnL.nMoves = 1;
   pawnL.lastMove = 1;
   Black pawnR(PAWN);
   pawnR.nMoves = 1;
   pawnR.lastMove = 1;

   board.board[0][4] = &pawnL;
   board.board[2][4] = &pawnR;

   Black P(PAWN);
   board.board[1][5] = &P;
   
   set <Move> moves; // b5 can capture a5 and c5
   Move b5a6e, b5c6e;

   b5a6e.source.colRow = b5c6e.source.colRow = 0x14;
   b5a6e.capture = b5c6e.capture = PAWN;
   b5a6e.moveType = b5c6e.moveType = Move::ENPASSANT;
   b5a6e.dest.colRow = 0x05;
   b5c6e.dest.colRow = 0x25;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 move
   assertUnit(moves.find(b5a6e) != moves.end());
   assertUnit(moves.find(b5c6e) != moves.end());

   // TEARDOWN
                       board.board[1][5] =
   board.board[0][4] = board.board[1][5] = board.board[2][4] = nullptr;
}


/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant black f4 can capture e4 and g4. Note that f3 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{  // SETUP
   BoardEmpty board;
   board.moveNumber = 2;
   Pawn pawn(0, 0, false);
   pawn.fWhite = false;
   pawn.position.colRow = 0x53;
   pawn.nMoves = 1;
   board.board[5][3] = &pawn;
   
   White pawnL(PAWN);
   pawnL.nMoves = 1;
   pawnL.lastMove = 1;
   White pawnR(PAWN);
   pawnR.nMoves = 1;
   pawnR.lastMove = 1;

   board.board[4][3] = &pawnL;
   board.board[6][3] = &pawnR;

   White P(PAWN);
   board.board[5][2] = &P;
   
   set <Move> moves; // f4 can capture e4 and g4
   Move f4e3e, f4g4e;

   f4e3e.source.colRow = f4g4e.source.colRow = 0x53;
   f4e3e.capture = f4g4e.capture = PAWN;
   f4e3e.moveType = f4g4e.moveType = Move::ENPASSANT;
   f4e3e.dest.colRow = 0x42;
   f4g4e.dest.colRow = 0x62;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 move
   assertUnit(moves.find(f4e3e) != moves.end());
   assertUnit(moves.find(f4g4e) != moves.end());

   // TEARDOWN
   board.board[4][2] = board.board[5][3] = board.board[6][3] =
                       board.board[5][2] =nullptr;
}

/*************************************
 * GET MOVES TEST Promotion
 * Promotion: white pawn b7 can capture two pawns: a8 and c8. 
 *            It can also move into b8. All three are promoted to queen
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{  
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x16;
   pawn.nMoves = 1;
   board.board[1][6] = &pawn;
   
   Black P(PAWN);
   board.board[0][7] = board.board[2][7] = &P;
   
   set <Move> moves;
   Move b7a8p, b7b8, b7c8p;

   b7a8p.source.colRow = b7b8.source.colRow = b7c8p.source.colRow = 0x16;
   b7a8p.capture = b7c8p.capture = PAWN;
   b7a8p.promote = b7b8.promote = b7c8p.promote = QUEEN;
   b7a8p.dest.colRow = 0x07;
   b7b8.dest.colRow  = 0x17;
   b7c8p.dest.colRow = 0x27;
   
   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);  // 3 move
   assertUnit(moves.find(b7a8p) != moves.end());
   assertUnit(moves.find(b7b8)  != moves.end());
   assertUnit(moves.find(b7c8p) != moves.end());

   // TEARDOWN
                       board.board[1][5] =
   board.board[0][4] = board.board[1][5] = board.board[2][4] = nullptr;
}


/*************************************
 * GET MOVES TEST Promotion
 * Promotion: black pawn e2 can capture two rooks: d1 and f1.
 *            It can also move into e1. All three are promoted to queen
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         r . r       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, true);
   pawn.fWhite = false;
   pawn.position.colRow = 0x41;
   pawn.nMoves = 1;
   board.board[4][1] = &pawn;

   White R(ROOK);
   board.board[3][0] = board.board[5][0] = &R;

   set <Move> moves;
   Move e2d1p, e2e1, e2f1p;

   e2d1p.source.colRow = e2e1.source.colRow = e2f1p.source.colRow = 0x16;
   e2d1p.capture = e2f1p.capture = PAWN;
   e2d1p.promote = e2e1.promote = e2f1p.promote = QUEEN;
   e2d1p.dest.colRow = 0x30;
   e2e1.dest.colRow = 0x40;
   e2f1p.dest.colRow = 0x50;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);  // 3 move
   assertUnit(moves.find(e2d1p) != moves.end());
   assertUnit(moves.find(e2e1) != moves.end());
   assertUnit(moves.find(e2f1p) != moves.end());

   // TEARDOWN
   board.board[1][5] =
      board.board[0][4] = board.board[1][5] = board.board[2][4] = nullptr;
}


/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
   // SETUP
   const Pawn pawn(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = pawn.getType();

   // VERIFY
   assertUnit(pt == PAWN);
}  // TEARDOWN
