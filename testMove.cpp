/***********************************************************************
 * Header File:
 *    TEST MOVE
 * Author:
 *    McKay Larman
 * Summary:
 *    test the Move class
 ************************************************************************/


#include "testMove.h"
#include "move.h"
#include <cassert>

 /*************************************
  * Constructor : default
  * Input:
  * Output: source=INVALID
  *         dest  =INVALID
  **************************************/
void TestMove::constructor_default()
{  // Setup
   // Exercise
   Move m = Move();
   // Verify
   assertUnit(m.source.colRow == 0x99);
   assertUnit(m.dest.colRow == 0x99);
}  // Teardown

 /*************************************
  * CONSTRUCTOR : standard string move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::constructString_simple()
{  // Setup
   string str = "e5e6";
   char* text = &str[0];
   // Exercise
   Move m(text);
   // Verify
   assertUnit(m.source.colRow == 0x44);
   assertUnit(m.dest.colRow == 0x45);
   assertUnit(m.moveType == Move::MOVE);
}  // Teardown

 /*************************************
  * READ simple move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::read_simple()
{
   // Setup
   string str = "e5e6";
   char* textRhs = &str[0];
   // Exercise
   Move m = textRhs;
   // Verify
   assertUnit(m.source.colRow == 0x44);
   assertUnit(m.dest.colRow == 0x45);
   assertUnit(m.moveType == Move::MOVE);
}  // Teardown

 /*************************************
  * READ capture move
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =3,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::read_capture()
{  // Setup
   string str = "e5d6r";
   char* textRhs = &str[0];
   // Exercise
   Move m = textRhs;
   // Verify
   assertUnit(m.source.colRow == 0x44);
   assertUnit(m.dest.colRow == 0x35);
   assertUnit(m.moveType == Move::MOVE);
   assertUnit(m.capture == ROOK);
}  // Teardown

 /*************************************
  * READ enpassant move
  * Input:  e5f6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::read_enpassant()
{  // Setup
   string str = "e5f6E";
   char* textRhs = &str[0];
   // Exercise
   Move m = textRhs;
   // Verify
   assertUnit(m.source.colRow == 0x44);
   assertUnit(m.dest.colRow == 0x55);
   assertUnit(m.moveType == Move::ENPASSANT);
}  // Teardown

 /*************************************
  * READ king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::read_castleKing()
{  // Setup
   string str = "e1g1c";
   char* textRhs = &str[0];
   // Exercise
   Move m = textRhs;
   // Verify
   assertUnit(m.source.colRow == 0x40);
   assertUnit(m.dest.colRow == 0x60);
   assertUnit(m.moveType == Move::CASTLE_KING);
}  // Teardown

 /*************************************
  * READ queen side castle
  * Input:  e1c1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::read_castleQueen()
{  // Setup
   string str = "e1c1C";
   char* textRhs = &str[0];
   // Exercise
   Move m = textRhs;
   // Verify
   assertUnit(m.source.colRow == 0x40);
   assertUnit(m.dest.colRow == 0x20);
   assertUnit(m.moveType == Move::CASTLE_QUEEN);
}  // Teardown

 /*************************************
  * ASSIGN simple move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::assign_simple()
{  // Setup
   Move moveLhs;
   string str = "e5e6";
   char* textRhs = &str[0];
   // Exercise
   moveLhs = textRhs;
   // Verify
   assertUnit(moveLhs.source.colRow == 0x44);
   assertUnit(moveLhs.dest.colRow == 0x45);
   assertUnit(moveLhs.moveType == Move::MOVE);
}  // Teardown

 /*************************************
  * ASSIGN capture move
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =3,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::assign_capture()
{  // Setup
   Move moveLhs;
   string str = "e5d6r";
   char* textRhs = &str[0];
   // Exercise
   moveLhs = textRhs;
   // Verify
   assertUnit(moveLhs.source.colRow == 0x44);
   assertUnit(moveLhs.dest.colRow == 0x35);
   assertUnit(moveLhs.moveType == Move::MOVE);
   assertUnit(moveLhs.capture == PieceType::ROOK);
}  // Teardown

 /*************************************
  * ASSIGN enpassant move
  * Input:  e5f6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::assign_enpassant()
{  // Setup
   Move moveLhs;
   string str = "e5f6E";
   char* textRhs = &str[0];
   // Exercise
   moveLhs = textRhs;
   // Verify
   assertUnit(moveLhs.source.colRow == 0x44);
   assertUnit(moveLhs.dest.colRow == 0x55);
   assertUnit(moveLhs.moveType == Move::ENPASSANT);
}  // Teardown

 /*************************************
  * ASSIGN king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::assign_castleKing()
{  // Setup
   Move moveLhs;
   string str = "e1g1c";
   char* textRhs = &str[0];
   // Exercise
   moveLhs = textRhs;
   // Verify
   assertUnit(moveLhs.source.colRow == 0x40);
   assertUnit(moveLhs.dest.colRow == 0x60);
   assertUnit(moveLhs.moveType == Move::CASTLE_KING);
}  // Teardown

 /*************************************
  * ASSIGN queen side castle
  * Input:  e1c1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::assign_castleQueen()
{  // Setup
   Move moveLhs;
   string str = "e1c1C";
   char* textRhs = &str[0];
   // Exercise
   moveLhs = textRhs;
   // Verify
   assertUnit(moveLhs.source.colRow == 0x40);
   assertUnit(moveLhs.dest.colRow == 0x20);
   assertUnit(moveLhs.moveType == Move::CASTLE_QUEEN);
}  // Teardown

 /*************************************
  * GET TEXT simple move
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  * Output:  e5e6
  **************************************/
