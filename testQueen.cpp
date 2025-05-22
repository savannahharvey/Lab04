/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "testQueen.h"
#include "pieceQueen.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      

#include <iostream>
using namespace std;


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3     p p p           3
 * 2     p(q)p           2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Queen queen(3, 4, false);
   queen.fWhite = true;
   queen.position.colRow = 0x21;
   board.board[2][1] = &queen;
   White white(PAWN);
   board.board[1][2] = board.board[2][2] = board.board[3][2] = &white;
   board.board[1][1] =                     board.board[3][1] = &white;
   board.board[1][0] = board.board[2][0] = board.board[3][0] = &white;

   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // we are blocked

   // TEARDOWN
   board.board[1][2] = board.board[2][2] = board.board[3][2] = nullptr;
   board.board[1][1] =                     board.board[3][1] = nullptr;
   board.board[1][0] = board.board[2][0] = board.board[3][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Queen queen(3, 4, false);
   queen.fWhite = true;
   queen.position.colRow = 0x21;
   board.board[2][1] = &queen;

   set <Move> moves;
   Move           c2c8,
                  c2c7,                         c2h7,
                  c2c6,                   c2g6,
                  c2c5,             c2f5,
      c2a4,       c2c4,       c2e4,
            c2b3, c2c3, c2d3,
      c2a2, c2b2, /*q*/ c2d2, c2e2, c2f2, c2g2, c2h2,
            c2b1, c2c1, c2d1;

   c2a2.source.colRow = c2a4.source.colRow = 0x21;
   c2b1.source.colRow = c2b2.source.colRow = 0x21;
   c2b3.source.colRow = c2c1.source.colRow = 0x21;
   c2c3.source.colRow = c2c4.source.colRow = 0x21;
   c2c5.source.colRow = c2c6.source.colRow = 0x21;
   c2c7.source.colRow = c2c8.source.colRow = 0x21;
   c2d1.source.colRow = c2d2.source.colRow = 0x21;
   c2d3.source.colRow = c2e2.source.colRow = 0x21;
   c2e4.source.colRow = c2f2.source.colRow = 0x21;
   c2f5.source.colRow = c2g2.source.colRow = 0x21;
   c2g6.source.colRow = c2h2.source.colRow = 0x21;
   c2h7.source.colRow = 0x21;

   c2a2.dest.colRow = 0x01;
   c2a4.dest.colRow = 0x03;
   c2b1.dest.colRow = 0x10;
   c2b2.dest.colRow = 0x11;
   c2b3.dest.colRow = 0x12;
   c2c1.dest.colRow = 0x20;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2c8.dest.colRow = 0x27;
   c2d1.dest.colRow = 0x30;
   c2d2.dest.colRow = 0x31;
   c2d3.dest.colRow = 0x32;
   c2e2.dest.colRow = 0x41;
   c2e4.dest.colRow = 0x43;
   c2f2.dest.colRow = 0x51;
   c2f5.dest.colRow = 0x54;
   c2g2.dest.colRow = 0x61;
   c2g6.dest.colRow = 0x65;
   c2h2.dest.colRow = 0x71;
   c2h7.dest.colRow = 0x76;

   c2a2.capture = c2a4.capture = SPACE;
   c2b1.capture = c2b2.capture = SPACE;
   c2b3.capture = c2c1.capture = SPACE;
   c2c3.capture = c2c4.capture = SPACE;
   c2c5.capture = c2c6.capture = SPACE;
   c2c7.capture = c2c8.capture = SPACE;
   c2d1.capture = c2d2.capture = SPACE;
   c2d3.capture = c2e2.capture = SPACE;
   c2e4.capture = c2f2.capture = SPACE;
   c2f5.capture = c2g2.capture = SPACE;
   c2g6.capture = c2h2.capture = SPACE;
   c2h7.capture = SPACE;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);  // many possible moves
   assertUnit(moves.find(c2a2) != moves.end());
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2b1) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2c1) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2c8) != moves.end());
   assertUnit(moves.find(c2d1) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());
   assertUnit(moves.find(c2h2) != moves.end());
   assertUnit(moves.find(c2h7) != moves.end());

   // TEARDOWN
   board.board[0][1] = board.board[0][3] = board.board[1][0] = nullptr;
   board.board[1][1] = board.board[1][2] = board.board[2][0] = nullptr;
   board.board[2][2] = board.board[2][3] = board.board[2][4] = nullptr;
   board.board[2][5] = board.board[2][6] = board.board[2][7] = nullptr;
   board.board[3][0] = board.board[3][1] = board.board[3][2] = nullptr;
   board.board[4][1] = board.board[4][3] = board.board[5][1] = nullptr;
   board.board[5][4] = board.board[6][1] = board.board[6][5] = nullptr;
   board.board[7][1] = board.board[6][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Queen queen(3, 4, false);
   queen.fWhite = true;
   queen.position.colRow = 0x21;
   board.board[2][1] = &queen;
   White white(PAWN);
   board.board[1][0] = board.board[1][1] = board.board[1][2] = &white;
   board.board[0][1] = board.board[0][3] = board.board[2][7] = &white;
   board.board[7][6] = board.board[7][1] = &white;

   set <Move> moves;
   Move           c2c8,
                  c2c7,                         c2h7,
                  c2c6,                   c2g6,
                  c2c5,             c2f5,
      c2a4,       c2c4,       c2e4,
            c2b3, c2c3, c2d3,
      c2a2, c2b2, /*q*/ c2d2, c2e2, c2f2, c2g2, c2h2,
            c2b1, c2c1, c2d1;

   c2a2.source.colRow = c2a4.source.colRow = 0x21;
   c2b1.source.colRow = c2b2.source.colRow = 0x21;
   c2b3.source.colRow = c2c1.source.colRow = 0x21;
   c2c3.source.colRow = c2c4.source.colRow = 0x21;
   c2c5.source.colRow = c2c6.source.colRow = 0x21;
   c2c7.source.colRow = c2c8.source.colRow = 0x21;
   c2d1.source.colRow = c2d2.source.colRow = 0x21;
   c2d3.source.colRow = c2e2.source.colRow = 0x21;
   c2e4.source.colRow = c2f2.source.colRow = 0x21;
   c2f5.source.colRow = c2g2.source.colRow = 0x21;
   c2g6.source.colRow = c2h2.source.colRow = 0x21;
   c2h7.source.colRow = 0x21;

   c2a2.dest.colRow = 0x01;
   c2a4.dest.colRow = 0x03;
   c2b1.dest.colRow = 0x10;
   c2b2.dest.colRow = 0x11;
   c2b3.dest.colRow = 0x12;
   c2c1.dest.colRow = 0x20;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2c8.dest.colRow = 0x27;
   c2d1.dest.colRow = 0x30;
   c2d2.dest.colRow = 0x31;
   c2d3.dest.colRow = 0x32;
   c2e2.dest.colRow = 0x41;
   c2e4.dest.colRow = 0x43;
   c2f2.dest.colRow = 0x51;
   c2f5.dest.colRow = 0x54;
   c2g2.dest.colRow = 0x61;
   c2g6.dest.colRow = 0x65;
   c2h2.dest.colRow = 0x71;
   c2h7.dest.colRow = 0x76;

   c2b1.capture = c2c1.capture = PAWN;
   c2d1.capture = c2a2.capture = PAWN;
   c2a4.capture = c2c8.capture = PAWN;
   c2h2.capture = c2h7.capture = PAWN;

   c2a4.capture = c2b2.capture = SPACE;
   c2b3.capture = c2c3.capture = SPACE;
   c2c4.capture = c2c5.capture = SPACE;
   c2c6.capture = c2c7.capture = SPACE;
   c2d2.capture = c2d3.capture = SPACE;
   c2e2.capture = c2e4.capture = SPACE;
   c2f2.capture = c2f5.capture = SPACE;
   c2g2.capture = c2g6.capture = SPACE;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);  // many possible moves
   assertUnit(moves.find(c2a2) != moves.end());
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2c8) != moves.end());
   assertUnit(moves.find(c2d1) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());
   assertUnit(moves.find(c2h2) != moves.end());
   assertUnit(moves.find(c2h7) != moves.end());

   // TEARDOWN
   board.board[0][1] = board.board[0][3] = board.board[1][0] = nullptr;
   board.board[1][1] = board.board[1][2] = board.board[2][0] = nullptr;
   board.board[2][2] = board.board[2][3] = board.board[2][4] = nullptr;
   board.board[2][5] = board.board[2][6] = board.board[2][7] = nullptr;
   board.board[3][0] = board.board[3][1] = board.board[3][2] = nullptr;
   board.board[4][1] = board.board[4][3] = board.board[5][1] = nullptr;
   board.board[5][4] = board.board[6][1] = board.board[6][5] = nullptr;
   board.board[7][1] = board.board[6][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToCapture()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}


/*************************************
 * GET TYPE : queen
 * Input:
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}
