/***********************************************************************
 * Source File:
 *    BOARD 
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "pieceBishop.h"
#include "pieceRook.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include "piecePawn.h"
#include <cassert>
using namespace std;

/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;
}

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
   return *board[pos.getCol()][pos.getRow()];
}

Piece& Board::operator [] (const Position& pos)
{
   return *board[pos.getCol()][pos.getRow()];
}

 /***********************************************
 * BOARD : DISPLAY
 *         Display the board
 ***********************************************/
void Board::display(const Position & posHover, const Position & posSelect) const
{
   ogstream gout;

   // draw the checkerboard
   gout.drawBoard();

   // draw any selections
   gout.drawHover(posHover);
   gout.drawSelected(posSelect);

   // draw possible moves
   set <Move> possible;
   int c = posSelect.getCol();
   int r = posSelect.getRow();

   if (c >= 0 && c < 8 && r >= 0 && r < 8) // valid col and row
   {
      Piece* pPiece = board[c][r];
      if (pPiece)
      {
         if ( (pPiece->isWhite() && numMoves % 2 == 0) || 
            ( !pPiece->isWhite() && numMoves % 2 == 1) )
            pPiece->getMoves(possible, *this); // getMoves changes possible
      }
   }

   set <Move> ::iterator it;
   for (it = possible.begin(); it != possible.end(); ++it)
      // iterate through and display possible moves
      gout.drawPossible((*it).getDest());

   // draw the pieces
   for (int col = 0; col < 8; ++col)
   {
      for (int row = 0; row < 8; ++row)
      {
         Piece* piece = board[col][row];
         if (piece != nullptr)
            piece->display(&gout);
      }
   }
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   // free everything
   for (int c = 0; c < 8; c++)
      for (int r = 0; r < 8; r++)
         board[c][r] = nullptr;

   numMoves = 0;
   pgout = nullptr;

   board[0][0] = new Rook(0, 0, true);
   board[1][0] = new Knight(1, 0, true);
   board[2][0] = new Bishop(2, 0, true);
   board[3][0] = new Queen(3, 0, true);
   board[4][0] = new King(4, 0, true);
   board[5][0] = new Bishop(5, 0, true);
   board[6][0] = new Knight(6, 0, true);
   board[7][0] = new Rook(7, 0, true);
   board[0][1] = new Pawn(0, 1, true);
   board[1][1] = new Pawn(1, 1, true);
   board[2][1] = new Pawn(2, 1, true);
   board[3][1] = new Pawn(3, 1, true);
   board[4][1] = new Pawn(4, 1, true);
   board[5][1] = new Pawn(5, 1, true);
   board[6][1] = new Pawn(6, 1, true);
   board[7][1] = new Pawn(7, 1, true);
   board[0][2] = new Space(0, 2);
   board[1][2] = new Space(1, 2);
   board[2][2] = new Space(2, 2);
   board[3][2] = new Space(3, 2);
   board[4][2] = new Space(4, 2);
   board[5][2] = new Space(5, 2);
   board[6][2] = new Space(6, 2);
   board[7][2] = new Space(7, 2);
   board[0][3] = new Space(0, 3);
   board[1][3] = new Space(1, 3);
   board[2][3] = new Space(2, 3);
   board[3][3] = new Space(3, 3);
   board[4][3] = new Space(4, 3);
   board[5][3] = new Space(5, 3);
   board[6][3] = new Space(6, 3);
   board[7][3] = new Space(7, 3);
   board[0][4] = new Space(0, 4);
   board[1][4] = new Space(1, 4);
   board[2][4] = new Space(2, 4);
   board[3][4] = new Space(3, 4);
   board[4][4] = new Space(4, 4);
   board[5][4] = new Space(5, 4);
   board[6][4] = new Space(6, 4);
   board[7][4] = new Space(7, 4);
   board[0][5] = new Space(0, 5);
   board[1][5] = new Space(1, 5);
   board[2][5] = new Space(2, 5);
   board[3][5] = new Space(3, 5);
   board[4][5] = new Space(4, 5);
   board[5][5] = new Space(5, 5);
   board[6][5] = new Space(6, 5);
   board[7][5] = new Space(7, 5);
   board[0][6] = new Pawn(0, 6, false);
   board[1][6] = new Pawn(1, 6, false);
   board[2][6] = new Pawn(2, 6, false);
   board[3][6] = new Pawn(3, 6, false);
   board[4][6] = new Pawn(4, 6, false);
   board[5][6] = new Pawn(5, 6, false);
   board[6][6] = new Pawn(6, 6, false);
   board[7][6] = new Pawn(7, 6, false);
   board[0][7] = new Rook(0, 7, false);
   board[1][7] = new Knight(1, 7, false);
   board[2][7] = new Bishop(2, 7, false);
   board[3][7] = new Queen(3, 7, false);
   board[4][7] = new King(4, 7, false);
   board[5][7] = new Bishop(5, 7, false);
   board[6][7] = new Knight(6, 7, false);
   board[7][7] = new Rook(7, 7, false);
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
   // free everything
   for (int c = 0; c < 8; c++)
      for (int r = 0; r < 8; r++)
         board[c][r] = nullptr;
}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{
   for (int c = 0; c < 8; c++)
   {
      for (int r = 0; r < 8; r++)
      {
         Position posPeice = board[c][r]->getPosition();
         assert(posPeice.getCol() == c);
         assert(posPeice.getRow() == r);
      }
   }
}


/**********************************************
 * BOARD : CAN MOVE
 *         Determine if a move is possible first
 *   INPUT Previous Select and Select
 *********************************************/
