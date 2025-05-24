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
#include "piecePawn.h"
#include "pieceRook.h"
#include "pieceBishop.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include <cassert>

/*
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
 ********************************************************
void TestBoard::move_pawnSimple()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x01;
   Move a2a3;
   a2a3.source.colRow = 0x01;
   a2a3.dest.colRow = 0x02;
   a2a3.capture = SPACE;
   
   // EXERCISE
   board.move(a2a3);

   // VERIFY
   assertUnit((board.board[0][1]->getType()) == SPACE);
   assertUnit((board.board[0][2]->getType()) == PAWN);
   
   // TEARDOWN
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
 ********************************************************
void TestBoard::move_pawnCapture()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x05;
   Rook rook(0, 0, true);
   rook.fWhite = false;
   rook.position.colRow = 0x16;
   Move a6b7;
   a6b7.source.colRow = 0x05;
   a6b7.dest.colRow = 0x16;
   a6b7.capture = ROOK;

   // EXERCISE
   board.move(a6b7);

   // VERIFY
   assertUnit(board.board[0][5]->getType() == SPACE);
   assertUnit(board.board[1][6]->getType() == PAWN);

   // TEARDOWN
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
 ********************************************************
void TestBoard::move_pawnDouble()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x41;
   Move e2e4;
   e2e4.source.colRow = 0x41;
   e2e4.dest.colRow = 0x43;
   e2e4.capture = SPACE;

   // EXERCISE
   board.move(e2e4);

   // VERIFY
   assertUnit(board.board[4][1]->getType() == SPACE);
   assertUnit(board.board[4][3]->getType() == PAWN);

   // TEARDOWN
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
 ********************************************************
void TestBoard::move_pawnEnpassant()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x04;
   Pawn pawn(0, 0, true);
   pawn.fWhite = false;
   pawn.position.colRow = 0x14;
   Move a5b6;
   a5b6.source.colRow = 0x04;
   a5b6.dest.colRow = 0x15;
   a5b6.capture = PAWN;

   // EXERCISE
   board.move(a5b6);

   // VERIFY
   assertUnit(board.board[0][4]->getType() == SPACE);
   assertUnit(board.board[1][4]->getType() == SPACE);
   assertUnit(board.board[1][5]->getType() == PAWN);

   // TEARDOWN
   board.board[0][4] = board.board[1][4] = nullptr;
   board.board[1][5] = nullptr;
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
 ********************************************************
void TestBoard::move_pawnPromotion()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(0, 0, false);
   pawn.fWhite = true;
   pawn.position.colRow = 0x06;
   Move a7a8;
   a7a8.source.colRow = 0x06;
   a7a8.dest.colRow = 0x07;
   a7a8.capture = SPACE;

   // EXERCISE
   board.move(a7a8);

   // VERIFY
   assertUnit(board.board[0][6]->getType() == SPACE);
   assertUnit(board.board[0][7]->getType() == ROOK);

   // TEARDOWN
   board.board[4][1] = board.board[4][3] = nullptr;
}
*/

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
   BoardEmpty board;
   Rook rook(0, 0, false);
   rook.fWhite = true;
   rook.position.colRow = 0x44;
   Move e5a5;
   e5a5.source.colRow = 0x44;
   e5a5.dest.colRow = 0x04;
   e5a5.capture = SPACE;

   // EXERCISE
   board.move(e5a5);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[0][4]->getType() == ROOK);

   // TEARDOWN
   board.board[4][4] = board.board[0][4] = nullptr;
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
   BoardEmpty board;
   Rook rook(0, 0, false);
   rook.fWhite = true;
   rook.position.colRow = 0x44;
   Bishop bishop(0, 0, true);
   bishop.fWhite = false;
   bishop.position.colRow = 0x04;
   Move e5a5;
   e5a5.source.colRow = 0x44;
   e5a5.dest.colRow = 0x04;
   e5a5.capture = BISHOP;

   // EXERCISE
   board.move(e5a5);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[0][4]->getType() == ROOK);

   // TEARDOWN
   board.board[4][4] = board.board[0][4] = nullptr;
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
   BoardEmpty board;
   Bishop bishop(0, 0, false);
   bishop.fWhite = true;
   bishop.position.colRow = 0x44;
   Move e5g3;
   e5g3.source.colRow = 0x44;
   e5g3.dest.colRow = 0x62;
   e5g3.capture = BISHOP;

   // EXERCISE
   board.move(e5g3);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[0][4]->getType() == ROOK);

   // TEARDOWN
   board.board[4][4] = board.board[6][2] = nullptr;
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
   BoardEmpty board;
   Bishop bishop(0, 0, false);
   bishop.fWhite = true;
   bishop.position.colRow = 0x44;
   Queen queen(0, 0, true);
   queen.fWhite = false;
   queen.position.colRow = 0x62;
   Move e5g3;
   e5g3.source.colRow = 0x44;
   e5g3.dest.colRow = 0x62;
   e5g3.capture = BISHOP;

   // EXERCISE
   board.move(e5g3);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[6][2]->getType() == ROOK);

   // TEARDOWN
   board.board[4][4] = board.board[0][4] = nullptr;
}

