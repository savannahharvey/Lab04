/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/


#include "testBishop.h"
#include "pieceBishop.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      



/**************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3     p   p           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false);
   bishop.fWhite = true;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop;
   Black black(PAWN);
   black.position.colRow = 0x12;
   board.board[1][2] = &black;
   Black black1(PAWN);
   black1.position.colRow = 0x32;
   board.board[3][2] = &black1;
   Black black2(PAWN);
   black.position.colRow = 0x30;
   board.board[3][0] = &black2;
   Black black3(PAWN);
   black1.position.colRow = 0x10;
   board.board[1][0] = &black3;
   set <Move> moves;
   Move c2b3p;
   c2b3p.source.colRow = 0x21;
   c2b3p.dest.colRow = 0x12;
   c2b3p.capture = PAWN;
   Move c2d3p;
   c2d3p .source.colRow = 0x21;
   c2d3p.dest.colRow = 0x32;
   c2d3p.capture = PAWN;
   Move c2d0p;
   c2d0p.source.colRow = 0x21;
   c2d0p.dest.colRow = 0x30;
   c2d0p.capture = PAWN;
   Move c2b0p;
   c2b0p.source.colRow = 0x21;
   c2b0p.dest.colRow = 0x10;
   c2b0p.capture = PAWN;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);  // many possible moves
   assertUnit(moves.find(c2b3p) != moves.end());
   assertUnit(moves.find(c2d3p) != moves.end());
   assertUnit(moves.find(c2d0p) != moves.end());
   assertUnit(moves.find(c2b0p) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // white bishop
   board.board[1][2] = nullptr; // black pawn
   board.board[3][2] = nullptr; // black pawn
   board.board[3][0] = nullptr; // black pawn
   board.board[1][0] = nullptr; // black pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false);
   bishop.fWhite = true;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop;
   set <Move> moves;
   Move c2b3;
   c2b3.source.colRow = 0x21;
   c2b3.dest.colRow = 0x12;
   c2b3.capture = SPACE;
   Move c2d3;
   c2d3.source.colRow = 0x21;
   c2d3.dest.colRow = 0x32;
   c2d3.capture = SPACE;
   Move c2d0;
   c2d0.source.colRow = 0x21;
   c2d0.dest.colRow = 0x30;
   c2d0.capture = SPACE;
   Move c2b0;
   c2b0.source.colRow = 0x21;
   c2b0.dest.colRow = 0x10;
   c2b0.capture = SPACE;
   Move c2a4;
   c2a4.source.colRow = 0x21;
   c2a4.dest.colRow = 0x03;
   c2a4.capture = SPACE;
   Move c2e4;
   c2e4.source.colRow = 0x21;
   c2e4.dest.colRow = 0x43;
   c2e4.capture = SPACE;
   Move c2f5;
   c2f5.source.colRow = 0x21;
   c2f5.dest.colRow = 0x54;
   c2f5.capture = SPACE;
   Move c2g6;
   c2g6.source.colRow = 0x21;
   c2g6.dest.colRow = 0x65;
   c2g6.capture = SPACE;
   Move c2f7;
   c2f7.source.colRow = 0x21;
   c2f7.dest.colRow = 0x76;
   c2f7.capture = SPACE;


   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);  // many possible moves
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2d0) != moves.end());
   assertUnit(moves.find(c2b0) != moves.end());
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());
   assertUnit(moves.find(c2f7) != moves.end());


   // TEARDOWN
   board.board[2][1] = nullptr; // white bishop
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, true);
   bishop.fWhite = false;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop;
   Black black(PAWN);
   black.position.colRow = 0x03;
   board.board[0][3] = &black;
   Black black1(PAWN);
   black1.position.colRow = 0x76;
   board.board[7][6] = &black1;
   Black black2(PAWN);
   black.position.colRow = 0x30;
   board.board[3][0] = &black2;
   Black black3(PAWN);
   black1.position.colRow = 0x10;
   board.board[1][0] = &black3;
   set <Move> moves;
   Move c2b3;
   c2b3.source.colRow = 0x21;
   c2b3.dest.colRow = 0x12;
   c2b3.capture = SPACE;
   Move c2d3;
   c2d3.source.colRow = 0x21;
   c2d3.dest.colRow = 0x32;
   c2d3.capture = SPACE;
   Move c2e4;
   c2e4.source.colRow = 0x21;
   c2e4.dest.colRow = 0x43;
   c2e4.capture = SPACE;
   Move c2f5;
   c2f5.source.colRow = 0x21;
   c2f5.dest.colRow = 0x54;
   c2f5.capture = SPACE;
   Move c2g6;
   c2g6.source.colRow = 0x21;
   c2g6.dest.colRow = 0x65;
   c2g6.capture = SPACE;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);  // many possible moves
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // black bishop
   board.board[0][3] = nullptr; // black pawn
   board.board[7][6] = nullptr; // black pawn
   board.board[3][0] = nullptr; // black pawn
   board.board[1][0] = nullptr; // black pawn

}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false);
   bishop.fWhite = true;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop;
   Black black(PAWN);
   black.position.colRow = 0x03;
   board.board[0][3] = &black;
   Black black1(PAWN);
   black1.position.colRow = 0x76;
   board.board[7][6] = &black1;
   Black black2(PAWN);
   black.position.colRow = 0x30;
   board.board[3][0] = &black2;
   Black black3(PAWN);
   black1.position.colRow = 0x10;
   board.board[1][0] = &black3;
   set <Move> moves;
   Move c2b3;
   c2b3.source.colRow = 0x21;
   c2b3.dest.colRow = 0x12;
   c2b3.capture = SPACE;
   Move c2d3;
   c2d3.source.colRow = 0x21;
   c2d3.dest.colRow = 0x32;
   c2d3.capture = SPACE;
   Move c2d0;
   c2d0.source.colRow = 0x21;
   c2d0.dest.colRow = 0x30;
   c2d0.capture = PAWN;
   Move c2b0;
   c2b0.source.colRow = 0x21;
   c2b0.dest.colRow = 0x10;
   c2b0.capture = PAWN;
   Move c2a4;
   c2a4.source.colRow = 0x21;
   c2a4.dest.colRow = 0x03;
   c2a4.capture = PAWN;
   Move c2e4;
   c2e4.source.colRow = 0x21;
   c2e4.dest.colRow = 0x43;
   c2e4.capture = SPACE;
   Move c2f5;
   c2f5.source.colRow = 0x21;
   c2f5.dest.colRow = 0x54;
   c2f5.capture = SPACE;
   Move c2g6;
   c2g6.source.colRow = 0x21;
   c2g6.dest.colRow = 0x65;
   c2g6.capture = SPACE;
   Move c2f7;
   c2f7.source.colRow = 0x21;
   c2f7.dest.colRow = 0x76;
   c2f7.capture = PAWN;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);  // many possible moves
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2d0) != moves.end());
   assertUnit(moves.find(c2b0) != moves.end());
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());
   assertUnit(moves.find(c2f7) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // white bishop
   board.board[1][2] = nullptr; // black pawn
   board.board[3][2] = nullptr; // black pawn
   board.board[3][0] = nullptr; // black pawn
   board.board[1][0] = nullptr; // black pawn
}


/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
   // SETUP  
   const Bishop bishop(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = bishop.getType();

   // VERIFY
   assertUnit(pt == BISHOP);
}  // TEARDOWN