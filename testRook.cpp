/***********************************************************************
 * Source File:
 *    TEST ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the rook
 ************************************************************************/

#include "testRook.h"
#include "pieceRook.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3       p             3
 * 2     p(r)p           2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Rook rook(3, 4, false);
   rook.fWhite = true;
   rook.position.colRow = 0x21;
   board.board[2][1] = &rook;
   White white(PAWN);
   board.board[2][0] = board.board[1][1] = &white;
   board.board[2][2] = board.board[3][1] = &white;

   set <Move> moves;

   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // we are blocked

   // TEARDOWN
   board.board[2][0] = board.board[1][1] = nullptr;
   board.board[2][2] = board.board[3][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   . .(r). . . . .   2
 * 1       .             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Rook rook(3, 4, false);
   rook.fWhite = true;
   rook.position.colRow = 0x21;
   board.board[2][1] = &rook;

   set <Move> moves;
   Move           c2c8,
                  c2c7,
                  c2c6,
                  c2c5,
                  c2c4,
                  c2c3,
      c2a2, c2b2, /*q*/ c2d2, c2e2, c2f2, c2g2, c2h2,
                  c2d1;

   c2a2.source.colRow = c2b2.source.colRow = 0x21;
   c2c3.source.colRow = c2c4.source.colRow = 0x21;
   c2c5.source.colRow = c2c6.source.colRow = 0x21;
   c2c7.source.colRow = c2c8.source.colRow = 0x21;
   c2d1.source.colRow = c2d2.source.colRow = 0x21;
   c2e2.source.colRow = c2f2.source.colRow = 0x21;
   c2g2.source.colRow = c2h2.source.colRow = 0x21;

   c2a2.dest.colRow = 0x01;
   c2b2.dest.colRow = 0x11;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2c8.dest.colRow = 0x27;
   c2d1.dest.colRow = 0x20;
   c2d2.dest.colRow = 0x31;
   c2e2.dest.colRow = 0x41;
   c2f2.dest.colRow = 0x51;
   c2g2.dest.colRow = 0x61;
   c2h2.dest.colRow = 0x71;

   c2a2.capture = c2b2.capture = SPACE;
   c2c3.capture = c2c4.capture = SPACE;
   c2c5.capture = c2c6.capture = SPACE;
   c2c7.capture = c2c8.capture = SPACE;
   c2d1.capture = c2d2.capture = SPACE;
   c2e2.capture = c2f2.capture = SPACE;
   c2g2.capture = c2h2.capture = SPACE;
   
   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 14);  // many possible moves
   assertUnit(moves.find(c2a2) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2c8) != moves.end());
   assertUnit(moves.find(c2d1) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());
   assertUnit(moves.find(c2h2) != moves.end());

   // TEARDOWN
   board.board[0][1] = board.board[1][1] = board.board[2][0] = nullptr;
   board.board[2][2] = board.board[2][3] = board.board[2][4] = nullptr;
   board.board[2][5] = board.board[2][6] = board.board[2][7] = nullptr;
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[5][4] = board.board[6][1] = board.board[7][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   p .(r). . . . p   2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Rook rook(3, 4, false);
   rook.fWhite = true;
   rook.position.colRow = 0x21;
   board.board[2][1] = &rook;
   White white(PAWN);
   board.board[2][0] = board.board[2][7] = &white;
   board.board[0][1] = board.board[7][1] = &white;

   set <Move> moves;
   Move
            c2c7,
            c2c6,
            c2c5,
            c2c4,
            c2c3,
      c2b2, /*q*/ c2d2, c2e2, c2f2, c2g2;

   c2b2.source.colRow = c2c3.source.colRow = c2c4.source.colRow = 0x21;
   c2c5.source.colRow = c2c6.source.colRow = c2c7.source.colRow = 0x21;
   c2d2.source.colRow = c2e2.source.colRow = c2f2.source.colRow = 0x21;
   c2g2.source.colRow = 0x21;

   c2b2.dest.colRow = 0x11;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2d2.dest.colRow = 0x31;
   c2e2.dest.colRow = 0x41;
   c2f2.dest.colRow = 0x51;
   c2g2.dest.colRow = 0x61;

   c2b2.capture = c2c3.capture = c2c4.capture = SPACE;
   c2c5.capture = c2c6.capture = c2c7.capture = SPACE;
   c2d2.capture = c2e2.capture = c2f2.capture = SPACE;
   c2g2.capture = SPACE;

   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 10);  // many possible moves
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());

   // TEARDOWN
   board.board[0][1] = board.board[1][1] = board.board[2][0] = nullptr;
   board.board[2][2] = board.board[2][3] = board.board[2][4] = nullptr;
   board.board[2][5] = board.board[2][6] = board.board[2][7] = nullptr;
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[5][4] = board.board[6][1] = board.board[7][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   P .(r). . . . P   2
 * 1       P             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Rook rook(3, 4, true);
   rook.fWhite = false;
   rook.position.colRow = 0x21;
   board.board[2][1] = &rook;

   set <Move> moves;
   Move           c2c8,
                  c2c7,
                  c2c6,
                  c2c5,
                  c2c4,
                  c2c3,
      c2a2, c2b2, /*q*/ c2d2, c2e2, c2f2, c2g2, c2h2,
                  c2d1;

   c2a2.source.colRow = c2b2.source.colRow = 0x21;
   c2c3.source.colRow = c2c4.source.colRow = 0x21;
   c2c5.source.colRow = c2c6.source.colRow = 0x21;
   c2c7.source.colRow = c2c8.source.colRow = 0x21;
   c2d1.source.colRow = c2d2.source.colRow = 0x21;
   c2e2.source.colRow = c2f2.source.colRow = 0x21;
   c2g2.source.colRow = c2h2.source.colRow = 0x21;

   c2a2.dest.colRow = 0x01;
   c2b2.dest.colRow = 0x11;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2c8.dest.colRow = 0x27;
   c2d1.dest.colRow = 0x20;
   c2d2.dest.colRow = 0x31;
   c2e2.dest.colRow = 0x41;
   c2f2.dest.colRow = 0x51;
   c2g2.dest.colRow = 0x61;
   c2h2.dest.colRow = 0x71;

   c2d1.capture = c2a2.capture = PAWN;
   c2c8.capture = c2h2.capture = PAWN;

   c2b2.capture = c2c3.capture = c2c4.capture = SPACE;
   c2c5.capture = c2c6.capture = c2c7.capture = SPACE;
   c2d2.capture = c2e2.capture = c2f2.capture = SPACE;
   c2g2.capture = SPACE;

   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 14);  // many possible moves
   assertUnit(moves.find(c2a2) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2c8) != moves.end());
   assertUnit(moves.find(c2d1) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());
   assertUnit(moves.find(c2h2) != moves.end());

   // TEARDOWN
   board.board[0][1] = board.board[1][1] = board.board[2][0] = nullptr;
   board.board[2][2] = board.board[2][3] = board.board[2][4] = nullptr;
   board.board[2][5] = board.board[2][6] = board.board[2][7] = nullptr;
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[5][4] = board.board[6][1] = board.board[7][1] = nullptr;
}


/*************************************
 * GET TYPE : rook
 * Input:
 * Output: ROOK
 **************************************/
void TestRook::getType()
{
   // SETUP  
   const Rook rook(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = rook.getType();

   // VERIFY
   assertUnit(pt == ROOK);
}  // TEARDOWN