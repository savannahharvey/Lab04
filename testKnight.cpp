/***********************************************************************
 * Source File:
 *    TEST KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the knight
 ************************************************************************/

#include "testKnight.h"
#include "pieceKnight.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      

void TestKnight::clearBoard(BoardEmpty & board)
{
   for (int outer = 0; outer < 8; outer++)
   {
      for (int inner = 0; inner < 8; inner++)
         board.board[outer][inner] = nullptr;
   }
}

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3             p   .   3
  * 2           P         2
  * 1              (n)    1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestKnight::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   clearBoard(board);
   Knight knight(7, 7, false /*white*/); // we will reset all this.
   knight.fWhite = true;
   knight.position.colRow = 0x60;
   board.board[6][0] = &knight;
   Black black(PAWN);
   black.position.colRow = 0x41;
   board.board[4][1] = &black;
   White white(PAWN);
   white.position.colRow = 0x52;
   board.board[5][2] = &white;
   set <Move> moves;
   Move g1e2p;
   g1e2p.source.colRow = 0x60;
   g1e2p.dest.colRow = 0x41;
   g1e2p.capture = PAWN;
   Move g1h3;
   g1h3.source.colRow = 0x60;
   g1h3.dest.colRow = 0x72;
   g1h3.capture = SPACE;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // many possible moves
   assertUnit(moves.find(g1e2p) != moves.end());
   assertUnit(moves.find(g1h3 ) != moves.end());

   // TEARDOWN
   board.board[6][0] = nullptr; // white knight
   board.board[4][1] = nullptr; // black pawn
   board.board[5][2] = nullptr; // white pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8 7
 * 7       p   p         7 6  2/6 4/6
 * 6     p       p       6 5  1/5 5/5
 * 5        (n)          5 4    3/4 knight
 * 4     p       p       4 3  1/3 5/3
 * 3       p   p         3 2  2/2 4/2
 * 2                     2 1
 * 1                     1 0
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 *     0 1 2 3 4 5 6 7
 **************************************/