bool Board::canMove(const Position& posPrev, const Position& posSelect)
{
   int c = posPrev.getCol();
   int r = posPrev.getRow();
   
   if (!posPrev.isValid() || !posSelect.isValid()) // if invalid
      return false;
   
   // check if whites turn or not
   if (board[c][r]->isWhite() && numMoves % 2 == 1)
      return false;
   else if (!(board[c][r]->isWhite()) && numMoves % 2 == 0)
      return false;

   set <Move> possible;

   board[c][r]->getMoves(possible, *this); // getMoves changes possible

   for (std::set<Move>::iterator it = possible.begin(); it != possible.end(); ++it)
   {
      if (it->getDest() == posSelect)
      {
         Move newMove = const_cast<Move&>(*it);
         move(newMove);
         return true;
      }
   }
   return false;
}


/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move& move)
{
   int destCol = move.getDest().getCol();
   int destRow = move.getDest().getRow();
   int srcCol = move.getSource().getCol();
   int srcRow = move.getSource().getRow();
   
   if (move.getMoveType() == Move::MOVE)
   {
      // get rid of what was at the new dest address
      delete board[destCol][destRow];

      // board at destination has the same piece as the source
      board[destCol][destRow] = board[srcCol][srcRow];
      board[destCol][destRow]->movePeice(destCol, destRow, getCurrentMove());

      // new space object...
      Space* space = new Space(srcCol, srcRow);
      // board at source is a new space piece now
      board[srcCol][srcRow] = space;
   }

   else if (move.getMoveType() == Move::PROMOTION)
   {
      // is White
      bool isW = board[srcCol][srcRow]->isWhite();

      // new queen object...
      Queen* queen = new Queen(destCol, destRow, isW);
      // delete pawn
      delete board[srcCol][srcRow];

      // board at destination is new queen object
      board[destCol][destRow] = queen;

      // new space object...
      Space* space = new Space(srcCol, srcRow);
      // board at source is a new space piece now
      board[srcCol][srcRow] = space;
   }

   else if (move.getMoveType() == Move::ENPASSANT)
   {
      // get rid of what was at the new dest address
      delete board[destCol][destRow];

      // board at destination has the same piece as the source
      board[destCol][destRow] = board[srcCol][srcRow];
      board[destCol][destRow]->movePeice(destCol, destRow, getCurrentMove());


      // new space object...
      Space* space = new Space(srcCol, srcRow);
      // board at source is a new space piece now
      board[srcCol][srcRow] = space;

      // delete pawn and add space there
      if (board[destCol][destRow]->isWhite() == true) // if white
      {
         delete board[destCol][destRow - 1];
         Space* space = new Space(destCol, destRow - 1);
         board[destCol][destRow - 1] = space;
      }
      else
      {
         delete board[destCol][destRow + 1];
         Space* space = new Space(destCol, destRow + 1);
         board[destCol][destRow + 1] = space;
      }
   }

   else if (move.getMoveType() == Move::CASTLE_KING)
   {
      if (board[srcCol][srcRow]->isWhite() == true) // if white
      {
         // get rid of what was at the new dest addresses
         delete board[5][0];
         delete board[6][0];

         // move king and rook
         board[destCol][destRow] = board[srcCol][srcRow];
         board[5][0] = board[7][0];
         board[destCol][destRow]->movePeice(destCol, destRow, getCurrentMove());
         board[5][0]->movePeice(5, 0, getCurrentMove());


         // new space objects...
         Space* space = new Space(srcCol, srcRow);
         Space* space2 = new Space(7, 0);
         // board at source of king and rook are new space pieces now
         board[srcCol][srcRow] = space;
         board[7][0] = space2;
      }
      else
      {
         // get rid of what was at the new dest addresses
         delete board[5][7];
         delete board[6][7];

         // move king and rook
         board[destCol][destRow] = board[srcCol][srcRow];
         board[5][7] = board[7][7];
         board[destCol][destRow]->movePeice(destCol, destRow, getCurrentMove());
         board[5][7]->movePeice(5, 7, getCurrentMove());


         // new space objects...
         Space* space = new Space(srcCol, srcRow);
         Space* space2 = new Space(7, 7);
         // board at source of king and rook are new space pieces now
         board[srcCol][srcRow] = space;
         board[7][7] = space2;
      }
   }

   else if (move.getMoveType() == Move::CASTLE_QUEEN)
   {
      if (board[srcCol][srcRow]->isWhite() == true) // if white
      {
         // get rid of what was at the new dest addresses
         delete board[3][0];
         delete board[2][0];

         // move king and rook
         board[destCol][destRow] = board[srcCol][srcRow];
         board[3][0] = board[0][0]; // Move rook
         board[destCol][destRow]->movePeice(destCol, destRow, getCurrentMove());
         board[3][0]->movePeice(3, 0, getCurrentMove());


         // new space objects...
         Space* space = new Space(srcCol, srcRow);
         Space* space2 = new Space(0, 0);
         // board at source of king and rook are new space pieces now
         board[srcCol][srcRow] = space;
         board[0][0] = space2;
      }
      else // Black castle Queen
      {
         // get rid of what was at the new dest addresses
         delete board[3][7];
         delete board[2][7];

         // move king and rook
         board[destCol][destRow] = board[srcCol][srcRow];
         board[3][7] = board[0][7];
         board[destCol][destRow]->movePeice(destCol, destRow, getCurrentMove());
         board[3][7]->movePeice(3, 7, getCurrentMove());

         // new space objects...
         Space* space = new Space(srcCol, srcRow);
         Space* space2 = new Space(0, 7);
         // board at source of king and rook are new space pieces now
         board[srcCol][srcRow] = space;
         board[0][7] = space2;
      }
   }
   numMoves++;
   assertBoard();
}


/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;

   pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty() 
{
   delete pSpace;
}
