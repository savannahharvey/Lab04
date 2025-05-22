/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    McKay Larman
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
//#include "pieceRook.h"
#include "pieceKing.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   King king(3, 4, false);
   king.fWhite = true;
   king.position.colRow = 0x34;
   board.board[3][4] = &king;
   
   White white(PAWN);
   board.board[2][5] = board.board[3][5] = board.board[4][5] = &white;
   board.board[2][4] = /* hello there */   board.board[4][4] = &white;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = &white;

   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // we are blocked

   // TEARDOWN
   board.board[2][5] = board.board[3][5] = board.board[4][5] = nullptr;
   board.board[2][4] = board.board[3][4] = board.board[4][4] = nullptr;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   King king(3, 4, false);
   king.fWhite = true;
   king.position.colRow = 0x34;
   board.board[3][4] = &king;
   
   Black black(PAWN);
   board.board[2][5] = board.board[3][5] = board.board[4][5] = &black;
   board.board[2][4] = board.board[3][4] = board.board[4][4] = &black;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = &black;

   set <Move> moves;
   Move d5c6p, d5d6p, d5e6p;
   Move d5c5p,        d5e5p;
   Move d5c4p, d5d4p, d5e4p;
   
   d5c6p.source.colRow = d5d6p.source.colRow = d5e6p.source.colRow =
   d5c5p.source.colRow =                       d5e5p.source.colRow =
   d5c4p.source.colRow = d5d4p.source.colRow = d5e4p.source.colRow = 0x34;
   
   d5c6p.capture = d5d6p.capture = d5e6p.capture =
   d5c5p.capture =                 d5e5p.capture =
   d5c4p.capture = d5d4p.capture = d5e4p.capture = PAWN;
   
   d5c6p.dest.colRow = 0x25;
   d5d6p.dest.colRow = 0x35;
   d5e6p.dest.colRow = 0x45;
   d5c5p.dest.colRow = 0x24;
   d5e5p.dest.colRow = 0x44;
   d5c4p.dest.colRow = 0x23;
   d5d4p.dest.colRow = 0x33;
   d5e4p.dest.colRow = 0x43;
   

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);  // 8 moves
   assertUnit(moves.find(d5c6p) != moves.end());
   assertUnit(moves.find(d5d6p) != moves.end());
   assertUnit(moves.find(d5e6p) != moves.end());
   assertUnit(moves.find(d5c5p) != moves.end());
   assertUnit(moves.find(d5e5p) != moves.end());
   assertUnit(moves.find(d5c4p) != moves.end());
   assertUnit(moves.find(d5d4p) != moves.end());
   assertUnit(moves.find(d5e4p) != moves.end());

   // TEARDOWN
   board.board[2][5] = board.board[3][5] = board.board[4][5] = nullptr;
   board.board[2][4] = board.board[3][4] = board.board[4][4] = nullptr;
   board.board[2][3] = board.board[3][3] = board.board[4][3] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   King king(3, 4, false);
   king.fWhite = true;
   king.position.colRow = 0x34;
   board.board[3][4] = &king;

   set <Move> moves;
   Move d5c6, d5d6, d5e6;
   Move d5c5,       d5e5;
   Move d5c4, d5d4, d5e4;

   d5c6.source.colRow = d5d6.source.colRow = d5e6.source.colRow =
   d5c5.source.colRow =                      d5e5.source.colRow =
   d5c4.source.colRow = d5d4.source.colRow = d5e4.source.colRow = 0x34;
   
   d5c6.dest.colRow = 0x25;
   d5d6.dest.colRow = 0x35;
   d5e6.dest.colRow = 0x45;
   d5c5.dest.colRow = 0x24;
   d5e5.dest.colRow = 0x44;
   d5c4.dest.colRow = 0x23;
   d5d4.dest.colRow = 0x33;
   d5e4.dest.colRow = 0x43;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);  // 8 moves
   assertUnit(moves.find(d5c6) != moves.end());
   assertUnit(moves.find(d5d6) != moves.end());
   assertUnit(moves.find(d5e6) != moves.end());
   assertUnit(moves.find(d5c5) != moves.end());
   assertUnit(moves.find(d5e5) != moves.end());
   assertUnit(moves.find(d5c4) != moves.end());
   assertUnit(moves.find(d5d4) != moves.end());
   assertUnit(moves.find(d5e4) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   King king(0, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x00;
   board.board[0][0] = &king;

   set <Move> moves;
   Move a1a2, a1b2;
   Move       a1b1;

   a1a2.source.colRow = a1b2.source.colRow = a1b1.source.colRow = 0x00;
   
   a1a2.dest.colRow = 0x01;
   a1b2.dest.colRow = 0x11;
   a1b1.dest.colRow = 0x10;
   
   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);  // 3 moves
   assertUnit(moves.find(a1a2) != moves.end());
   assertUnit(moves.find(a1b2) != moves.end());
   assertUnit(moves.find(a1b1) != moves.end());

   // TEARDOWN
   board.board[0][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
   // SETUP
   BoardEmpty board;
   King king(4, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x40;
   board.board[4][0] = &king;
   
   White pawn(PAWN);
   White rook(ROOK);
   
   board.board[3][1] = board.board[4][1] = board.board[5][1] = &pawn;
   board.board[0][0] = board.board[7][0] = &rook;
   
   set <Move> moves;
   Move e1c1C, e1d1, e1f1, e1g1c;

   e1c1C.source.colRow = e1d1.source.colRow = e1f1.source.colRow = e1g1c.source.colRow = 0x40;
   
   e1c1C.dest.colRow = 0x20;
   e1d1.dest.colRow  = 0x30;
   e1f1.dest.colRow  = 0x50;
   e1g1c.dest.colRow = 0x60;
   
   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);  // 4 moves
   assertUnit(moves.find(e1c1C) != moves.end());
   assertUnit(moves.find(e1d1)  != moves.end());
   assertUnit(moves.find(e1f1)  != moves.end());
   assertUnit(moves.find(e1g1c) != moves.end());

   // TEARDOWN
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[0][0] = board.board[4][0] = board.board[7][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{  // SETUP
   BoardEmpty board;
   King king(4, 7, false);
   king.fWhite = true;
   king.position.colRow = 0x47;
   board.board[4][7] = &king;
   
   White pawn(PAWN);
   White rook(ROOK);
   
   board.board[3][6] = board.board[4][6] = board.board[5][6] = &pawn;
   board.board[0][7] = board.board[7][7] = &rook;
   
   set <Move> moves;
   Move e7c7C, e7d7, e7f7, e7g7c;

   e7c7C.source.colRow = e7d7.source.colRow = e7f7.source.colRow = e7g7c.source.colRow = 0x47;
   
   e7c7C.dest.colRow = 0x27;
   e7d7.dest.colRow  = 0x37;
   e7f7.dest.colRow  = 0x57;
   e7g7c.dest.colRow = 0x67;
   
   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);  // 4 moves
   assertUnit(moves.find(e7c7C) != moves.end());
   assertUnit(moves.find(e7d7)  != moves.end());
   assertUnit(moves.find(e7f7)  != moves.end());
   assertUnit(moves.find(e7g7c) != moves.end());

   // TEARDOWN
   board.board[3][6] = board.board[4][6] = board.board[5][6] = nullptr;
   board.board[0][7] = board.board[4][7] = board.board[7][7] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
   // SETUP
   BoardEmpty board;
   King king(4, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x40;
   king.nMoves = 2;
   board.board[4][0] = &king;
   
   White pawn(PAWN);
   White rook(ROOK);
   
   board.board[3][1] = board.board[4][1] = board.board[5][1] = &pawn;
   board.board[0][0] = board.board[7][0] = &rook;
   
   set <Move> moves;
   Move e1d1, e1f1;

   e1d1.source.colRow = e1f1.source.colRow = 0x40;
   
   e1d1.dest.colRow  = 0x30;
   e1f1.dest.colRow  = 0x50;
   
   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 moves
   assertUnit(moves.find(e1d1)  != moves.end());
   assertUnit(moves.find(e1f1)  != moves.end());

   // TEARDOWN
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[0][0] = board.board[4][0] = board.board[7][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
   // SETUP
   BoardEmpty board;
   King king(4, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x40;
   board.board[4][0] = &king;
   
   White pawn(PAWN);
   White rook(ROOK);
   rook.nMoves = 2;
   
   board.board[3][1] = board.board[4][1] = board.board[5][1] = &pawn;
   board.board[0][0] = board.board[7][0] = &rook;
   
   set <Move> moves;
   Move e1d1, e1f1;

   e1d1.source.colRow = e1f1.source.colRow = 0x40;
   
   e1d1.dest.colRow  = 0x30;
   e1f1.dest.colRow  = 0x50;
   
   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // 2 moves
   assertUnit(moves.find(e1d1)  != moves.end());
   assertUnit(moves.find(e1f1)  != moves.end());

   // TEARDOWN
   board.board[3][1] = board.board[4][1] = board.board[5][1] = nullptr;
   board.board[0][0] = board.board[4][0] = board.board[7][0] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{  // SETUP
   const King king(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = king.getType();

   // VERIFY
   assertUnit(pt == KING);
}  // TEARDOWN
