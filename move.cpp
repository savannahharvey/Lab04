/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;


/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move()
{
   // start with something
   this->source = Position();
   this->dest = Position();
   this->capture = INVALID;
}

/***************************************************
 * MOVE : PARSE
 ***************************************************/
void Move::parse(char* t)
{
   // Convert char* to string and start the iterator.
   string text(t);
   string::const_iterator it = text.cbegin();

   // get the source
   int col = *it - 'a';
   it++;
   int row = *it - '1';
   it++;
   this->source.setCol(col);
   this->source.setRow(row);

   // get the destination
   col = *it - 'a';
   it++;
   row = *it - '1';
   it++;
   this->dest.setCol(col);
   this->dest.setRow(row);

   // If there is not more text, then the moveType is Move.
   if (it != text.end())
   {
      // capture and promotion information
      switch (*it)
      {
         // Captures
      case 'p':   // capture a pawn
      case 'n':   // capture a knight
      case 'b':   // capture a bishop
      case 'r':   // capture a rook
      case 'q':   // capture a queen
      case 'k':   // !! you can't capture a king you silly!
         this->capture = this->pieceTypeFromLetter(*it);
         this->moveType = MOVE;
         break;

         // Move Types
      case 'c':  // short castling or king's castle
         this->moveType = CASTLE_KING;
         break;
      case 'C':  // long castling or queen's castle
         this->moveType = CASTLE_QUEEN;
         break;
      case 'E':  // En-passant
         this->moveType = ENPASSANT;
         break;

         // Promotions
      case 'N':  // Promote to knight
      case 'B':  // Promote to Bishop
      case 'R':  // Promote to Rook
      case 'Q':  // Promote to Queen
         this->promote = this->pieceTypeFromLetter(*it);
         this->moveType = MOVE;
         break;

         // This shouldnt happen.
      default:
         this->moveType = MOVE_ERROR;
         break;
      }
   }
   // If there is no text after the locations.
   else
   {
      this->moveType = MOVE;
   }
}

/***************************************************
 * MOVE : LETTER FROM PIECE TYPE
 * Convert the Piece Type into a letter.
 ***************************************************/
char Move::letterFromPieceType(PieceType pt) const
{
   char letter;

   switch (pt)
   {
   case SPACE:
      letter = ' ';
      break;
   case PAWN:
      letter = 'p';
      break;
   case KNIGHT:
      letter = 'n';
      break;
   case BISHOP:
      letter = 'b';
      break;
   case ROOK:
      letter = 'r';
      break;
   case QUEEN:
      letter = 'q';
      break;
   case KING:
      letter = 'k';
      break;
   default:
      letter = '!';
      break;
   }
   return letter;
}

/***************************************************
 * MOVE : PIECE TYPE FROM LETTER
 * convert a letter int a PieceType enum.
 ***************************************************/
PieceType Move::pieceTypeFromLetter(char letter) const
{
   PieceType piece;
   switch (letter)
   {
   case ' ':
      piece = SPACE;
      break;
   case 'p':
      piece = PAWN;
      break;
   case 'b':
      piece = BISHOP;
      break;
   case 'n':
      piece = KNIGHT;
      break;
   case 'r':
      piece = ROOK;
      break;
   case 'q':
      piece = QUEEN;
      break;
   case 'k':
      piece = KING;
      break;
   default:
      piece = INVALID;
      break;
   }
   return piece;
}

/***************************************************
 * MOVE : GET TEXT
 * Turn the object back into Universal Chess Interface notation.
 ***************************************************/
string Move::getText()
{
   char* text = new char[6];
   text[0] = '\0';
   // get the first 4 characters for locations.
   char* sourceText = this->lettersFromPosition(source);
   char* destText = this->lettersFromPosition(dest);

   // add sourceText to the text, then destText.
   strcat(text, sourceText); // text[0] text[1]
   strcat(text, destText); // text[2] text[3]

   // Assign the last caracter if applicable
   if (moveType == MOVE && capture == INVALID) // No extra characters
   {
      text[4] = '\0'; // null terminate
   }
   else if (moveType == ENPASSANT) // En-passant
   {
      text[4] = 'E';
      text[5] = '\0'; // null terminate
   }
   else if (moveType == CASTLE_KING) // Castle
   {
      text[4] = 'c';
      text[5] = '\0'; // null terminate
   }
   else if (moveType == CASTLE_QUEEN) // Castle
   {
      text[4] = 'C';
      text[5] = '\0'; // null terminate
   }
   else // If we get here, that means its a regular move but a capture has happened
   {
      text[4] = letterFromPieceType(capture); // assign the capture
      text[5] = '\0'; // null terminate
   }
   // Convert to string
   string t = text;
   return t;
}

/***************************************************
 * MOVE : LETTERS FROM POSITION
 * convert a chess position object into the Universal Chess
 * Interface notation representation.
 ***************************************************/
char* Move::lettersFromPosition(Position& pos)
{
   // This will be 2 characters long.
   char* text = new char[3];

   // Turn the column into a letter
   switch (pos.getCol()) {
   case 0:
      text[0] = 'a';
      break;
   case 1:
      text[0] = 'b';
      break;
   case 2:
      text[0] = 'c';
      break;
   case 3:
      text[0] = 'd';
      break;
   case 4:
      text[0] = 'e';
      break;
   case 5:
      text[0] = 'f';
      break;
   case 6:
      text[0] = 'g';
      break;
   case 7:
      text[0] = 'h';
      break;
   default:
      text[0] = '!';
      break;
   }
   // the row will be a number
   text[1] = static_cast<char>(pos.getRow() + '1'); // Check this!!!
   text[2] = '\0'; // Null-terminate the string
   return text;
}
