/* 
 * File:   main.cpp
 * Author: Sam Kraus
 * Chess  
 * Created on August 29, 2019, 7:39 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <stdlib.h>

using namespace std;

// --Function Declarations--
int fnInitialize();
int fnMenu();
int fnCreateBoard();
int fnMovePiece();
int fnCheckValidMove();
int fnExecuteMove();
int fnPrintNewBoard();
int fnGameOver();

//variables
//strings
string moveFrom = "";
string moveTo = "";
string valid = "";
//pieces
string whitePawn = "wP";
string whiteRook = "wR";
string whiteKnight = "wN";
string whiteBishop = "wB";
string whiteKing = "wK";
string whiteQueen = "wQ";
string noPiece = "  ";
string blackPawn = "bP";
string blackRook = "bR";
string blackKnight = "bN";
string blackBishop = "bB";
string blackKing = "bK";
string blackQueen = "bQ";
string border = "##";

//ints
int menuSwitch = 0;
//bools
bool checkMate = false;
int currentPlayer = 1;
//arrays

//board dec
const int rows = 8;
const int columns = 8;

/*
 * This is used to assign initial values to each square on the chess board. 
 * The values of this array never change.  It is only used during the create board phase.
 * This is the top level array in creating the layout of the board.  9's are the 
 * borders of the game board while anything else represents either a piece of empty space.
 */
const int startingBoardPieceAssignments[17][17]{
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9,-4,9,-3,9,-2,9,-5,9,-6,9,-2,9,-3,9,-4,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9,-1,9,-1,9,-1,9,-1,9,-1,9,-1,9,-1,9,-1,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9, 0,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9, 1,9, 1,9, 1,9, 1,9, 1,9, 1,9, 1,9, 1,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9},
{9, 4,9, 3,9, 2,9, 5,9, 6,9, 2,9, 3,9, 4,9},
{9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9, 9,9}};
//end starting board dec

//live board dec
/*
 * This (below) stores coordinates of the board during for the whole game.  
 * It is used to compare entries.  If a user does not utilize variables stored in this Array,
 * the entry will be invalidated.  
 * If the move is invalid, the board does not change. This board is a constant.
 */
string liveBoardCoordinates[17][17]{
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a8","##","b8","##","c8","##","d8","##","e8","##","f8","##","g8","##","h8","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a7","##","b7","##","c7","##","d7","##","e7","##","f7","##","g7","##","h7","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a6","##","b6","##","c6","##","d6","##","e6","##","f6","##","g6","##","h6","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a5","##","b5","##","c5","##","d5","##","e5","##","f5","##","g5","##","h5","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a4","##","b4","##","c4","##","d4","##","e4","##","f4","##","g4","##","h4","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a3","##","b3","##","c3","##","d3","##","e3","##","f3","##","g3","##","h3","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a2","##","b2","##","c2","##","d2","##","e2","##","f2","##","g2","##","h2","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a1","##","b1","##","c1","##","d1","##","e1","##","f1","##","g1","##","h1","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}};//coordinates of each space (tracks against the search counter)

//Temporary (invisible) board dec.  Stores user actions before validation phase.
/*This (below) stores temporary board during the validate move phase.  
* Proposed moves go here.  If the move is valid, this becomes the new board.  
* If the move is invalid, the board does not change. 
* This only becomes the new board if the execute move is enabled.*/
string liveBoardTemp[17][17]{
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a8","##","b8","##","c8","##","d8","##","e8","##","f8","##","g8","##","h8","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a7","##","b7","##","c7","##","d7","##","e7","##","f7","##","g7","##","h7","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a6","##","b6","##","c6","##","d6","##","e6","##","f6","##","g6","##","h6","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a5","##","b5","##","c5","##","d5","##","e5","##","f5","##","g5","##","h5","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a4","##","b4","##","c4","##","d4","##","e4","##","f4","##","g4","##","h4","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a3","##","b3","##","c3","##","d3","##","e3","##","f3","##","g3","##","h3","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a2","##","b2","##","c2","##","d2","##","e2","##","f2","##","g2","##","h2","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a1","##","b1","##","c1","##","d1","##","e1","##","f1","##","g1","##","h1","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}};

//This board is the viewport for players.  This updates after a successful validation phase.
string liveBoardViewable[17][17]{
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a8","##","b8","##","c8","##","d8","##","e8","##","f8","##","g8","##","h8","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a7","##","b7","##","c7","##","d7","##","e7","##","f7","##","g7","##","h7","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a6","##","b6","##","c6","##","d6","##","e6","##","f6","##","g6","##","h6","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a5","##","b5","##","c5","##","d5","##","e5","##","f5","##","g5","##","h5","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a4","##","b4","##","c4","##","d4","##","e4","##","f4","##","g4","##","h4","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a3","##","b3","##","c3","##","d3","##","e3","##","f3","##","g3","##","h3","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a2","##","b2","##","c2","##","d2","##","e2","##","f2","##","g2","##","h2","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"},
{"##","a1","##","b1","##","c1","##","d1","##","e1","##","f1","##","g1","##","h1","##"},
{"##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##","##"}};//viewPort to display current game.  

int pieces[14];//includes border and empty

//function Definitions
int fnInitialize()
{
    cout << "Initializing Game....\n";
    //one time at startup code launches here.
    
    fnMenu();//begin game flow cycle
    
    return 0;
}

int fnMenu()
{
    cout << "Main Menu" << endl;
    cout << "Start Game (1)" << endl;
    cout << "Quit (2)" << endl;
    cin >> menuSwitch;
    switch(menuSwitch)
    {
        case 1: cout << "Starting New Game\n";
                 fnCreateBoard();
        default: cout << "Quitting\n";
    }
    return 0;
}

int fnCreateBoard()
{
    cout << "fnCreatingBoard\n";
    int spaceX = 0;
    int spaceY = 0;
    for (spaceX = 0; spaceX < 17; spaceX++){
        cout << endl;        
        for (spaceY = 0; spaceY < 17; spaceY++){
            if (startingBoardPieceAssignments[spaceX][spaceY] == -4){
                liveBoardViewable[spaceX][spaceY]=blackRook;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY] == -3){
                liveBoardViewable[spaceX][spaceY]=blackKnight;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== -2){
                liveBoardViewable[spaceX][spaceY]=blackBishop;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== -5){
                liveBoardViewable[spaceX][spaceY]=blackQueen;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== -6){
                liveBoardViewable[spaceX][spaceY]=blackKing;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== -1){
                liveBoardViewable[spaceX][spaceY]=blackPawn;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 0){
                liveBoardViewable[spaceX][spaceY]=noPiece;
            }   
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 4){
                liveBoardViewable[spaceX][spaceY]=whiteRook;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 3){
                liveBoardViewable[spaceX][spaceY]=whiteKnight;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 2){
                liveBoardViewable[spaceX][spaceY]=whiteBishop;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 5){
                liveBoardViewable[spaceX][spaceY]=whiteQueen;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 6){
                liveBoardViewable[spaceX][spaceY]=whiteKing;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 1){
                liveBoardViewable[spaceX][spaceY]=whitePawn;
            }
            else if (startingBoardPieceAssignments[spaceX][spaceY]== 9){
                liveBoardViewable[spaceX][spaceY]=border;
            }
    cout << liveBoardViewable[spaceX][spaceY];//prints piece to space in array
        }
    }
    cout << endl;       
    fnMovePiece();
    return 0;
}

