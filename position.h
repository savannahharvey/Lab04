/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default
const int OFFSET_BOARD = 50;   // boarder between the board and the edge of screen

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
   int dCol;
   int dRow;
};

const Delta ADD_R = {  0,  1 };
const Delta ADD_C = {  1,  0 };
const Delta SUB_R = {  0, -1 };
const Delta SUB_C = { -1,  0 };


class PositionTest;
class TestKnight;
class TestKing;
class TestBoard;
class TestMove;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
   friend class PositionTest;
   friend class TestBishop;
   friend class TestRook;
   friend class TestQueen;
   friend class TestKing;
   friend class TestKnight;
   friend class TestPawn;
   friend class TestBoard;
   friend class TestMove;

public:

   // Position :    The Position class can work with other positions,
   //               Allowing for comparisions, copying, etc.
   Position(const Position& rhs) : colRow(rhs.colRow)  {}
   Position() : colRow(0x99) {}
   
   bool isInvalid() const { return (getRow() == -1 || getCol() == -1) ? true : false; }
   bool isValid()   const { return (getRow() == -1 || getCol() == -1) ? false : true; }
   void setValid() {}
   void setInvalid() {}
   bool operator <  (const Position& rhs) const
   {
      if (rhs.colRow > this->colRow)
      {
         return true;
      }
      return false;
   }
   bool operator == (const Position& rhs) const
   {
      if (rhs.colRow == this->colRow)
      {
         return true;
      }
      return false;
   }
   bool operator != (const Position& rhs) const { return true; }
   const Position& operator =  (const Position& rhs)
   {
      this->colRow = rhs.colRow;
      return *this;
   }

   // Location : The Position class can work with locations, which
   //            are 0...63 where we start in row 0, then row 1, etc.
   Position(int location) : colRow(0x99) {}
   int getLocation() const { return getRow() * 8 + getCol(); }
   void setLocation(int location) {}


   // Row/Col : The position class can work with row/column,
   //           which are 0..7 and 0...7
   Position(int c, int r) : colRow(c * 16 + r) {}
   virtual int getCol() const
   {
      int col = (int)((colRow & 0xf0) >> 4);
      int row = (int)((colRow & 0x0f) >> 0);
      return (col < 8 && row < 8) ? col : -1;
   }
   virtual int getRow() const
   {
      int row = (int)((colRow & 0x0f) >> 0);
      int col = (int)((colRow & 0xf0) >> 4);
      return (row < 8 && col < 8) ? row : -1;
   }
   void setRow(int r)
   {
      // | concatenates 0x[a]0 with 0x0[b] to get 0x[a][b]
      if (r >= 0 && r < 8)
         colRow = (colRow & 0xf0) | (r & 0x0f);
      else
         colRow = 0xff;
   }
   void setCol(int c)
   {
      // | concatenates 0x0[a] with 0x0[b] << 4 to get 0x[b][a]
      if (c >= 0 && c < 8)
         colRow = (colRow & 0x0f) | ((c & 0x0f) << 4);
      else
         colRow = 0xff;
   }
   void set(int c, int r)
   {
      colRow = c * 16 + r;
   }

   // Text:    The Position class can work with textual coordinates,
   //          such as "d4"

   Position(const char* s) : colRow(0x99)
   {
      *this = s;
   }
   const Position& operator =  (const char* rhs)
   {
      string rhsString = rhs;
      string::const_iterator it = rhsString.cbegin();
      int col = *it - 'a';
      it++;
      int row = *it - '1';
      it++;
      colRow = col * 16 + row;
      return *this;
   }
   const Position& operator =  (const string& rhs)
   {
      string::const_iterator it = rhs.cbegin();
      int col = *it - 'a';
      it++;
      int row = *it - '1';
      it++;
      colRow = col * 16 + row;
      return *this;
   }


   // Pixels:    The Position class can work with screen coordinates,
   //            a.k.a. Pixels, these are X and Y coordinates. Note that
   //            we need to scale them according to the size of the board.
   int getX()   const
   {
      return (int)((double)getCol() * getSquareWidth() + getSquareWidth());
   }
   int getY()   const
   {
      return (int)((double)getRow() * getSquareHeight() + getSquareHeight());
   }
   void setXY(double x, double y)
   {
      if (((int)(x / getSquareWidth()) - 1) > 7 || ((int)(x / getSquareWidth()) - 1) < 0)
         colRow = 0xff;
      if (8 - (int)(y / getSquareHeight()) > 7 || (8 - (int)(y / getSquareHeight())) < 0)
         colRow = 0xff;
      if (getCol() == -1 || getRow() == -1)
         colRow = 0xff;
      else
         set((int)(x / getSquareWidth()) - 1,
            8 - (int)(y / getSquareHeight()));
   }
   double getSquareWidth()  const { return squareWidth; }
   double getSquareHeight() const { return squareHeight; }
   void setBoardWidthHeight(int widthBoard, int heightBoard)
   {
      if (widthBoard < 0 || heightBoard < 0)
         return;
      squareWidth = (double)widthBoard / 10.0; // 8 squares + 2 spaces
      squareHeight = (double)heightBoard / 10.0;
   }

   // Delta:    The Position class can work with deltas, which are
   //           offsets from a given location. This helps pieces move
   //           on the chess board.
   Position(const Position& rhs, const Delta& delta) : colRow(rhs.colRow)
   {
      this->setCol(rhs.getCol() + delta.dCol);
      this->setRow(rhs.getRow() + delta.dRow);
   }
   void adjustRow(int dRow) { setRow(dRow); }
   void adjustCol(int dCol) { setCol(dCol); }
   const Position& operator += (const Delta& rhs)
   {
      int row = rhs.dRow;
      int col = rhs.dCol;

      if ((getCol() + col) > 7 || (getCol() + col) < 0)
         colRow = 0xff;
      if ((getRow() + row) > 7 || (getRow() + row) < 0)
         colRow = 0xff;
      if (getCol() == -1 || getRow() == -1)
         colRow = 0xff;
      else
         set(getCol() + col, getRow() + row);

      return *this;
   }
   Position operator + (const Delta& rhs) const { return *this; }

private:
   void set(uint8_t colRowNew) {}

   uint8_t colRow;
   static double squareWidth;
   static double squareHeight;
};


ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);