/********************************************************
*    e5g3
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
* |                     |       |                     |
* 8                     8       8                     8
* 7                     7       7                     7
* 6                     6       6                     6
* 5          (q)        5       5           .         5
* 4                     4  -->  4                     4
* 3                .    3       3               q     3
* 2                     2       2                     2
* 1                     1       1                     1
* |                     |       |                     |
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
********************************************************/
void TestBoard::move_queenSlide()
{
   // SETUP
   BoardEmpty board;
   Queen queen(0, 0, false);
   queen.fWhite = true;
   queen.position.colRow = 0x44;
   Move e5g3;
   e5g3.source.colRow = 0x44;
   e5g3.dest.colRow = 0x62;
   e5g3.capture = SPACE;

   // EXERCISE
   board.move(e5g3);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[6][2]->getType() == QUEEN);

   // TEARDOWN
   board.board[4][4] = board.board[0][4] = nullptr;
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
   BoardEmpty board;
   Queen queen(0, 0, false);
   queen.fWhite = true;
   queen.position.colRow = 0x44;
   Bishop bishop(0, 0, true);
   bishop.fWhite = false;
   bishop.position.colRow = 0x04;
   Move e5a5;
   e5a5.source.colRow = 0x44;
   e5a5.dest.colRow = 0x04;
   e5a5.capture = BISHOP;

   // EXERCISE
   board.move(e5a5);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[0][4]->getType() == QUEEN);

   // TEARDOWN
   board.board[4][4] = board.board[0][4] = nullptr;
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
   BoardEmpty board;
   King king(0, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x40;
   Move e1f1;
   e1f1.source.colRow = 0x40;
   e1f1.dest.colRow = 0x50;
   e1f1.capture = SPACE;

   // EXERCISE
   board.move(e1f1);

   // VERIFY
   assertUnit(board.board[4][0]->getType() == SPACE);
   assertUnit(board.board[5][0]->getType() == KING);

   // TEARDOWN
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
   BoardEmpty board;
   King king(0, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x40;
   Rook rook(0, 0, true);
   rook.fWhite = false;
   rook.position.colRow = 0x50;
   Move e1f1;
   e1f1.source.colRow = 0x40;
   e1f1.dest.colRow = 0x50;
   e1f1.capture = ROOK;

   // EXERCISE
   board.move(e1f1);

   // VERIFY
   assertUnit(board.board[4][0]->getType() == SPACE);
   assertUnit(board.board[5][0]->getType() == KING);

   // TEARDOWN
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
   BoardEmpty board;
   King king(0, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x40;
   Rook rook(0, 0, false);
   rook.fWhite = true;
   rook.position.colRow = 0x70;
   Move e1g1;
   e1g1.source.colRow = 0x40;
   e1g1.dest.colRow = 0x60;
   e1g1.capture = SPACE;

   // EXERCISE
   board.move(e1g1);

   // VERIFY
   assertUnit(board.board[4][0]->getType() == SPACE);
   assertUnit(board.board[6][0]->getType() == KING);
   assertUnit(board.board[5][0]->getType() == ROOK);
   assertUnit(board.board[7][0]->getType() == SPACE);

   // TEARDOWN
   board.board[4][0] = board.board[5][0] = nullptr;
   board.board[6][0] = board.board[7][0] = nullptr;
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
   BoardEmpty board;
   King king(0, 0, false);
   king.fWhite = true;
   king.position.colRow = 0x40;
   Rook rook(7, 7, false);
   rook.fWhite = true;
   rook.position.colRow = 0x00;
   Move e1g1;
   e1g1.source.colRow = 0x40;
   e1g1.dest.colRow = 0x20;
   e1g1.capture = SPACE;

   // EXERCISE
   board.move(e1g1);

   // VERIFY
   assertUnit(board.board[0][0]->getType() == SPACE);
   assertUnit(board.board[1][0]->getType() == SPACE);
   assertUnit(board.board[2][0]->getType() == KING);
   assertUnit(board.board[3][0]->getType() == ROOK);
   assertUnit(board.board[4][0]->getType() == SPACE);

   // TEARDOWN
   board.board[4][0] = board.board[5][0] = nullptr;
   board.board[6][0] = board.board[7][0] = nullptr;
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

   // EXERCISE
   Board board;

   // VERIFY
   assertUnit(board.board[0][0]->getType() == ROOK);
   assertUnit(board.board[0][1]->getType() == PAWN);
   assertUnit(board.board[0][2]->getType() == SPACE);
   assertUnit(board.board[0][3]->getType() == SPACE);
   assertUnit(board.board[0][4]->getType() == SPACE);
   assertUnit(board.board[0][5]->getType() == SPACE);
   assertUnit(board.board[0][6]->getType() == PAWN);
   assertUnit(board.board[0][7]->getType() == ROOK);
   assertUnit(board.board[1][0]->getType() == KNIGHT);
   assertUnit(board.board[1][0]->getType() == PAWN);
   assertUnit(board.board[1][1]->getType() == SPACE);
   assertUnit(board.board[1][2]->getType() == SPACE);
   assertUnit(board.board[1][3]->getType() == SPACE);
   assertUnit(board.board[1][4]->getType() == SPACE);
   assertUnit(board.board[1][5]->getType() == SPACE);
   assertUnit(board.board[1][6]->getType() == PAWN);
   assertUnit(board.board[1][7]->getType() == KNIGHT);
   assertUnit(board.board[2][0]->getType() == BISHOP);
   assertUnit(board.board[2][1]->getType() == PAWN);
   assertUnit(board.board[2][2]->getType() == SPACE);
   assertUnit(board.board[2][3]->getType() == SPACE);
   assertUnit(board.board[2][4]->getType() == SPACE);
   assertUnit(board.board[2][5]->getType() == SPACE);
   assertUnit(board.board[2][6]->getType() == PAWN);
   assertUnit(board.board[2][7]->getType() == BISHOP);
   assertUnit(board.board[3][0]->getType() == QUEEN);
   assertUnit(board.board[3][1]->getType() == PAWN);
   assertUnit(board.board[3][2]->getType() == SPACE);
   assertUnit(board.board[3][3]->getType() == SPACE);
   assertUnit(board.board[3][4]->getType() == SPACE);
   assertUnit(board.board[3][5]->getType() == SPACE);
   assertUnit(board.board[3][6]->getType() == PAWN);
   assertUnit(board.board[3][7]->getType() == QUEEN);
   assertUnit(board.board[4][0]->getType() == KING);
   assertUnit(board.board[4][1]->getType() == PAWN);
   assertUnit(board.board[4][2]->getType() == SPACE);
   assertUnit(board.board[4][3]->getType() == SPACE);
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[4][5]->getType() == SPACE);
   assertUnit(board.board[4][6]->getType() == PAWN);
   assertUnit(board.board[4][7]->getType() == KING);
   assertUnit(board.board[5][0]->getType() == BISHOP);
   assertUnit(board.board[5][1]->getType() == PAWN);
   assertUnit(board.board[5][2]->getType() == SPACE);
   assertUnit(board.board[5][3]->getType() == SPACE);
   assertUnit(board.board[5][4]->getType() == SPACE);
   assertUnit(board.board[5][5]->getType() == SPACE);
   assertUnit(board.board[5][6]->getType() == PAWN);
   assertUnit(board.board[5][7]->getType() == BISHOP);
   assertUnit(board.board[6][0]->getType() == KNIGHT);
   assertUnit(board.board[6][1]->getType() == PAWN);
   assertUnit(board.board[6][2]->getType() == SPACE);
   assertUnit(board.board[6][3]->getType() == SPACE);
   assertUnit(board.board[6][4]->getType() == SPACE);
   assertUnit(board.board[6][5]->getType() == SPACE);
   assertUnit(board.board[6][6]->getType() == PAWN);
   assertUnit(board.board[6][7]->getType() == KNIGHT);
   assertUnit(board.board[7][0]->getType() == ROOK);
   assertUnit(board.board[7][1]->getType() == PAWN);
   assertUnit(board.board[7][2]->getType() == SPACE);
   assertUnit(board.board[7][3]->getType() == SPACE);
   assertUnit(board.board[7][4]->getType() == SPACE);
   assertUnit(board.board[7][5]->getType() == SPACE);
   assertUnit(board.board[7][6]->getType() == PAWN);
   assertUnit(board.board[7][7]->getType() == ROOK);
   // TEARDOWN
   board.board[0][0] = board.board[0][1] = nullptr;
   board.board[0][2] = board.board[0][3] = nullptr;
   board.board[0][4] = board.board[0][5] = nullptr;
   board.board[0][6] = board.board[0][7] = nullptr;
   board.board[1][0] = board.board[1][1] = nullptr;
   board.board[1][2] = board.board[1][3] = nullptr;
   board.board[1][4] = board.board[1][5] = nullptr;
   board.board[1][6] = board.board[1][7] = nullptr;
   board.board[2][0] = board.board[2][1] = nullptr;
   board.board[2][2] = board.board[2][3] = nullptr;
   board.board[2][4] = board.board[2][5] = nullptr;
   board.board[2][6] = board.board[2][7] = nullptr;
   board.board[3][0] = board.board[3][1] = nullptr;
   board.board[3][2] = board.board[3][3] = nullptr;
   board.board[3][4] = board.board[3][5] = nullptr;
   board.board[3][6] = board.board[3][7] = nullptr;
   board.board[4][0] = board.board[4][1] = nullptr;
   board.board[4][2] = board.board[4][3] = nullptr;
   board.board[4][4] = board.board[4][5] = nullptr;
   board.board[4][6] = board.board[4][7] = nullptr;
   board.board[5][0] = board.board[5][1] = nullptr;
   board.board[5][2] = board.board[5][3] = nullptr;
   board.board[5][4] = board.board[5][5] = nullptr;
   board.board[5][6] = board.board[5][7] = nullptr;
   board.board[6][0] = board.board[6][1] = nullptr;
   board.board[6][2] = board.board[6][3] = nullptr;
   board.board[6][4] = board.board[6][5] = nullptr;
   board.board[6][6] = board.board[6][7] = nullptr;
   board.board[7][0] = board.board[7][1] = nullptr;
   board.board[7][2] = board.board[7][3] = nullptr;
   board.board[7][4] = board.board[7][5] = nullptr;
   board.board[7][6] = board.board[7][7] = nullptr;
}


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
   e5c6.source.colRow = 0x44;
   e5c6.dest.colRow = 0x25;
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
   e5c6r.source.colRow = 0x44;
   e5c6r.dest.colRow = 0x25;
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