void TestMove::getText_simple()
{  // Setup
   Move m;
   m.source.colRow = 0x44;
   m.dest.colRow = 0x45;
   m.moveType = Move::MOVE;
   // Exercise
   string text = m.getText();
   // Verify
   assertUnit(text == "e5e6");
}  // Teardown

 /*************************************
  * GET TEXT capture
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  *         capture=ROOK
  * Output:  e5e6r
  **************************************/
void TestMove::getText_capture()
{  // Setup
   Move m;
   m.source.colRow = 0x44;
   m.dest.colRow = 0x45;
   m.moveType = Move::MOVE;
   m.capture = ROOK;
   // Exercise
   string text = m.getText();
   // Verify
   assertUnit(text == "e5e6r");
}  // Teardown

 /*************************************
  * GET TEXT en passant
  * Input : source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  *         capture=PAWN
  * Output:  e5f6E
  **************************************/
void TestMove::getText_enpassant()
{  // Setup
   Move m;
   m.source.colRow = 0x44;
   m.dest.colRow = 0x55;
   m.moveType = Move::ENPASSANT;
   m.capture = PAWN;
   // Exercise
   string text = m.getText();
   // Verify
   assertUnit(text == "e5f6E");
}  // Teardown

 /*************************************
  * GET TEXT king side castle
  * Input : source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  * Output:  e1g1c
  **************************************/
void TestMove::getText_castleKing()
{  // Setup
   Move m;
   m.source.colRow = 0x40;
   m.dest.colRow = 0x60;
   m.moveType = Move::CASTLE_KING;
   // Exercise
   string text = m.getText();
   // Verify
   assertUnit(text == "e1g1c");
}  // Teardown

 /*************************************
  * GET TEXT queen side castle
  * Input : source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  * Output:  e1c1C
  **************************************/
void TestMove::getText_castleQueen()
{  // Setup
   Move m;
   m.source.colRow = 0x40;
   m.dest.colRow = 0x20;
   m.moveType = Move::CASTLE_QUEEN;
   // Exercise
   string text = m.getText();
   // Verify
   assertUnit(text == "e1c1C");
}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE space
  * Input :  SPACE
  * Output:  ' '
  **************************************/
void TestMove::letterFromPieceType_space()
{  // Setup
   char type;
   Move m;
   // exercise
   type = m.letterFromPieceType(PieceType::SPACE);
   // Verify
   assertUnit(type == ' ');
}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE pawn
  * Input : PAWN
  * Output:  'p'
  **************************************/
void TestMove::letterFromPieceType_pawn()
{  // Setup
   char type;
   Move m;
   // exercise
   type = m.letterFromPieceType(PieceType::PAWN);
   // Verify
   assertUnit(type == 'p');
}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE bishop
  * Input : BISHOP
  * Output:  'b'
  **************************************/
void TestMove::letterFromPieceType_bishop()
{  // Setup
   char type;
   Move m;
   // exercise
   type = m.letterFromPieceType(PieceType::BISHOP);
   // Verify
   assertUnit(type == 'b');
}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE knight
  * Input : KNIGHT
  * Output:  'n'
  **************************************/
void TestMove::letterFromPieceType_knight()
{  // Setup
   char type;
   Move m;
   // exercise
   type = m.letterFromPieceType(PieceType::KNIGHT);
   // Verify
   assertUnit(type == 'n');
}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE rook
  * Input : ROOK
  * Output:  'r'
  **************************************/
void TestMove::letterFromPieceType_rook()
{  // Setup
   char type;
   Move m;
   // exercise
   type = m.letterFromPieceType(PieceType::ROOK);
   // Verify
   assertUnit(type == 'r');
}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE queen
  * Input : QUEEN
  * Output:  'q'
  **************************************/
void TestMove::letterFromPieceType_queen()
{  // Setup
   char type;
   Move m;
   // exercise
   type = m.letterFromPieceType(PieceType::QUEEN);
   // Verify
   assertUnit(type == 'q');
}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE king
  * Input : KING
  * Output:  'k'
  **************************************/