void TestKnight::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   clearBoard(board);
   Knight knight(7, 7, false /*white*/);
   knight.fWhite = true;
   knight.position.colRow = 0x34;
   board.board[3][4] = &knight;
   White white0(PAWN);
   board.board[2][6] = &white0;
   White white1(PAWN);
   board.board[4][6] = &white1;
   White white2(PAWN);
   board.board[5][5] = &white2;
   White white3(PAWN);
   board.board[5][3] = &white3;
   White white4(PAWN);
   board.board[4][2] = &white4;
   White white5(PAWN);
   board.board[2][2] = &white5;
   White white6(PAWN);
   board.board[1][3] = &white6;
   White white7(PAWN);
   board.board[1][5] = &white7;
   set <Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // 0 possible moves

   // TEARDOWN
   board.board[3][4] = nullptr; // white knight
   board.board[2][6] = nullptr; // white pawn
   board.board[4][6] = nullptr; // white pawn
   board.board[5][5] = nullptr; // white pawn
   board.board[5][3] = nullptr; // white pawn
   board.board[4][2] = nullptr; // white pawn
   board.board[2][2] = nullptr; // white pawn
   board.board[1][3] = nullptr; // white pawn
   board.board[1][5] = nullptr; // white pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   clearBoard(board);
   Knight knight(7, 7, true /*black*/);
   knight.fWhite = false;
   knight.position.colRow = 0x34;
   board.board[3][4] = &knight;
   White white0(PAWN);
   board.board[2][6] = &white0;
   White white1(PAWN);
   board.board[4][6] = &white1;
   White white2(PAWN);
   board.board[5][5] = &white2;
   White white3(PAWN);
   board.board[5][3] = &white3;
   White white4(PAWN);
   board.board[4][2] = &white4;
   White white5(PAWN);
   board.board[2][2] = &white5;
   White white6(PAWN);
   board.board[1][3] = &white6;
   White white7(PAWN);
   board.board[1][5] = &white7;
   set <Move> moves;
   Move d5c7p;
   d5c7p.source.colRow = 0x34;
   d5c7p.dest.colRow = 0x26;
   d5c7p.capture = PAWN;
   Move d5e7p;
   d5e7p.source.colRow = 0x34;
   d5e7p.dest.colRow = 0x46;
   d5e7p.capture = PAWN;
   Move d5f6p;
   d5f6p.source.colRow = 0x34;
   d5f6p.dest.colRow = 0x55;
   d5f6p.capture = PAWN;
   Move d5f4p;
   d5f4p.source.colRow = 0x34;
   d5f4p.dest.colRow = 0x53;
   d5f4p.capture = PAWN;
   Move d5e3p;
   d5e3p.source.colRow = 0x34;
   d5e3p.dest.colRow = 0x42;
   d5e3p.capture = PAWN;
   Move d5c3p;
   d5c3p.source.colRow = 0x34;
   d5c3p.dest.colRow = 0x22;
   d5c3p.capture = PAWN;
   Move d5d4p;
   d5d4p.source.colRow = 0x34;
   d5d4p.dest.colRow = 0x13;
   d5d4p.capture = PAWN;
   Move d5b6p;
   d5b6p.source.colRow = 0x34;
   d5b6p.dest.colRow = 0x15;
   d5b6p.capture = PAWN;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);  // 8 possible moves
   assertUnit(moves.find(d5c7p) != moves.end());
   assertUnit(moves.find(d5e7p) != moves.end());
   assertUnit(moves.find(d5f6p) != moves.end());
   assertUnit(moves.find(d5f4p) != moves.end());
   assertUnit(moves.find(d5e3p) != moves.end());
   assertUnit(moves.find(d5c3p) != moves.end());
   assertUnit(moves.find(d5d4p) != moves.end());
   assertUnit(moves.find(d5b6p) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr; // black knight
   board.board[2][6] = nullptr; // white pawn
   board.board[4][6] = nullptr; // white pawn
   board.board[5][5] = nullptr; // white pawn
   board.board[5][3] = nullptr; // white pawn
   board.board[4][2] = nullptr; // white pawn
   board.board[2][2] = nullptr; // white pawn
   board.board[1][3] = nullptr; // white pawn
   board.board[1][5] = nullptr; // white pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       .   .         7
 * 6     .       .       6
 * 5        (n)          5
 * 4     .       .       4
 * 3       .   .         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   clearBoard(board);
   Knight knight(7, 7, false /*white*/);
   knight.fWhite = true;
   knight.position.colRow = 0x34;
   board.board[3][4] = &knight;
   White space0(SPACE);
   board.board[2][6] = &space0;
   White space1(SPACE);
   board.board[4][6] = &space1;
   White space2(SPACE);
   board.board[5][5] = &space2;
   White space3(SPACE);
   board.board[5][3] = &space3;
   White space4(SPACE);
   board.board[4][2] = &space4;
   White space5(SPACE);
   board.board[2][2] = &space5;
   White space6(SPACE);
   board.board[1][3] = &space6;
   White space7(SPACE);
   board.board[1][5] = &space7;
   set <Move> moves;
   Move d5c7p;
   d5c7p.source.colRow = 0x34;
   d5c7p.dest.colRow = 0x26;
   d5c7p.capture = SPACE;
   Move d5e7p;
   d5e7p.source.colRow = 0x34;
   d5e7p.dest.colRow = 0x46;
   d5e7p.capture = SPACE;
   Move d5f6p;
   d5f6p.source.colRow = 0x34;
   d5f6p.dest.colRow = 0x55;
   d5f6p.capture = SPACE;
   Move d5f4p;
   d5f4p.source.colRow = 0x34;
   d5f4p.dest.colRow = 0x53;
   d5f4p.capture = SPACE;
   Move d5e3p;
   d5e3p.source.colRow = 0x34;
   d5e3p.dest.colRow = 0x42;
   d5e3p.capture = SPACE;
   Move d5c3p;
   d5c3p.source.colRow = 0x34;
   d5c3p.dest.colRow = 0x22;
   d5c3p.capture = SPACE;
   Move d5d4p;
   d5d4p.source.colRow = 0x34;
   d5d4p.dest.colRow = 0x13;
   d5d4p.capture = SPACE;
   Move d5b6p;
   d5b6p.source.colRow = 0x34;
   d5b6p.dest.colRow = 0x15;
   d5b6p.capture = SPACE;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);  // 8 possible moves
   assertUnit(moves.find(d5c7p) != moves.end());
   assertUnit(moves.find(d5e7p) != moves.end());
   assertUnit(moves.find(d5f6p) != moves.end());
   assertUnit(moves.find(d5f4p) != moves.end());
   assertUnit(moves.find(d5e3p) != moves.end());
   assertUnit(moves.find(d5c3p) != moves.end());
   assertUnit(moves.find(d5d4p) != moves.end());
   assertUnit(moves.find(d5b6p) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr; // white knight
   board.board[2][6] = nullptr; // space
   board.board[4][6] = nullptr; // space
   board.board[5][5] = nullptr; // space
   board.board[5][3] = nullptr; // space
   board.board[4][2] = nullptr; // space
   board.board[2][2] = nullptr; // space
   board.board[1][3] = nullptr; // space
   board.board[1][5] = nullptr; // space
}



/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{
   // SETUP  
   const Knight knight(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = knight.getType();

   // VERIFY
   assertUnit(pt == KNIGHT);
}  // TEARDOWN
