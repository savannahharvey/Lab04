/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The knight class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{
   bool black = !isWhite();
	pgout->drawKnight(getPosition(), black);
}


/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
   Position source;
   source = this->position;
   Position dest;
   PieceType capture;
   
   /*****************
    * Up Left
    ****************/
   Move upLeft;
   dest.setCol(this->position.getCol() - 1);
   dest.setRow(this->position.getRow() + 2);
   // check if dest location is valid.
   if (dest.isValid())
   {
      if ( (board[dest].isWhite() != this->isWhite() ) || (board[dest].getType() == SPACE) )
      {
         upLeft.setSource(source);
         upLeft.setDest(dest);
         
         // See if I capture
         if (board[dest].getType() != SPACE)
         {
            capture = board[dest].getType();
            upLeft.setCapture(capture);
         }
         // add the move to the set.
         moves.insert(upLeft);
      }
   }
   
   /*****************
    * Up Right
    ****************/
   Move upRight;
   
   dest.setCol(position.getCol() + 1);
   dest.setRow(position.getRow() + 2);
   // check if dest location is valid.
   if (dest.isValid())
   {
      if ( ( board[dest].getType() == SPACE ) || ( board[dest].isWhite() != this->isWhite() ) )
      {
         upRight.setSource(source);
         upRight.setDest(dest);
         
         // See if I capture
         if (board[dest].getType() != SPACE)
         {
            capture = board[dest].getType();
            upRight.setCapture(capture);
         }
         // add the move to the set.
         moves.insert(upRight);
      }
   }
   
   /*****************
    * Right Up
    ****************/
   Move rightUp;
   
   dest.setCol(position.getCol() + 2);
   dest.setRow(position.getRow() + 1);
   // check if dest location is valid.
   if(dest.isValid() &&
    ((board[dest].isWhite() != this->isWhite()) ||// see if it is an opposite color
     (board[dest].getType() == SPACE)) ) // Or it can be blank
   {
      rightUp.setSource(source);
      rightUp.setDest(dest);
      
      // See if I capture
      if (board[dest].getType() != SPACE)
      {
         capture = board[dest].getType();
         rightUp.setCapture(capture);
      }
      // add the move to the set.
      moves.insert(rightUp);
   }
   
   /*****************
    * Right Down
    ****************/
   Move rightDown;
   
   dest.setCol(position.getCol() + 2);
   dest.setRow(position.getRow() - 1);
   // check if dest location is valid.
   if(dest.isValid() &&
    ((board[dest].isWhite() != this->isWhite()) ||// see if it is an opposite color
     (board[dest].getType() == SPACE)) ) // Or it can be blank
   {
      rightDown.setSource(source);
      rightDown.setDest(dest);
      
      // See if I capture
      if (board[dest].getType() != SPACE)
      {
         capture = board[dest].getType();
         rightDown.setCapture(capture);
      }
      // add the move to the set.
      moves.insert(rightDown);
   }
   
   /*****************
    * Down Right
    ****************/
   Move downRight;
   
   dest.setCol(position.getCol() + 1);
   dest.setRow(position.getRow() - 2);
   // check if dest location is valid.
   if(dest.isValid() &&
    ((board[dest].isWhite() != this->isWhite()) ||// see if it is an opposite color
     (board[dest].getType() == SPACE)) ) // Or it can be blank
   {
      downRight.setSource(source);
      downRight.setDest(dest);
      
      // See if I capture
      if (board[dest].getType() != SPACE)
      {
         capture = board[dest].getType();
         downRight.setCapture(capture);
      }
      // add the move to the set.
      moves.insert(downRight);
   }
   
   /*****************
    * Down Left
    ****************/
   Move downLeft;
   
   dest.setCol(position.getCol() - 1);
   dest.setRow(position.getRow() - 2);
   // check if dest location is valid.
   if(dest.isValid() &&
    ((board[dest].isWhite() != this->isWhite()) ||// see if it is an opposite color
     (board[dest].getType() == SPACE)) ) // Or it can be blank
   {
      downLeft.setSource(source);
      downLeft.setDest(dest);
      
      // See if I capture
      if (board[dest].getType() != SPACE)
      {
         capture = board[dest].getType();
         downLeft.setCapture(capture);
      }
      // add the move to the set.
      moves.insert(downLeft);
   }
   // left down
   /*****************
    * Left Down
    ****************/
   Move leftDown;
   
   dest.setCol(position.getCol() - 2);
   dest.setRow(position.getRow() - 1);
   // check if dest location is valid.
   if(dest.isValid() &&
    ((board[dest].isWhite() != this->isWhite()) ||// see if it is an opposite color
     (board[dest].getType() == SPACE)) ) // Or it can be blank
   {
      leftDown.setSource(source);
      leftDown.setDest(dest);
      
      // See if I capture
      if (board[dest].getType() != SPACE)
      {
         capture = board[dest].getType();
         leftDown.setCapture(capture);
      }
      // add the move to the set.
      moves.insert(leftDown);
   }

   /*****************
    * Left Up
    ****************/
   Move leftUp;
   
   dest.setCol(position.getCol() - 2);
   dest.setRow(position.getRow() + 1);
   // check if dest location is valid.
   if(dest.isValid() &&
    ((board[dest].isWhite() != this->isWhite()) ||// see if it is an opposite color
     (board[dest].getType() == SPACE)) ) // Or it can be blank
   {
      leftUp.setSource(source);
      leftUp.setDest(dest);
      
      // See if I capture
      if (board[dest].getType() != SPACE)
      {
         capture = board[dest].getType();
         leftUp.setCapture(capture);
      }
      // add the move to the set.
      moves.insert(leftUp);
   }
}