int fnMovePiece()
{
    cout << "fnMovePiece\n";
    cout << "Turn: Player " << currentPlayer << "'s\n";
    cout << "Move from: ";
    cin >> moveFrom;
    cout << endl << "To: ";
    cin >> moveTo;
    fnCheckValidMove();
    return 0;
}

int fnCheckValidMove()
{
    cout << "fnCheckValidMove\n";
    cout << "Player " << currentPlayer << " moves " << moveFrom << " to " << moveTo << "...\n";
    if (currentPlayer == 1)
    {
        cout << "Player 2, is this move valid?\n";
        cin >> valid;
    }
    else if (currentPlayer == 2)
    {
        cout << "Player 1, is this move valid?\n";
        cin >> valid;
    }
    if (valid == "yes" || valid =="Yes" || valid == "Yes." || valid == "yes.")
    {
        cout << "Move is valid\n";
        fnExecuteMove();
    }
    else
    {
        valid = "";// clears valid entry.
        moveFrom="";//clears move from
        moveTo="";//clears move to
        cout << "Opposing player says your move is invalid.\n";
        fnMovePiece();//reboots the action to move phase.  
    }
    return 0;
}

int fnGameOver()
{
    cout << "Player " << currentPlayer << " wins!\n"; //checkmate
    fnMenu();
    return 0;//ends the game.
}

int fnExecuteMove()
{
    int moveX;
    int moveY;
    cout << "fnExecuteMove\n";
    for (moveX = 0; moveX < 17; moveX++){
        for (moveY = 0; moveY < 17; moveY++){
            int checkSpaceX = 0;
            int checkSpaceY = 0;
            if (moveFrom == liveBoardCoordinates[moveX][moveY]){
                for (checkSpaceX = 0; checkSpaceX < 17; checkSpaceX++){
                    for (checkSpaceY = 0; checkSpaceY < 17; checkSpaceY++){
                        if (moveTo == liveBoardCoordinates[checkSpaceX][checkSpaceY]){
                        liveBoardViewable[checkSpaceX][checkSpaceY] = liveBoardViewable[moveX][moveY];
                        liveBoardViewable[moveX][moveY] =  noPiece;
                        }
                    }
                }
            }
        }
    }

    if (currentPlayer == 1)
    {
        cout << "Player " << currentPlayer << " moves.\n";
        currentPlayer = 2;
        fnPrintNewBoard();
    }
    else if (currentPlayer == 2)
    {
        cout << "Player " << currentPlayer << " moves\n";
        currentPlayer = 1;
        fnPrintNewBoard();
    }
    if (checkMate == true)
    {
        fnGameOver();
    }
    fnPrintNewBoard();
    return 0;
}

int fnPrintNewBoard(){
    cout << "Printing updated board.";
    int printX = 0;
    int printY = 0;
    cout << endl;
    for (printX = 0; printX < 17; printX++){
        cout << endl;
        for(printY =0; printY < 17; printY++)
        {
            cout << liveBoardViewable[printX][printY];
        }
    }
    fnMovePiece();
}

int main(int argc, char** argv){
    
    cout << "Starting Game\n";
    fnInitialize();
    return 0;
  
}
