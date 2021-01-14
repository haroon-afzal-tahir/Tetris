#pragma once
#include <iostream>
using namespace std;

//Class of entire game
class Tetris
{
public:
	void Download();		//loading the game
	void Instructions();	//prints instructions for the game
	void PlayGame();		//allows user to either play the game or exit the system
	void ExitScreen();		//allows user to either play the game again or exit the system
	void gamePlay();		//Entire game play of Tetris
	void gameOver();		//Game over printed with graphics
};

//Board class
class Board
{
protected:
	int width;
	int height;
	bool** board;
	int** colour;
	int score;
public:
	Board();					//default constructor
	Board(int, int);			//overloaded constructor
	~Board();					//destructor
	int** get_colour();			//gets the colour
	void set_colour(int**);		//sets the colour
	bool** get_board();			//get the board every time
	void set_board(bool**);		//set the board
	void print_board();			//prints the tetris board
	void check_board(int&);		//checks the board
	void fill_board();			//fills the board with pieces
	int get_score();			//gets the score
	void set_score(int);		//sets the score
	void print_score();			//prints the score
	void fill_empty();			//fills the part of the board which has empty spaces
};

//Piece class
class Piece : public Board {
protected:
	int x;
	int y;
	int rotation;
public:
	Piece();									//default constructor
	int get_x();								//gets x coordinate
	int get_y();								//gets y coordinate
	int get_rotation();							//gets rotation number of piece
	void set_x(int);							//sets x coordinate
	void set_y(int);							//sets y coordinate
	void set_rotation(int);						//sets rotation number of piece
	bool virtual print() = 0;					//pure virtual function of printing the pieces
	void virtual next_piece_call() = 0;			//pure virtual function of printing the next piece on screen
	void virtual next_piece_remove() = 0;		//pure virtual function of removing the previous piece
	void virtual rotations_call() = 0;			//pure virtual function of printing rotations of pieces
	void virtual rotations_call_remove() = 0;	//pure virtual function of removing the rotations of pieces
};

//Piece L inherited from Piece class
class Piece_L : public Piece {
public:
	bool print() override;					//function of printing the piece
	void next_piece_call() override;		//function of printing the piece on screen
	void next_piece_remove() override;		//function of removing the piece
	void rotations_call() override;			//function of printing rotations of piece
	void rotations_call_remove() override;	//function of removing the rotations of piece
};

//Piece S inherited from Piece class
class Piece_S : public Piece {
public:
	bool print() override;					//function of printing the piece
	void next_piece_call() override;		//function of printing the piece on screen
	void next_piece_remove() override;		//function of removing the piece
	void rotations_call() override;			//function of printing rotations of piece
	void rotations_call_remove() override;	//function of removing the rotations of piece
};

//Piece Z inherited from Piece class
class Piece_Z : public Piece {
public:
	bool print() override;					//function of printing the piece
	void next_piece_call() override;		//function of printing the piece on screen
	void next_piece_remove() override;		//function of removing the piece
	void rotations_call() override;			//function of printing rotations of piece
	void rotations_call_remove() override;	//function of removing the rotations of piece
};

//Piece O inherited from Piece class
class Piece_O : public Piece {
public:
	bool print() override;					//function of printing the piece
	void next_piece_call() override;		//function of printing the piece on screen
	void next_piece_remove() override;		//function of removing the piece
	void rotations_call() override;			//function of printing rotations of piece
	void rotations_call_remove() override;	//function of removing the rotations of piece
};

//Piece I inherited from Piece class
class Piece_I : public Piece {
public:
	bool print() override;					//function of printing the piece
	void next_piece_call() override;		//function of printing the piece on screen
	void next_piece_remove() override;		//function of removing the piece
	void rotations_call() override;			//function of printing rotations of piece
	void rotations_call_remove() override;	//function of removing the rotations of piece
};

//Piece J inherited from Piece class
class Piece_J : public Piece {
public:
	bool print() override;					//function of printing the piece
	void next_piece_call() override;		//function of printing the piece on screen
	void next_piece_remove() override;		//function of removing the piece
	void rotations_call() override;			//function of printing rotations of piece
	void rotations_call_remove() override;	//function of removing the rotations of piece
};

//Piece T inherited from Piece class
class Piece_T : public Piece {
public:
	bool print() override;					//function of printing the piece
	void next_piece_call() override;		//function of printing the piece on screen
	void next_piece_remove() override;		//function of removing the piece
	void rotations_call() override;			//function of printing rotations of piece
	void rotations_call_remove() override;	//function of removing the rotations of piece
};