void TestMove::letterFromPieceType_king()
{  // Setup
   char type;
   Move m;
   // exercise
   type = m.letterFromPieceType(PieceType::KING);
   // Verify
   assertUnit(type == 'k');
}  // Teardown

 /*************************************
  * PIECE TYPE FROM LETTER pawn
  * Input : 'p'
  * Output:  PAWN
  **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{  // Setup
   PieceType piece;
   Move m;
   // Exercise
   piece = m.pieceTypeFromLetter('p');
   // Verify
   assertUnit(piece == PAWN);
}  // Teardown

 /*************************************
  * PIECE TYPE FROM LETTER bishop
  * Input : 'b'
  * Output:  BISHOP
  **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{  // Setup
   PieceType piece;
   Move m;
   // Exercise
   piece = m.pieceTypeFromLetter('b');
   // Verify
   assertUnit(piece == BISHOP);
}  // Teardown

 /*************************************
  * PIECE TYPE FROM LETTER knight
  * Input : 'n'
  * Output:  KNIGHT
  **************************************/
void TestMove::pieceTypeFromLetter_knight()
{  // Setup
   PieceType piece;
   Move m;
   // Exercise
   piece = m.pieceTypeFromLetter('n');
   // Verify
   assertUnit(piece == KNIGHT);
}  // Teardown

 /*************************************
  * PIECE TYPE FROM LETTER rook
  * Input : 'r'
  * Output:  ROOK
  **************************************/
void TestMove::pieceTypeFromLetter_rook()
{  // Setup
   PieceType piece;
   Move m;
   // Exercise
   piece = m.pieceTypeFromLetter('r');
   // Verify
   assertUnit(piece == ROOK);
}  // Teardown

 /*************************************
  * PIECE TYPE FROM LETTER queen
  * Input : 'q'
  * Output:  QUEEN
  **************************************/
void TestMove::pieceTypeFromLetter_queen()
{  // Setup
   PieceType piece;
   Move m;
   // Exercise
   piece = m.pieceTypeFromLetter('q');
   // Verify
   assertUnit(piece == QUEEN);
}  // Teardown

 /*************************************
  * PIECE TYPE FROM LETTER king
  * Input : 'k'
  * Output:  KING
  **************************************/
void TestMove::pieceTypeFromLetter_king()
{  // Setup
   PieceType piece;
   Move m;
   // Exercise
   piece = m.pieceTypeFromLetter('k');
   // Verify
   assertUnit(piece == KING);
}  // Teardown


 /*************************************
  * EQUAL - NOT
  * Input : b2b4 == b2b5
  * Output: false
  **************************************/
void TestMove::equal_not()
{  // Setup
   Move moveLhs;
   moveLhs.source.colRow = 0x11;
   moveLhs.dest.colRow = 0x13;
   Move moveRhs;
   moveRhs.source.colRow = 0x11;
   moveRhs.dest.colRow = 0x14;
   bool response;
   // Exercise
   response = moveLhs == moveRhs;
   // Verify
   assertUnit(response == false);
}  // Teardown

 /*************************************
  * EQUAL - EQUALS
  * Input : b2b4 == b2b4
  * Output: true
  **************************************/
void TestMove::equal_equals()
{  // Setup
   Move moveLhs;
   moveLhs.source.colRow = 0x11;
   moveLhs.dest.colRow = 0x13;
   Move moveRhs;
   moveRhs.source.colRow = 0x11;
   moveRhs.dest.colRow = 0x13;
   bool response;
   // Exercise
   response = moveLhs == moveRhs;
   // Verify
   assertUnit(response == true);
}  // Teardown

 /*************************************
  * LESS THAN - LESS THAN
  * Input : b2b2 < b2b4
  * Output: true
  *    Note that the less-than operator is needed
  *    so std::set<T> can sort the elements. Thus,
  *    any T in a set must define less-than. In this
  *    case, I defined it according to the
  *     destination's Position's location.
  **************************************/
void TestMove::lessthan_lessthan()
{  // Setup
   Move moveLhs;
   moveLhs.source.colRow = 0x11;
   moveLhs.dest.colRow = 0x11;
   Move moveRhs;
   moveRhs.source.colRow = 0x11;
   moveRhs.dest.colRow = 0x13;
   bool response;
   // Exercise
   response = moveLhs < moveRhs;
   // Verify
   assertUnit(response == true);
}  // Teardown

 /*************************************
  * LESS THAN - EQUALS
  * Input : b2b4 < b2b4
  * Output: false
  **************************************/
void TestMove::lessthan_equals()
{  // Setup
   Move moveLhs;
   moveLhs.source.colRow = 0x11;
   moveLhs.dest.colRow = 0x13;
   Move moveRhs;
   moveRhs.source.colRow = 0x11;
   moveRhs.dest.colRow = 0x13;
   bool response;
   // Exercise
   response = moveLhs < moveRhs;
   // Verify
   assertUnit(response == false);
}  // Teardown


 /*************************************
  * LESS THAN - GREATAER THAN
  * Input : b2b4 < b2b2
  * Output: false
  **************************************/
void TestMove::lessthan_greaterthan()
{  // Setup
   Move moveLhs;
   moveLhs.source.colRow = 0x11;
   moveLhs.dest.colRow = 0x13;
   Move moveRhs;
   moveRhs.source.colRow = 0x11;
   moveRhs.dest.colRow = 0x11;
   bool response;
   // Exercise
   response = moveLhs < moveRhs;
   // Verify
   assertUnit(response == false);
}  // Teardown
