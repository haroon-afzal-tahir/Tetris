#include "Tetris.h"
#include "mygraphics.h"
#include <conio.h>
using namespace std;

// Board Functions
Board::Board() {	//default constructor
	gotoxy(40, 1);
	cout << "Next Piece";		//the upcoming piece will be printed underneath

	gotoxy(40, 8);
	cout << "Rotation of Current Piece";		//all rotations will be printed of the current piece underneath

	gotoxy(40, 20);
	cout << "Score: ";		//score will be counted and printed

	width = 12;
	height = 20;
	score = 0;
	board = new bool* [(height - 1)];				//memory allocated
	for (int i = 0; i < (height - 1); i++) {
		board[i] = new bool[(width - 1)];
		for (int j = 0; j < (width - 1); j++) {
			board[i][j] = false;
		}
	}
	colour = new int* [(height - 1)];				//memory allocated
	for (int i = 0; i < (height - 1); i++) {
		colour[i] = new int[(width - 1)];
		for (int j = 0; j < (width - 1); j++) {
			colour[i][j] = 0;
		}
	}
}
Board::~Board()
{								//destructor
	if (board != nullptr) {
		for (int i = 0; i < (height - 1); i++) {
			delete[] board[i];
		}
		delete[] board;
	}
	if (colour != nullptr) {
		for (int i = 0; i < (height - 1); i++) {
			delete[] colour[i];
		}
		delete[] colour;
	}
	width = 0;
	height = 0;
	score = 0;
	board = nullptr;			//empty board
	colour = nullptr;			//empty colour
}
Board::Board(int x, int y) {		//overloaded constructor
	this->width = x;
	this->height = y;
	this->board = new bool* [(height - 1)];
	for (int i = 0; i < (height - 1); i++) {
		this->board[i] = new bool[(width - 1)];
		for (int j = 0; j < (width - 1); j++) {
			this->board[i][j] = false;
		}
	}

	this->colour = new int* [(height - 1)];
	for (int i = 0; i < (height - 1); i++) {
		this->colour[i] = new int[(width - 1)];
		for (int j = 0; j < (width - 1); j++) {
			this->colour[i][j] = 0;
		}
	}
	this->score = 0;
}
bool** Board::get_board() {			//gets the board
	return board;
}
void Board::print_board() {			//prints the boundary of board
	showConsoleCursor(false);
	int a = 50, b = 70, c = 50, d = 70; // a = x1, c = y1, b = x2, d = y2
	for (int i = 0; i < width; i++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		a += 20;
		b += 20;
	}

	for (int j = 0; j < height; j++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		c += 20;
		d += 20;
	}

	for (int k = 0; k < width; k++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		a -= 20;
		b -= 20;
	}

	for (int i = 0; i < height; i++) {
		drawRectangle(a, c, b, d, 211, 211, 211, 128, 128, 128);
		c -= 20;
		d -= 20;
	}
}
void Board::set_board(bool** board) {		//sets the board
	this->board = new bool* [19];
	for (int i = 0; i < 19; i++) {
		this->board[i] = new bool[11];
	}
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 11; j++) {
			this->board[i][j] = board[i][j];
		}
	}
}
void Board::check_board(int& score) {			//checks the board
	bool check = true;
	int i = 18, j = 0;
	for (i = 18; i >= 0; i--) {
		check = true;
		for (j = 0; j < 11; j++) {
			if (board[i][j] == false) {
				check = false;
				break;
			}
		}
		if (check) {
			int x = 0;
			int a1 = 70, b1 = 90;
			int y = i * 20;
			score += 15;				//if the row is emptied, the score is added
			set_score(score);
			for (x = 0; x < 220; x += 20) {
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
				board[i][(x / 20)] = false;
			}
			x = 0;
			for (int k = i; k >= 0; k--) {
				x = 0;
				if (k != 0) {
					for (int l = 0; l < 11; l++) {
						if (colour[k - 1][l] == 0) {
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							board[k][l] = false;
							colour[k][l] = 0;
						}
						else if (colour[k - 1][l] == 1) {
							// Piece L
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							board[k][l] = true;
							colour[k][l] = 1;
						}
						else if (colour[k - 1][l] == 2) {
							// Piece S
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
							board[k][l] = true;
							colour[k][l] = 2;
						}
						else if (colour[k - 1][l] == 3) {
							// Piece Z
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							board[k][l] = true;
							colour[k][l] = 3;
						}
						else if (colour[k - 1][l] == 4) {
							// Piece O
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
							board[k][l] = true;
							colour[k][l] = 4;
						}
						else if (colour[k - 1][l] == 5) {
							// Piece I
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
							board[k][l] = true;
							colour[k][l] = 5;
						}
						else if (colour[k - 1][l] == 6) {
							// Piece J
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							board[k][l] = true;
							colour[k][l] = 6;
						}
						else if (colour[k - 1][l] == 7) {
							// Piece T
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							board[k][l] = true;
							colour[k][l] = 7;
						}
						x += 20;
					}
					y -= 20;
				}
				else {
					for (x = 0; x < 220; x += 20) {
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						board[k][(x / 20)] = false;
						colour[k][(x / 20)] = 0;
					}
					x = 0;
				}
			}
			i++;
		}
	}
}
int** Board::get_colour() {		//sets the colour
	return colour;
}
void Board::set_colour(int** colour) {			//sets the colour
	this->colour = new int* [19];
	for (int i = 0; i < 19; i++) {
		this->colour[i] = new int[11];
	}
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 11; j++) {
			this->colour[i][j] = colour[i][j];
		}
	}
}
void Board::set_score(int score) {		//sets score
	this->score = score;
}
int Board::get_score() {		//gets score
	return score;
}
void Board::print_score() {			//prints score of the game
	cout << score;

	//removing the previous score and printing updated score
	if ((score / 10) == 0) {
		cout << "\b";
	}
	if ((score / 10) >= 1 && (score / 10) <= 9) {
		cout << "\b\b";
	}
	if ((score / 10) >= 10 && (score / 10) <= 99) {
		cout << "\b\b\b";
	}
	if ((score / 10) >= 100 && (score / 10) <= 999) {
		cout << "\b\b\b\b";
	}
	if ((score / 10) >= 1000 && (score / 10) <= 9999) {
		cout << "\b\b\b\b\b";
	}
	if ((score / 10) >= 10000 && (score / 10) <= 99999) {
		cout << "\b\b\b\b\b\b";
	}
}
void Board::fill_board() {			//fills the board
	int a1 = 70, b1 = 90;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 11; j++) {
			if (colour[i][j] == 0) {
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 0, 0, 0, 0, 0, 0);
			}
			else if (colour[i][j] == 1) {
				// Piece L
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 255, 156, 0, 128, 0, 128);
			}
			else if (colour[i][j] == 2) {
				// Piece S
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 235, 122, 179, 225, 56, 141);
			}
			else if (colour[i][j] == 3) {
				// Piece Z
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 255, 2, 129, 139, 0, 0);
			}
			else if (colour[i][j] == 4) {
				// Piece O
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 0, 232, 232, 0, 181, 181);
			}
			else if (colour[i][j] == 5) {
				// Piece I
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 255, 129, 2, 181, 91, 0);
			}
			else if (colour[i][j] == 6) {
				// Piece J
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 2, 255, 129, 0, 181, 91);
			}
			else if (colour[i][j] == 7) {
				// Piece T
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 255, 255, 79, 232, 232, 0);
			}
		}
	}
}
void Board::fill_empty() {			// fills the empty spaces in board
	int a1 = 70, b1 = 90;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 11; j++) {
			if (board[i][j] == false) {
				drawRectangle(a1 + (j * 20), 70 + (i * 20), b1 + (j * 20), 90 + (i * 20), 0, 0, 0, 0, 0, 0);
			}
		}
	}
}

// Piece Functions
Piece::Piece() {		//default constructor
	x = 0;
	y = 20;
	rotation = 0;
}
int Piece::get_x() {		//getter of x co-ordinate
	return x;
}
int Piece::get_y() {		//getter of y co-ordinate
	return y;
}
int Piece::get_rotation() {		//getter of rotation number
	return rotation;
}
void Piece::set_x(int x) {		//setter of x co-ordinate
	this->x = x;
}
void Piece::set_y(int y) {		//setter of y co-ordinate
	this->y = y;
}
void Piece::set_rotation(int rotation) {		//setter of rotation number
	this->rotation = rotation;
}

// Piece_L Function
bool Piece_L::print() {		//function of printing the piece
	int count = 0;
	int last_value = 0;
	int temp = 0;
	bool check = false;
	board = get_board();			//gets the board set previously
	bool flag = false;
	while (1) {
		if (rotation == 0) {			//default rotation
			int a1 = 170, b1 = 190;
			for (int i = 0; i < 4; i++) {
				if (board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			if (y > 340) {
				y -= 20;
			}
			while (y <= 340) {
				if (y != 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

					if (board[temp1 + 3][temp2] == false && board[temp1 + 3][temp2 + 1] == false) {
						//bottom border
						temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 2][temp2 + 1] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 3][temp2] || board[i + 3][temp2 + 1]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 90 + last_value, b1 + 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 90 + last_value, b1 + 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								last_value = temp;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 255, 156, 0, 0, 0, 0);
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}

						//piece drawn
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 2][temp2 + 1] = true;
						flag = true;

						colour[temp1][temp2] = 1;
						colour[temp1 + 1][temp2] = 1;
						colour[temp1 + 2][temp2] = 1;
						colour[temp1 + 2][temp2 + 1] = 1;

						break;
					}
				}
				if (y == 340) {					//piece drawn at the bottom
					int temp1 = ((y / 20) - 1);
					int temp2 = ((x / 20) + 5);
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 2][temp2] = true;
					board[temp1 + 2][temp2 + 1] = true;

					colour[temp1][temp2] = 1;
					colour[temp1 + 1][temp2] = 1;
					colour[temp1 + 2][temp2] = 1;
					colour[temp1 + 2][temp2 + 1] = 1;

					flag = true;
					break;
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {		//piece moved down
					if (y != 340) {
						int temp1 = ((y / 20) - 1);
						int temp2 = ((x / 20) + 5);

						if (board[temp1 + 3][temp2] == false && board[temp1 + 3][temp2 + 1] == false) {
							//bottom border
							temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 2][temp2 + 1] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 3][temp2] || board[i + 3][temp2 + 1]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 90 + last_value, b1 + 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 90 + last_value, b1 + 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									last_value = temp;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 255, 156, 0, 0, 0, 0);
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 2][temp2] = true;
							board[temp1 + 2][temp2 + 1] = true;
							flag = true;

							colour[temp1][temp2] = 1;
							colour[temp1 + 1][temp2] = 1;
							colour[temp1 + 2][temp2] = 1;
							colour[temp1 + 2][temp2 + 1] = 1;

							break;
						}
					}
					if (y == 340) {			//prints the piece at the bottom
						int temp1 = ((y / 20) - 1);
						int temp2 = ((x / 20) + 5);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 2][temp2 + 1] = true;
						flag = true;

						colour[temp1][temp2] = 1;
						colour[temp1 + 1][temp2] = 1;
						colour[temp1 + 2][temp2] = 1;
						colour[temp1 + 2][temp2 + 1] = 1;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {			//moves the piece and borders rightwards
					if (x != 80) {
						int temp1 = ((y / 20) - 1);
						int temp2 = ((x / 20) + 5);
						if (board[temp1][temp2 + 1] == false) {
							if (board[temp1 + 1][temp2 + 1] == false) {
								if (board[temp1 + 2][temp2 + 2] == false) {
									x += 20;
									count = 2;
								}
							}
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {		//moves the piece and borders leftwards
					if (x != -100) {
						int temp1 = y / 20, temp2 = x / 20;
						if (board[temp1 - 1][temp2 + 4] == false) {
							if (board[temp1][temp2 + 4] == false) {
								if (board[temp1 + 1][temp2 + 4] == false) {
									x -= 20;
									count = 1;
								}
							}
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {		//rotates the piece
					rotation++;
					drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 1) {				//first rotation
			int a1 = 150, b1 = 170;
			for (int i = 0; i < 3; i++) {
				if (board[i][4] || board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			if (x < -80) {
				x += 20;
			}
			while (y <= 360) {
				if (y != 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

					if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
						//bottom border
						temp = 340;
						while (1) {
							if (board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false && board[(temp / 20)][temp2 + 2] == false) {
								for (int i = 0; i < 17; i++) {
									if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								last_value = temp;
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						//prints the piece
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						delay(500);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);

						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;
						board[temp1][temp2 + 2] = true;

						flag = true;

						colour[temp1 + 1][temp2] = 1;
						colour[temp1 + 1][temp2 + 1] = 1;
						colour[temp1 + 1][temp2 + 2] = 1;
						colour[temp1][temp2 + 2] = 1;

						break;
					}
				}
				if (y == 360) {		//prints the piece at bottom
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					int temp1 = ((y / 20) - 1);
					int temp2 = ((x / 20) + 4);

					board[temp1 + 1][temp2] = true;
					board[temp1 + 1][temp2 + 1] = true;
					board[temp1 + 1][temp2 + 2] = true;
					board[temp1][temp2 + 2] = true;

					flag = true;

					colour[temp1 + 1][temp2] = 1;
					colour[temp1 + 1][temp2 + 1] = 1;
					colour[temp1 + 1][temp2 + 2] = 1;
					colour[temp1][temp2 + 2] = 1;

					break;
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {		//moves the piece down fastly
					if (y != 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

						if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
							temp = 340;
							while (1) {
								if (board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false && board[(temp / 20)][temp2 + 2] == false) {
									for (int i = 0; i < 17; i++) {
										if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									last_value = temp;
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);

							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);

							board[temp1 + 1][temp2] = true;
							board[temp1 + 1][temp2 + 1] = true;
							board[temp1 + 1][temp2 + 2] = true;
							board[temp1][temp2 + 2] = true;

							flag = true;

							colour[temp1 + 1][temp2] = 1;
							colour[temp1 + 1][temp2 + 1] = 1;
							colour[temp1 + 1][temp2 + 2] = 1;
							colour[temp1][temp2 + 2] = 1;

							break;
						}
					}
					if (y == 360) {				//prints the piece at the bottom
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						int temp1 = ((y / 20) - 1);
						int temp2 = ((x / 20) + 4);

						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;
						board[temp1][temp2 + 2] = true;

						flag = true;

						colour[temp1 + 1][temp2] = 1;
						colour[temp1 + 1][temp2 + 1] = 1;
						colour[temp1 + 1][temp2 + 2] = 1;
						colour[temp1][temp2 + 2] = 1;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {				//moves the piece and borders rightwards
					if (x != 80) {
						int temp1 = y / 20;
						int temp2 = x / 20;
						if (board[temp1 - 1][temp2 + 6] == false && board[temp1][temp2 + 6] == false) {
							x += 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {			//moves the piece and borders leftwards
					if (x != -80) {
						int temp1 = y / 20, temp2 = x / 20;
						if (board[temp1][temp2 + 3] == false && board[temp1 - 1][temp2 + 5] == false) {
							x -= 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {			//rotates the piece
					rotation++;
					drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 2) {			//second rotation
			int a1 = 150, b1 = 170;
			for (int i = 0; i <= 3; i++) {
				if (board[i][4] || board[i][5]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			if (y > 340) {
				y -= 20;
			}
			while (y <= 340) {
				if (y != 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

					if (board[temp1 + 1][temp2 - 1] == false && board[temp1 + 3][temp2] == false) {
						temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2 - 1] == false && board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 1][temp2 - 1] || board[i + 3][temp2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 90 + last_value, b1 + 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 90 + last_value, b1 + 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 255, 156, 0, 0, 0, 0);
								count = 0;
								last_value = temp;
								break;
							}
							else {
								temp -= 20;
							}
						}

						//prints the piece
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

						board[temp1][temp2 - 1] = true;
						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;

						flag = true;

						colour[temp1][temp2 - 1] = 1;
						colour[temp1][temp2] = 1;
						colour[temp1 + 1][temp2] = 1;
						colour[temp1 + 2][temp2] = 1;

						break;
					}
				}
				if (y == 340) {		//prints the piece at the bottom
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
					int temp1 = ((y / 20) - 1);
					int temp2 = ((x / 20) + 5);

					board[temp1][temp2 - 1] = true;
					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 2][temp2] = true;
					flag = true;

					colour[temp1][temp2 - 1] = 1;
					colour[temp1][temp2] = 1;
					colour[temp1 + 1][temp2] = 1;
					colour[temp1 + 2][temp2] = 1;

					break;
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {			//moves the piece downwards quickly
					if (y != 340) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

						if (board[temp1 + 1][temp2 - 1] == false && board[temp1 + 3][temp2] == false) {
							temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2 - 1] == false && board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 1][temp2 - 1] || board[i + 3][temp2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 90 + last_value, b1 + 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 90 + last_value, b1 + 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 255, 156, 0, 0, 0, 0);
									count = 0;
									last_value = temp;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

							board[temp1][temp2 - 1] = true;
							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 2][temp2] = true;

							flag = true;

							colour[temp1][temp2 - 1] = 1;
							colour[temp1][temp2] = 1;
							colour[temp1 + 1][temp2] = 1;
							colour[temp1 + 2][temp2] = 1;

							break;
						}
					}
					if (y == 340) {			//prints the piece at the bottom
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
						int temp1 = ((y / 20) - 1);
						int temp2 = ((x / 20) + 5);

						board[temp1][temp2 - 1] = true;
						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;

						flag = true;

						colour[temp1][temp2 - 1] = 1;
						colour[temp1][temp2] = 1;
						colour[temp1 + 1][temp2] = 1;
						colour[temp1 + 2][temp2] = 1;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {			//moves the piece and borders towards the right
					if (x != 100) {
						int temp1 = y / 20;
						int temp2 = x / 20;
						if (board[temp1][temp2 + 6] == false && board[temp1 - 1][temp2 + 6] == false && board[temp1 - 2][temp2 + 6] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {		//moves the piece and borders towards the left
					if (x != -80) {
						int temp1 = y / 20, temp2 = x / 20;
						if (board[temp1 - 2][temp2 + 4] == false && board[temp1 - 1][temp2 + 5] == false && board[temp1][temp2 + 5] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {		//rotates the piece
					rotation++;
					drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 3) {			//third rotation of the piece
			if (x > 80) {
				x -= 20;
			}
			int a1 = 150, b1 = 170;
			for (int i = 0; i < 3; i++) {
				if (board[i][4] || board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 360) {
				if (y != 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					//bottom border
					if (board[temp1 + 2][temp2] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false) {
						temp = 340;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 2][temp2] || board[i + 1][temp2 + 1] || board[i + 1][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
								count = 0;
								last_value = temp;
								break;
							}
							else {
								temp -= 20;
							}
						}

						//piece drawn
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1 + 1][temp2] = true;

						flag = true;

						colour[temp1][temp2] = 1;
						colour[temp1][temp2 + 1] = 1;
						colour[temp1][temp2 + 2] = 1;
						colour[temp1 + 1][temp2] = 1;

						break;
					}
				}
				if (y == 360) {			//piece drawn at the bottom of the screen
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
					int temp1 = ((y / 20) - 1);
					int temp2 = ((x / 20) + 4);

					board[temp1][temp2] = true;
					board[temp1][temp2 + 1] = true;
					board[temp1][temp2 + 2] = true;
					board[temp1 + 1][temp2] = true;

					flag = true;

					colour[temp1][temp2] = 1;
					colour[temp1][temp2 + 1] = 1;
					colour[temp1][temp2 + 2] = 1;
					colour[temp1 + 1][temp2] = 1;

					break;
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {			//brings the piece down quickly
					if (y != 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

						if (board[temp1 + 2][temp2] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false) {
							temp = 340;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 2][temp2] || board[i + 1][temp2 + 1] || board[i + 1][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 156, 0, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 156, 0, 0, 0, 0);
									count = 0;
									last_value = temp;
									break;
								}
								else {
									temp -= 20;
								}
							}

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
							board[temp1][temp2] = true;
							board[temp1][temp2 + 1] = true;
							board[temp1][temp2 + 2] = true;
							board[temp1 + 1][temp2] = true;

							flag = true;

							colour[temp1][temp2] = 1;
							colour[temp1][temp2 + 1] = 1;
							colour[temp1][temp2 + 2] = 1;
							colour[temp1 + 1][temp2] = 1;

							break;
						}
					}
					if (y == 360) {		//prints the piece at the bottom
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
						int temp1 = ((y / 20) - 1);
						int temp2 = ((x / 20) + 4);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1 + 1][temp2] = true;

						flag = true;

						colour[temp1][temp2] = 1;
						colour[temp1][temp2 + 1] = 1;
						colour[temp1][temp2 + 2] = 1;
						colour[temp1 + 1][temp2] = 1;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {			//moves the piece and borders rightwards
					if (x != 80) {
						int temp1 = y / 20;
						int temp2 = x / 20;
						if (board[temp1 - 1][temp2 + 7] == false && board[temp1][temp2 + 5] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {			//moves the piece and borders leftwards
					if (x != -80) {
						int temp1 = y / 20, temp2 = x / 20;
						if (board[temp1][temp2 + 3] == false && board[temp1 - 1][temp2 + 3] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {			//rotates the piece and brings it to default rotation
					rotation = 0;
					drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	set_board(board);			//sets the board after drawing the piece
	return check;
}
void Piece_L::next_piece_call() {			//function of printing the piece on screen
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);
}
void Piece_L::next_piece_remove() {			//function of removing the piece
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
}
void Piece_L::rotations_call() {		//function of printing rotations of piece
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

	// Rotation == 1
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);

	// Rotation == 2
	a1 += 80; b1 += 80;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 255, 156, 0, 128, 0, 128);

	// Rotation == 3
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 156, 0, 128, 0, 128);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 156, 0, 128, 0, 128);
}
void Piece_L::rotations_call_remove() {				//function of removing the rotations of piece
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);

	// Rotation == 1
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);

	// Rotation == 2
	a1 += 80; b1 += 80;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);

	// Rotation == 3
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
//SAME LOGICS HAVE BEEN IMPLEMENTED IN EVERY PIECE

// Piece_S Function
bool Piece_S::print() {
	int count = 0;
	int last_value = 0;
	bool check = false;
	board = get_board();
	bool flag = false;
	int a1 = 170, b1 = 190;
	if (rotation > 1) {
		rotation = 0;
	}
	while (1) {
		if (x < -80) {
			x += 20;
		}

		if (rotation == 0) {
			for (int i = 0; i < 3; i++) {
				if (board[i][4] || board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 360) {
				if (y < 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false) {
						int temp = 340;
						//bottom border
						while (1) {
							if (board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 1][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 - 20 + (x - 20), 70 + last_value, b1 - 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 - 20 + (x + 20), 70 + last_value, b1 - 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 235, 122, 179, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 235, 122, 179, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
								drawRectangle(a1 - 20 + x, 70 + temp, b1 - 20 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);

						board[temp1][temp2 + 2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2] = true;

						flag = true;

						colour[temp1][temp2 + 2] = 2;
						colour[temp1][temp2 + 1] = 2;
						colour[temp1 + 1][temp2 + 1] = 2;
						colour[temp1 + 1][temp2] = 2;

						break;
					}
				}
				if (y == 360) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

					board[temp1][temp2 + 1] = true;
					board[temp1][temp2 + 2] = true;
					board[temp1 + 1][temp2 + 1] = true;
					board[temp1 + 1][temp2] = true;

					flag = true;

					colour[temp1][temp2 + 1] = 2;
					colour[temp1][temp2 + 2] = 2;
					colour[temp1 + 1][temp2 + 1] = 2;
					colour[temp1 + 1][temp2] = 2;

					break;
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y < 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
						if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false) {
							int temp = 340;
							//bottom border
							while (1) {
								if (board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 1][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 - 20 + (x - 20), 70 + last_value, b1 - 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 - 20 + (x + 20), 70 + last_value, b1 - 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 235, 122, 179, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 235, 122, 179, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
									drawRectangle(a1 - 20 + x, 70 + temp, b1 - 20 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);

							board[temp1][temp2 + 2] = true;
							board[temp1][temp2 + 1] = true;
							board[temp1 + 1][temp2 + 1] = true;
							board[temp1 + 1][temp2] = true;

							flag = true;

							colour[temp1][temp2 + 2] = 2;
							colour[temp1][temp2 + 1] = 2;
							colour[temp1 + 1][temp2 + 1] = 2;
							colour[temp1 + 1][temp2] = 2;

							break;
						}
					}
					if (y == 360) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;

						flag = true;

						colour[temp1][temp2 + 1] = 2;
						colour[temp1][temp2 + 2] = 2;
						colour[temp1 + 1][temp2 + 1] = 2;
						colour[temp1 + 1][temp2] = 2;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
						if (board[temp1][temp2 + 3] == false && board[temp1 + 1][temp2 + 2] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -80) {
						int temp1 = ((y / 20) - 1), temp2 = x / 20;

						if (temp2 < 0) {
							if (temp2 == -1) {
								temp2 = 4;
							}
							else if (temp2 == -2) {
								temp2 = 3;
							}
							else if (temp2 == -3) {
								temp2 = 2;
							}
							else if (temp2 == -4) {
								temp2 = 1;
							}
						}
						else if (temp2 > 0) {
							if (temp2 == 1) {
								temp2 = 6;
							}
							else if (temp2 == 2) {
								temp2 = 7;
							}
							else if (temp2 == 3) {
								temp2 = 8;
							}
							else if (temp2 == 4) {
								temp2 = 9;
							}
						}
						else if (temp2 == 0) {
							temp2 = 5;
						}
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 2] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 - 20 + x, 70 + last_value, b1 - 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}

		if (rotation == 1) {
			if (y > 360) {
				y -= 20;
			}
			for (int i = 0; i < 3; i++) {
				if (board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 340) {
				if (y < 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

					if (board[temp1 + 2][temp2] == false && board[temp1 + 3][temp2 + 1] == false) {
						int temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 2][temp2 + 1] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 2][temp2] || board[i + 3][temp2 + 1]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 90 + last_value, b1 + 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 90 + last_value, b1 + 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 235, 122, 179, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 235, 122, 179, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 2][temp2 + 1] = true;
						flag = true;

						colour[temp1][temp2] = 2;
						colour[temp1 + 1][temp2] = 2;
						colour[temp1 + 1][temp2 + 1] = 2;
						colour[temp1 + 2][temp2 + 1] = 2;

						break;
					}
				}
				if (y == 340) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
					drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 1][temp2 + 1] = true;
					board[temp1 + 2][temp2 + 1] = true;
					flag = true;

					colour[temp1][temp2] = 2;
					colour[temp1 + 1][temp2] = 2;
					colour[temp1 + 1][temp2 + 1] = 2;
					colour[temp1 + 2][temp2 + 1] = 2;

					break;
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y < 340) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

						if (board[temp1 + 2][temp2] == false && board[temp1 + 3][temp2 + 1] == false) {
							int temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 2][temp2 + 1] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 2][temp2] || board[i + 3][temp2 + 1]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 90 + last_value, b1 + 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 90 + last_value, b1 + 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 235, 122, 179, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 235, 122, 179, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 90 + temp, b1 + 20 + x, 110 + temp, 235, 122, 179, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;;
								}
							}
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
							drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);

							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 1][temp2 + 1] = true;
							board[temp1 + 2][temp2 + 1] = true;
							flag = true;

							colour[temp1][temp2] = 2;
							colour[temp1 + 1][temp2] = 2;
							colour[temp1 + 1][temp2 + 1] = 2;
							colour[temp1 + 2][temp2 + 1] = 2;

							break;
						}
					}
					if (y == 340) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
						drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 2][temp2 + 1] = true;
						flag = true;

						colour[temp1][temp2] = 2;
						colour[temp1 + 1][temp2] = 2;
						colour[temp1 + 1][temp2 + 1] = 2;
						colour[temp1 + 2][temp2 + 1] = 2;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					if (x != 80) {
						int temp1 = ((y / 20) - 1);
						int temp2 = x / 20;
						if (board[temp1][temp2 + 6] == false && board[temp1 + 1][temp2 + 7] == false && board[temp1 + 2][temp2 + 7] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					if (x != -100) {
						int temp1 = ((y / 20) - 1);
						int temp2 = x / 20;
						if (temp2 < 0) {
							if (temp2 == -1) {
								temp2 = 4;
							}
							else if (temp2 == -2) {
								temp2 = 3;
							}
							else if (temp2 == -3) {
								temp2 = 2;
							}
							else if (temp2 == -4) {
								temp2 = 1;
							}
						}
						else if (temp2 > 0) {
							if (temp2 == 1) {
								temp2 = 6;
							}
							else if (temp2 == 2) {
								temp2 = 7;
							}
							else if (temp2 == 3) {
								temp2 = 8;
							}
							else if (temp2 == 4) {
								temp2 = 9;
							}
						}
						else if (temp2 == 0) {
							temp2 = 5;
						}
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false && board[temp1 + 2][temp2] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + last_value, b1 + 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 90 + last_value, b1 + 20 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	set_board(board);
	return check;
}
void Piece_S::next_piece_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
}
void Piece_S::next_piece_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
void Piece_S::rotations_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;
	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
	// Rotation == 1
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 235, 122, 179, 225, 56, 141);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 235, 122, 179, 225, 56, 141);
}
void Piece_S::rotations_call_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;
	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	// Rotation == 1
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 90 + y, b1 + 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
}
//SAME LOGICS HAVE BEEN IMPLEMENTED IN EVERY PIECE

// Piece_Z Function
bool Piece_Z::print() {
	int temp = 0;
	int count = 0;
	int last_value = 0;
	bool check = false;
	board = get_board();
	bool flag = false;
	if (rotation > 1) {
		rotation = 0;
	}
	int a1 = 170, b1 = 190;
	while (1) {
		if (rotation == 0) {
			if (x > 60) {
				x -= 20;
			}
			for (int i = 0; i < 3; i++) {
				if (board[i][5] || board[i][6] || board[i][7]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 360) {
				if (y < 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (board[temp1 + 1][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
						temp = 340;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
								for (int i = 0; i < 17; i++) {
									if (board[i + 1][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 2, 129, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 2, 129, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;
						flag = true;

						colour[temp1][temp2] = 3;
						colour[temp1][temp2 + 1] = 3;
						colour[temp1 + 1][temp2 + 1] = 3;
						colour[temp1 + 1][temp2 + 2] = 3;

						break;
					}
				}
				if (y == 360) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

					board[temp1][temp2] = true;
					board[temp1][temp2 + 1] = true;
					board[temp1 + 1][temp2 + 1] = true;
					board[temp1 + 1][temp2 + 2] = true;

					flag = true;

					colour[temp1][temp2] = 3;
					colour[temp1][temp2 + 1] = 3;
					colour[temp1 + 1][temp2 + 1] = 3;
					colour[temp1 + 1][temp2 + 2] = 3;

					break;
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y < 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						if (board[temp1 + 1][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
							temp = 340;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
									for (int i = 0; i < 17; i++) {
										if (board[i + 1][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 2, 129, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 2, 129, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							board[temp1][temp2] = true;
							board[temp1][temp2 + 1] = true;
							board[temp1 + 1][temp2 + 1] = true;
							board[temp1 + 1][temp2 + 2] = true;

							flag = true;

							colour[temp1][temp2] = 3;
							colour[temp1][temp2 + 1] = 3;
							colour[temp1 + 1][temp2 + 1] = 3;
							colour[temp1 + 1][temp2 + 2] = 3;

							break;
						}
					}
					if (y == 360) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;

						flag = true;

						colour[temp1][temp2] = 3;
						colour[temp1][temp2 + 1] = 3;
						colour[temp1 + 1][temp2 + 1] = 3;
						colour[temp1 + 1][temp2 + 2] = 3;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = x / 20;
					if (x != 60) {
						if (board[temp1][temp2 + 7] == false && board[temp1 + 1][temp2 + 8] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = x / 20;
					temp2 += 5;
					if (x != -100) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + last_value, b1 + 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 70 + last_value, b1 + 40 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 1) {
			if (y > 340) {
				y -= 20;
			}
			for (int i = 0; i < 3; i++) {
				if (board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 340) {
				if (y != 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 6);
					if (board[temp1 + 3][temp2 - 1] == false && board[temp1 + 2][temp2] == false) {
						temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 - 1] == false && board[(temp / 20) + 2][temp2 - 1] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 2][temp2] || board[i + 3][temp2 - 1]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 2, 129, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
								drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 2, 129, 0, 0, 0);
								count = 0;
								last_value = temp;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);
						delay(500);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 - 1] = true;
						board[temp1 + 2][temp2 - 1] = true;
						flag = true;

						colour[temp1][temp2] = 3;
						colour[temp1 + 1][temp2] = 3;
						colour[temp1 + 1][temp2 - 1] = 3;
						colour[temp1 + 2][temp2 - 1] = 3;

						break;
					}
				}
				if (y == 340) {
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 6);

					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 1][temp2 - 1] = true;
					board[temp1 + 2][temp2 - 1] = true;
					flag = true;

					colour[temp1][temp2] = 3;
					colour[temp1 + 1][temp2] = 3;
					colour[temp1 + 1][temp2 - 1] = 3;
					colour[temp1 + 2][temp2 - 1] = 3;

					break;
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 340) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 6);
						if (board[temp1 + 3][temp2 - 1] == false && board[temp1 + 2][temp2] == false) {
							temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 - 1] == false && board[(temp / 20) + 2][temp2 - 1] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 2][temp2] || board[i + 3][temp2 - 1]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 2, 129, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 2, 129, 0, 0, 0);
									drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 2, 129, 0, 0, 0);
									count = 0;
									last_value = temp;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);

							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);

							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 1][temp2 - 1] = true;
							board[temp1 + 2][temp2 - 1] = true;

							flag = true;

							colour[temp1][temp2] = 3;
							colour[temp1 + 1][temp2] = 3;
							colour[temp1 + 1][temp2 - 1] = 3;
							colour[temp1 + 2][temp2 - 1] = 3;

							break;
						}
					}
					if (y == 340) {
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 6);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 - 1] = true;
						board[temp1 + 2][temp2 - 1] = true;
						flag = true;

						colour[temp1][temp2] = 3;
						colour[temp1 + 1][temp2] = 3;
						colour[temp1 + 1][temp2 - 1] = 3;
						colour[temp1 + 2][temp2 - 1] = 3;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 6);
					if (x != 80) {
						if (board[temp1][temp2 + 1] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 2][temp2] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 6);
					if (x != -100) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 2] == false && board[temp1 + 2][temp2 - 2] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + last_value, b1 + 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 90 + last_value, b1 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	set_board(board);
	return check;
}
void Piece_Z::next_piece_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);
}
void Piece_Z::next_piece_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
void Piece_Z::rotations_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 2, 129, 139, 0, 0);

	// Rotation == 1
	a1 += 80; b1 += 80;
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 2, 129, 139, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 2, 129, 139, 0, 0);
}
void Piece_Z::rotations_call_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);

	// Rotation == 1
	a1 += 80; b1 += 80;
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
}
//SAME LOGICS HAVE BEEN IMPLEMENTED IN EVERY PIECE

// Piece_O Function
bool Piece_O::print() {
	int temp = 0;
	int count = 0;
	int last_value = 0;
	board = get_board();
	int a1 = 170, b1 = 190;
	bool check = false;
	for (int i = 0; i < 2; i++) {
		if (board[i][5] || board[i][6]) {
			check = true;
			gotoxy(0, 24);
		}
	}

	while (y <= 360) {
		if (check) {
			break;
		}
		if (y < 360) {
			int temp1 = ((y / 20) - 1), temp2 = x / 20;
			temp2 += 5;
			if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false) {
				temp = 340;
				while (1) {
					if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false) {
						for (int i = 0; i < 17; i++) {
							if (board[i + 2][temp2] || board[i + 2][temp2 + 1]) {
								temp = i * 20;
								break;
							}
						}
						if (count != 0) {
							if (count == 2) {
								drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
								drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
							}
							else if (count == 1) {
								drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
								drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
								drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
							}
						}
						temp += 20;
						drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 0, 232, 232, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 0, 232, 232, 0, 0, 0);
						drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 0, 232, 232, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 0, 232, 232, 0, 0, 0);
						last_value = temp;
						count = 0;
						break;
					}
					else {
						temp -= 20;
					}
				}
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);
				delay(500);
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
				y += 20;
			}
			else {
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);

				board[temp1][temp2] = true;
				board[temp1][temp2 + 1] = true;
				board[temp1 + 1][temp2] = true;
				board[temp1 + 1][temp2 + 1] = true;

				colour[temp1][temp2] = 4;
				colour[temp1][temp2 + 1] = 4;
				colour[temp1 + 1][temp2] = 4;
				colour[temp1 + 1][temp2 + 1] = 4;

				break;
			}
		}
		if (y == 360) {
			drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
			drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
			drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
			drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);

			int temp1 = ((y / 20) - 1), temp2 = x / 20;
			temp2 += 5;
			board[temp1][temp2] = true;
			board[temp1][temp2 + 1] = true;
			board[temp1 + 1][temp2] = true;
			board[temp1 + 1][temp2 + 1] = true;

			colour[temp1][temp2] = 4;
			colour[temp1][temp2 + 1] = 4;
			colour[temp1 + 1][temp2] = 4;
			colour[temp1 + 1][temp2 + 1] = 4;

			break;
		}
		if (GetAsyncKeyState(VK_DOWN) != 0) {
			if (y != 360) {
				int temp1 = ((y / 20) - 1), temp2 = x / 20;
				temp2 += 5;
				if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false) {
					temp = 340;
					while (1) {
						if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false) {
							for (int i = 0; i < 17; i++) {
								if (board[i + 2][temp2] || board[i + 2][temp2 + 1]) {
									temp = i * 20;
									break;
								}
							}
							if (count != 0) {
								if (count == 2) {
									drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
								}
								else if (count == 1) {
									drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
								}
							}
							temp += 20;
							drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 0, 232, 232, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 0, 232, 232, 0, 0, 0);
							drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 0, 232, 232, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 0, 232, 232, 0, 0, 0);
							last_value = temp;
							count = 0;
							break;
						}
						else {
							temp -= 20;
						}
					}
					y += 20;
				}
				else {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);

					board[temp1][temp2] = true;
					board[temp1][temp2 + 1] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 1][temp2 + 1] = true;

					colour[temp1][temp2] = 4;
					colour[temp1][temp2 + 1] = 4;
					colour[temp1 + 1][temp2] = 4;
					colour[temp1 + 1][temp2 + 1] = 4;

					break;
				}
			}
			if (y == 360) {
				drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
				drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);

				int temp1 = ((y / 20) - 1), temp2 = x / 20;
				temp2 += 5;
				board[temp1][temp2] = true;
				board[temp1][temp2 + 1] = true;
				board[temp1 + 1][temp2] = true;
				board[temp1 + 1][temp2 + 1] = true;

				colour[temp1][temp2] = 4;
				colour[temp1][temp2 + 1] = 4;
				colour[temp1 + 1][temp2] = 4;
				colour[temp1 + 1][temp2 + 1] = 4;

				break;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) != 0) {
			int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

			if (x != 80) {
				if (board[temp1][temp2 + 2] == false && board[temp1 + 1][temp2 + 2] == false) {
					x += 20;
					count = 2;
				}
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) != 0) {
			int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
			if (x != -100) {
				if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false) {
					x -= 20;
					count = 1;
				}
			}
		}
	}
	set_board(board);
	return check;
}
void Piece_O::next_piece_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);
}
void Piece_O::next_piece_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
void Piece_O::rotations_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 232, 232, 0, 181, 181);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 232, 232, 0, 181, 181);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 232, 232, 0, 181, 181);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 232, 232, 0, 181, 181);
}
void Piece_O::rotations_call_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
//SAME LOGICS HAVE BEEN IMPLEMENTED IN EVERY PIECE

// Piece_I Function
bool Piece_I::print() {
	int temp = 0;
	int count = 0;
	int last_value = 0;
	bool check = false;
	board = get_board();
	bool flag = false;
	if (rotation > 1) {
		rotation = 0;
	}
	int a1 = 130, b1 = 150;
	while (1) {
		if (rotation == 0) {
			if (x > 80) {
				x -= 60;
			}
			if (board[1][3] || board[1][4] || board[1][5] || board[1][6]) {
				check = true;
				gotoxy(0, 24);

				break;
			}
			while (y <= 380) {
				if (y != 380) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
					if (board[temp1 + 1][temp2] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false && board[temp1 + 1][temp2 + 3] == false) {
						temp = 360;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20)][temp2 + 3] == false) {
								for (int i = 0; i < 17; i++) {
									if (board[i + 1][temp2] || board[i + 1][temp2 + 1] || board[i + 1][temp2 + 2] || board[i + 1][temp2 + 3]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 60 + (x - 20), 50 + last_value, b1 + 60 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 60 + (x + 20), 50 + last_value, b1 + 60 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
								drawRectangle(a1 + 60 + x, 50 + temp, b1 + 60 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1][temp2 + 3] = true;
						flag = true;

						colour[temp1][temp2] = 5;
						colour[temp1][temp2 + 1] = 5;
						colour[temp1][temp2 + 2] = 5;
						colour[temp1][temp2 + 3] = 5;

						break;
					}
				}
				if (y == 380) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);

					board[temp1][temp2] = true;
					board[temp1][temp2 + 1] = true;
					board[temp1][temp2 + 2] = true;
					board[temp1][temp2 + 3] = true;
					flag = true;

					colour[temp1][temp2] = 5;
					colour[temp1][temp2 + 1] = 5;
					colour[temp1][temp2 + 2] = 5;
					colour[temp1][temp2 + 3] = 5;

					break;
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 380) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
						if (board[temp1 + 1][temp2] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false && board[temp1 + 1][temp2 + 3] == false) {
							temp = 360;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20)][temp2 + 3] == false) {
									for (int i = 0; i < 17; i++) {
										if (board[i + 1][temp2] || board[i + 1][temp2 + 1] || board[i + 1][temp2 + 2] || board[i + 1][temp2 + 3]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 60 + (x - 20), 50 + last_value, b1 + 60 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 60 + (x + 20), 50 + last_value, b1 + 60 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
									drawRectangle(a1 + 60 + x, 50 + temp, b1 + 60 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);

							board[temp1][temp2] = true;
							board[temp1][temp2 + 1] = true;
							board[temp1][temp2 + 2] = true;
							board[temp1][temp2 + 3] = true;

							flag = true;

							colour[temp1][temp2] = 5;
							colour[temp1][temp2 + 1] = 5;
							colour[temp1][temp2 + 2] = 5;
							colour[temp1][temp2 + 3] = 5;

							break;
						}
					}
					if (y == 380) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1][temp2 + 3] = true;

						flag = true;

						colour[temp1][temp2] = 5;
						colour[temp1][temp2 + 1] = 5;
						colour[temp1][temp2 + 2] = 5;
						colour[temp1][temp2 + 3] = 5;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
					if (x != 80) {
						if (board[temp1][temp2 + 4] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
					if (x != -60) {
						if (board[temp1][temp2 - 1] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 50 + last_value, b1 + 40 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 60 + x, 50 + last_value, b1 + 60 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 1) {
			if (y >= 320) {
				y -= 60;
			}
			if (board[4][3]) {
				check = true;
				gotoxy(0, 24);
				break;
			}
			while (y < 320) {
				if (y != 320) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
					if (board[temp1 + 4][temp2] == false) {
						temp = 300;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 3][temp2] == false) {
								for (int i = 0; i < 15; i++) {
									if (board[i + 4][temp2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 110 + last_value, b1 + (x - 20), 130 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 110 + last_value, b1 + (x + 20), 130 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 129, 2, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 129, 2, 0, 0, 0);
								drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 129, 2, 0, 0, 0);
								drawRectangle(a1 + x, 110 + temp, b1 + x, 130 + temp, 255, 129, 2, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 3][temp2] = true;
						flag = true;

						colour[temp1][temp2] = 5;
						colour[temp1 + 1][temp2] = 5;
						colour[temp1 + 2][temp2] = 5;
						colour[temp1 + 3][temp2] = 5;

						break;
					}
				}
				if (y == 320) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
					drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 2][temp2] = true;
					board[temp1 + 3][temp2] = true;
					flag = true;

					colour[temp1][temp2] = 5;
					colour[temp1 + 1][temp2] = 5;
					colour[temp1 + 2][temp2] = 5;
					colour[temp1 + 3][temp2] = 5;

					break;
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y != 320) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
						if (board[temp1 + 4][temp2] == false) {
							temp = 300;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 3][temp2] == false) {
									for (int i = 0; i < 15; i++) {
										if (board[i + 4][temp2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 110 + last_value, b1 + (x - 20), 130 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 110 + last_value, b1 + (x + 20), 130 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 0, 0, 0, 0, 0, 0);
									drawRectangle(a1 + x, 110 + temp, b1 + x, 130 + temp, 0, 0, 0, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
							drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);
							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 2][temp2] = true;
							board[temp1 + 3][temp2] = true;
							flag = true;

							colour[temp1][temp2] = 5;
							colour[temp1 + 1][temp2] = 5;
							colour[temp1 + 2][temp2] = 5;
							colour[temp1 + 3][temp2] = 5;

							break;
						}
					}
					if (y == 320) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
						drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 3][temp2] = true;

						flag = true;

						colour[temp1][temp2] = 5;
						colour[temp1 + 1][temp2] = 5;
						colour[temp1 + 2][temp2] = 5;
						colour[temp1 + 3][temp2] = 5;

						break;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
					if (x != 140) {
						if (board[temp1][temp2 + 1] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 3][temp2 + 1] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 3);
					if (x != -60) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false && board[temp1 + 2][temp2 - 1] == false && board[temp1 + 3][temp2 - 1] == false)
							x -= 20;
						count = 1;
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 90 + last_value, b1 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 110 + last_value, b1 + x, 130 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	set_board(board);
	return check;
}
void Piece_I::next_piece_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);
}
void Piece_I::next_piece_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 0, 0, 0, 0, 0, 0);
}
void Piece_I::rotations_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	// Rotation == 1
	a1 += 100; b1 += 100;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 129, 2, 181, 91, 0);
	drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 255, 129, 2, 181, 91, 0);
}
void Piece_I::rotations_call_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 60 + x, 50 + y, b1 + 60 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	// Rotation == 1
	a1 += 100; b1 += 100;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 110 + y, b1 + x, 130 + y, 0, 0, 0, 0, 0, 0);
}
//SAME LOGICS HAVE BEEN IMPLEMENTED IN EVERY PIECE

// Piece_J Function
bool Piece_J::print() {
	int temp = 0;
	int count = 0;
	int last_value = 0;;
	bool check = false;
	board = get_board();
	bool flag = false;
	int a1 = 170, b1 = 190;
	while (1) {
		if (rotation == 0) {
			if (x < -80) {
				x += 20;
			}
			if (y > 340) {
				y -= 20;
			}
			for (int i = 0; i < 4; i++) {
				if (board[i][4] || board[i][5]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 340) {
				if (y == 340) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 2][temp2] = true;
					board[temp1 + 2][temp2 - 1] = true;
					flag = true;

					colour[temp1][temp2] = 6;
					colour[temp1 + 1][temp2] = 6;
					colour[temp1 + 2][temp2] = 6;
					colour[temp1 + 2][temp2 - 1] = 6;

					break;
				}
				if (y != 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (board[temp1 + 3][temp2] == false && board[temp1 + 3][temp2 - 1] == false) {
						temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 2][temp2 - 1] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 3][temp2] || board[i + 3][temp2 - 1]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 - 20 + (x - 20), 90 + last_value, b1 - 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 - 20 + (x + 20), 90 + last_value, b1 - 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 - 20 + x, 90 + temp, b1 - 20 + x, 110 + temp, 2, 255, 129, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 2][temp2 - 1] = true;

						flag = true;

						colour[temp1][temp2] = 6;
						colour[temp1 + 1][temp2] = 6;
						colour[temp1 + 2][temp2] = 6;
						colour[temp1 + 2][temp2 - 1] = 6;

						break;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 340) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 2][temp2 - 1] = true;

						colour[temp1][temp2] = 6;
						colour[temp1 + 1][temp2] = 6;
						colour[temp1 + 2][temp2] = 6;
						colour[temp1 + 2][temp2 - 1] = 6;

						flag = true;
						break;
					}
					if (y != 340) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						if (board[temp1 + 3][temp2] == false && board[temp1 + 3][temp2 - 1] == false) {
							temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 2][temp2 - 1] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 3][temp2] || board[i + 3][temp2 - 1]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 - 20 + (x - 20), 90 + last_value, b1 - 20 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 - 20 + (x + 20), 90 + last_value, b1 - 20 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 - 20 + x, 90 + temp, b1 - 20 + x, 110 + temp, 2, 255, 129, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);

							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 2][temp2] = true;
							board[temp1 + 2][temp2 - 1] = true;
							flag = true;

							colour[temp1][temp2] = 6;
							colour[temp1 + 1][temp2] = 6;
							colour[temp1 + 2][temp2] = 6;
							colour[temp1 + 2][temp2 - 1] = 6;

							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != 100) {
						if (board[temp1][temp2 + 1] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 2][temp2 + 1] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != -80) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false && board[temp1 + 2][temp2 - 2] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 90 + last_value, b1 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 - 20 + x, 90 + last_value, b1 - 20 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 1) {
			if (x > 60) {
				x -= 40;
			}
			for (int i = 0; i < 3; i++) {
				if (board[i][5] || board[i][6] || board[i][7]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 360) {
				if (y == 360) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

					board[temp1][temp2] = true;
					board[temp1][temp2 + 1] = true;
					board[temp1][temp2 + 2] = true;
					board[temp1 + 1][temp2 + 2] = true;
					flag = true;

					colour[temp1][temp2] = 6;
					colour[temp1][temp2 + 1] = 6;
					colour[temp1][temp2 + 2] = 6;
					colour[temp1 + 1][temp2 + 2] = 6;

					break;
				}
				if (y != 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (board[temp1 + 1][temp2] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
						temp = 340;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
								for (int i = 0; i < 17; i++) {
									if (board[i + 1][temp2] || board[i + 1][temp2 + 1] || board[i + 2][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1 + 1][temp2 + 2] = true;
						flag = true;

						colour[temp1][temp2] = 6;
						colour[temp1][temp2 + 1] = 6;
						colour[temp1][temp2 + 2] = 6;
						colour[temp1 + 1][temp2 + 2] = 6;

						break;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 360) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1 + 1][temp2 + 2] = true;

						flag = true;

						colour[temp1][temp2] = 6;
						colour[temp1][temp2 + 1] = 6;
						colour[temp1][temp2 + 2] = 6;
						colour[temp1 + 1][temp2 + 2] = 6;

						break;
					}
					if (y != 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						if (board[temp1 + 1][temp2] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
							temp = 340;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
									for (int i = 0; i < 17; i++) {
										if (board[i + 1][temp2] || board[i + 1][temp2 + 1] || board[i + 2][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

							board[temp1][temp2] = true;
							board[temp1][temp2 + 1] = true;
							board[temp1][temp2 + 2] = true;
							board[temp1 + 1][temp2 + 2] = true;

							flag = true;

							colour[temp1][temp2] = 6;
							colour[temp1][temp2 + 1] = 6;
							colour[temp1][temp2 + 2] = 6;
							colour[temp1 + 1][temp2 + 2] = 6;

							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != 60) {
						if (board[temp1][temp2 + 3] == false && board[temp1 + 1][temp2 + 3] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != -100) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 + 1] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 50 + last_value, b1 + 40 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 70 + last_value, b1 + 40 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 2) {
			if (y > 340) {
				y -= 20;
			}
			for (int i = 0; i < 4; i++) {
				if (board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 340) {
				if (y == 340) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					board[temp1][temp2] = true;
					board[temp1][temp2 + 1] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 2][temp2] = true;

					flag = true;

					colour[temp1][temp2] = 6;
					colour[temp1][temp2 + 1] = 6;
					colour[temp1 + 1][temp2] = 6;
					colour[temp1 + 2][temp2] = 6;
					break;
				}
				if (y != 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (board[temp1 + 3][temp2] == false && board[temp1 + 1][temp2 + 1] == false) {
						temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 1][temp2 + 1] || board[i + 3][temp2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 2, 255, 129, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;

						flag = true;

						colour[temp1][temp2] = 6;
						colour[temp1][temp2 + 1] = 6;
						colour[temp1 + 1][temp2] = 6;
						colour[temp1 + 2][temp2] = 6;

						break;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 340) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;

						flag = true;

						colour[temp1][temp2] = 6;
						colour[temp1][temp2 + 1] = 6;
						colour[temp1 + 1][temp2] = 6;
						colour[temp1 + 2][temp2] = 6;

						break;
					}
					if (y != 340) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						if (board[temp1 + 3][temp2] == false && board[temp1 + 1][temp2 + 1] == false) {
							temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 1][temp2 + 1] || board[i + 3][temp2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 2, 255, 129, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);

							board[temp1][temp2] = true;
							board[temp1][temp2 + 1] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 2][temp2] = true;

							flag = true;

							colour[temp1][temp2] = 6;
							colour[temp1][temp2 + 1] = 6;
							colour[temp1 + 1][temp2] = 6;
							colour[temp1 + 2][temp2] = 6;

							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != 80) {
						if (board[temp1][temp2 + 2] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 2][temp2 + 1] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != -100) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false && board[temp1 + 2][temp2 - 1] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 90 + last_value, b1 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 3) {
			if (x > 60) {
				x -= 20;
			}
			for (int i = 0; i < 3; i++) {
				if (board[i][5] || board[i][6] || board[i][7]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 360) {
				if (y == 360) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 1][temp2 + 1] = true;
					board[temp1 + 1][temp2 + 2] = true;
					flag = true;

					colour[temp1][temp2] = 6;
					colour[temp1 + 1][temp2] = 6;
					colour[temp1 + 1][temp2 + 1] = 6;
					colour[temp1 + 1][temp2 + 2] = 6;

					break;
				}
				if (y != 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
						temp = 340;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
								for (int i = 0; i < 17; i++) {
									if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;
						flag = true;
						colour[temp1][temp2] = 6;
						colour[temp1 + 1][temp2] = 6;
						colour[temp1 + 1][temp2 + 1] = 6;
						colour[temp1 + 1][temp2 + 2] = 6;
						break;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 360) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;

						flag = true;
						colour[temp1][temp2] = 6;
						colour[temp1 + 1][temp2] = 6;
						colour[temp1 + 1][temp2 + 1] = 6;
						colour[temp1 + 1][temp2 + 2] = 6;
						break;
					}
					if (y != 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
						if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
							temp = 340;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
									for (int i = 0; i < 17; i++) {
										if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 2, 255, 129, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 1][temp2 + 1] = true;
							board[temp1 + 1][temp2 + 2] = true;
							flag = true;
							colour[temp1][temp2] = 6;
							colour[temp1 + 1][temp2] = 6;
							colour[temp1 + 1][temp2 + 1] = 6;
							colour[temp1 + 1][temp2 + 2] = 6;
							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != 60) {
						if (board[temp1][temp2 + 1] == false && board[temp1 + 1][temp2 + 3] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 5);
					if (x != -100) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + last_value, b1 + 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 70 + last_value, b1 + 40 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	set_board(board);
	return check;
}
void Piece_J::next_piece_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);
}
void Piece_J::next_piece_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);
}
void Piece_J::rotations_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 2, 255, 129, 0, 181, 91);

	// Rotation == 1
	a1 += 40; b1 += 40;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);

	// Rotation == 2
	a1 += 80; b1 += 80;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 2, 255, 129, 0, 181, 91);

	// Rotation == 3
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 2, 255, 129, 0, 181, 91);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 2, 255, 129, 0, 181, 91);
}
void Piece_J::rotations_call_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 - 20 + x, 90 + y, b1 - 20 + x, 110 + y, 0, 0, 0, 0, 0, 0);

	// Rotation == 1
	a1 += 40; b1 += 40;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);

	// Rotation == 2
	a1 += 80; b1 += 80;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);

	// Rotation == 3
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
//SAME LOGICS HAVE BEEN IMPLEMENTED IN EVERY PIECE

// Piece_T Function
bool Piece_T::print() {
	int temp = 0;
	int count = 0;
	int last_value = 0;
	bool check = false;
	board = get_board();
	bool flag = false;
	int a1 = 150, b1 = 170;
	while (1) {
		if (rotation == 0) {
			if (x > 80) {
				x -= 40;
			}
			for (int i = 0; i < 2; i++) {
				if (board[i][4] || board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 360) {
				if (y == 360) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					board[temp1][temp2] = true;
					board[temp1][temp2 + 1] = true;
					board[temp1][temp2 + 2] = true;
					board[temp1 + 1][temp2 + 1] = true;
					flag = true;
					colour[temp1][temp2] = 7;
					colour[temp1][temp2 + 1] = 7;
					colour[temp1][temp2 + 2] = 7;
					colour[temp1 + 1][temp2 + 1] = 7;
					break;
				}
				if (y != 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (board[temp1 + 1][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false) {
						temp = 340;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2 + 1] == false) {
								for (int i = 0; i < 17; i++) {
									if (board[i + 1][temp2] || board[i + 2][temp2 + 1] || board[i + 1][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						flag = true;
						colour[temp1][temp2] = 7;
						colour[temp1][temp2 + 1] = 7;
						colour[temp1][temp2 + 2] = 7;
						colour[temp1 + 1][temp2 + 1] = 7;
						break;
					}
				}
				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 360) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
						board[temp1][temp2] = true;
						board[temp1][temp2 + 1] = true;
						board[temp1][temp2 + 2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						flag = true;
						colour[temp1][temp2] = 7;
						colour[temp1][temp2 + 1] = 7;
						colour[temp1][temp2 + 2] = 7;
						colour[temp1 + 1][temp2 + 1] = 7;
						break;
					}
					if (y != 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
						if (board[temp1 + 1][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false) {
							temp = 340;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20)][temp2 + 1] == false && board[(temp / 20)][temp2 + 2] == false && board[(temp / 20) + 1][temp2 + 1] == false) {
									for (int i = 0; i < 17; i++) {
										if (board[i + 1][temp2] || board[i + 2][temp2 + 1] || board[i + 1][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 50 + last_value, b1 + 40 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 50 + last_value, b1 + 40 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 50 + temp, b1 + 40 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

							board[temp1][temp2] = true;
							board[temp1][temp2 + 1] = true;
							board[temp1][temp2 + 2] = true;
							board[temp1 + 1][temp2 + 1] = true;
							flag = true;
							colour[temp1][temp2] = 7;
							colour[temp1][temp2 + 1] = 7;
							colour[temp1][temp2 + 2] = 7;
							colour[temp1 + 1][temp2 + 1] = 7;
							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != 80) {
						if (board[temp1][temp2 + 3] == false && board[temp1 + 1][temp2 + 2] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != -80) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 50 + last_value, b1 + 40 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + last_value, b1 + 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 1) {
			if (y > 340) {
				y -= 20;
			}
			for (int i = 0; i < 3; i++) {
				if (board[i][4] || board[i][5]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 340) {
				if (y == 340) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 2][temp2] = true;
					board[temp1 + 1][temp2 + 1] = true;
					flag = true;
					colour[temp1][temp2] = 7;
					colour[temp1 + 1][temp2] = 7;
					colour[temp1 + 2][temp2] = 7;
					colour[temp1 + 1][temp2 + 1] = 7;
					break;
				}
				if (y != 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (board[temp1 + 3][temp2] == false && board[temp1 + 2][temp2 + 1] == false) {
						temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 3][temp2] || board[i + 2][temp2 + 1]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						flag = true;
						colour[temp1][temp2] = 7;
						colour[temp1 + 1][temp2] = 7;
						colour[temp1 + 2][temp2] = 7;
						colour[temp1 + 1][temp2 + 1] = 7;
						break;
					}
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 340) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						flag = true;
						colour[temp1][temp2] = 7;
						colour[temp1 + 1][temp2] = 7;
						colour[temp1 + 2][temp2] = 7;
						colour[temp1 + 1][temp2 + 1] = 7;
						break;
					}
					if (y != 340) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
						if (board[temp1 + 3][temp2] == false && board[temp1 + 2][temp2 + 1] == false) {
							temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 2][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 3][temp2] || board[i + 2][temp2 + 1]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 2][temp2] = true;
							board[temp1 + 1][temp2 + 1] = true;
							flag = true;
							colour[temp1][temp2] = 7;
							colour[temp1 + 1][temp2] = 7;
							colour[temp1 + 2][temp2] = 7;
							colour[temp1 + 1][temp2 + 1] = 7;
							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != 100) {
						if (board[temp1][temp2 + 1] == false && board[temp1 + 1][temp2 + 2] == false && board[temp1 + 2][temp2 + 1] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != -80) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 1] == false && board[temp1 + 2][temp2 - 1] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 90 + last_value, b1 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + last_value, b1 + 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 2) {
			if (x > 80) {
				x -= 20;
			}
			for (int i = 0; i < 2; i++) {
				if (board[i][4] || board[i][5] || board[i][6]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 360) {
				if (y == 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);

					board[temp1][temp2 + 1] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 1][temp2 + 1] = true;
					board[temp1 + 1][temp2 + 2] = true;

					colour[temp1][temp2 + 1] = 7;
					colour[temp1 + 1][temp2] = 7;
					colour[temp1 + 1][temp2 + 1] = 7;
					colour[temp1 + 1][temp2 + 2] = 7;
					flag = true;
					break;
				}
				if (y != 360) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
						temp = 340;
						while (1) {
							if (board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
								for (int i = 0; i < 17; i++) {
									if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						delay(500);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);

						board[temp1][temp2 + 1] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;

						colour[temp1][temp2 + 1] = 7;
						colour[temp1 + 1][temp2] = 7;
						colour[temp1 + 1][temp2 + 1] = 7;
						colour[temp1 + 1][temp2 + 2] = 7;
						flag = true;
						break;
					}
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);

						board[temp1][temp2 + 1] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 1][temp2 + 1] = true;
						board[temp1 + 1][temp2 + 2] = true;

						colour[temp1][temp2 + 1] = 7;
						colour[temp1 + 1][temp2] = 7;
						colour[temp1 + 1][temp2 + 1] = 7;
						colour[temp1 + 1][temp2 + 2] = 7;
						flag = true;
						break;
					}
					if (y != 360) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
						if (board[temp1 + 2][temp2] == false && board[temp1 + 2][temp2 + 1] == false && board[temp1 + 2][temp2 + 2] == false) {
							temp = 340;
							while (1) {
								if (board[(temp / 20)][temp2 + 1] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 + 1] == false && board[(temp / 20) + 1][temp2 + 2] == false) {
									for (int i = 0; i < 17; i++) {
										if (board[i + 2][temp2] || board[i + 2][temp2 + 1] || board[i + 2][temp2 + 2]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 70 + last_value, b1 + 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x - 20), 70 + last_value, b1 + 40 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x - 20), 50 + last_value, b1 + 20 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 70 + last_value, b1 + 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 40 + (x + 20), 70 + last_value, b1 + 40 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + 20 + (x + 20), 50 + last_value, b1 + 20 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 70 + temp, b1 + 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + 40 + x, 70 + temp, b1 + 40 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + 20 + x, 50 + temp, b1 + 20 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);

							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);

							board[temp1][temp2 + 1] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 1][temp2 + 1] = true;
							board[temp1 + 1][temp2 + 2] = true;

							colour[temp1][temp2 + 1] = 7;
							colour[temp1 + 1][temp2] = 7;
							colour[temp1 + 1][temp2 + 1] = 7;
							colour[temp1 + 1][temp2 + 2] = 7;
							flag = true;
							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != 80) {
						if (board[temp1][temp2 + 3] == false && board[temp1 - 1][temp2 + 2] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != -80) {
						if (board[temp1][temp2 - 1] == false && board[temp1 - 1][temp2] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation++;
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 70 + last_value, b1 + 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 40 + x, 70 + last_value, b1 + 40 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + 20 + x, 50 + last_value, b1 + 20 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
		if (rotation == 3) {
			if (x < -60) {
				x += 20;
			}
			if (y > 340) {
				y -= 20;
			}
			for (int i = 0; i < 3; i++) {
				if (board[i][3] || board[i][4]) {
					check = true;
					gotoxy(0, 24);
					break;
				}
			}
			while (y <= 340) {
				if (y == 340) {
					drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
					drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

					board[temp1][temp2] = true;
					board[temp1 + 1][temp2] = true;
					board[temp1 + 2][temp2] = true;
					board[temp1 + 1][temp2 - 1] = true;

					flag = true;

					colour[temp1][temp2] = 7;
					colour[temp1 + 1][temp2] = 7;
					colour[temp1 + 2][temp2] = 7;
					colour[temp1 + 1][temp2 - 1] = 7;

					break;
				}
				if (y != 340) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (board[temp1 + 3][temp2] == false && board[temp1 + 2][temp2 - 1] == false) {
						temp = 320;
						while (1) {
							if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 - 1] == false && board[(temp / 20) + 2][temp2] == false) {
								for (int i = 0; i < 16; i++) {
									if (board[i + 3][temp2] || board[i + 2][temp2 - 1]) {
										temp = i * 20;
										break;
									}
								}
								if (count != 0) {
									if (count == 2) {
										drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 - 20 + (x - 20), 70 + last_value, b1 - 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
									else if (count == 1) {
										drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
										drawRectangle(a1 - 20 + (x + 20), 70 + last_value, b1 - 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
									}
								}
								temp += 20;
								drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 255, 79, 0, 0, 0);
								drawRectangle(a1 - 20 + x, 70 + temp, b1 - 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
								last_value = temp;
								count = 0;
								break;
							}
							else {
								temp -= 20;
							}
						}
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						delay(500);
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
						y += 20;
					}
					else {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 1][temp2 - 1] = true;

						flag = true;

						colour[temp1][temp2] = 7;
						colour[temp1 + 1][temp2] = 7;
						colour[temp1 + 2][temp2] = 7;
						colour[temp1 + 1][temp2 - 1] = 7;

						break;
					}
				}

				if (GetAsyncKeyState(VK_DOWN) != 0) {
					if (y == 340) {
						drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
						drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);

						board[temp1][temp2] = true;
						board[temp1 + 1][temp2] = true;
						board[temp1 + 2][temp2] = true;
						board[temp1 + 1][temp2 - 1] = true;
						flag = true;
						colour[temp1][temp2] = 7;
						colour[temp1 + 1][temp2] = 7;
						colour[temp1 + 2][temp2] = 7;
						colour[temp1 + 1][temp2 - 1] = 7;
						break;
					}
					if (y != 340) {
						int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
						if (board[temp1 + 3][temp2] == false && board[temp1 + 2][temp2 - 1] == false) {
							temp = 320;
							while (1) {
								if (board[(temp / 20)][temp2] == false && board[(temp / 20) + 1][temp2] == false && board[(temp / 20) + 1][temp2 - 1] == false && board[(temp / 20) + 2][temp2] == false) {
									for (int i = 0; i < 16; i++) {
										if (board[i + 3][temp2] || board[i + 2][temp2 - 1]) {
											temp = i * 20;
											break;
										}
									}
									if (count != 0) {
										if (count == 2) {
											drawRectangle(a1 + (x - 20), 50 + last_value, b1 + (x - 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 70 + last_value, b1 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x - 20), 90 + last_value, b1 + (x - 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 - 20 + (x - 20), 70 + last_value, b1 - 20 + (x - 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
										else if (count == 1) {
											drawRectangle(a1 + (x + 20), 50 + last_value, b1 + (x + 20), 70 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 70 + last_value, b1 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 + (x + 20), 90 + last_value, b1 + (x + 20), 110 + last_value, 0, 0, 0, 0, 0, 0);
											drawRectangle(a1 - 20 + (x + 20), 70 + last_value, b1 - 20 + (x + 20), 90 + last_value, 0, 0, 0, 0, 0, 0);
										}
									}
									temp += 20;
									drawRectangle(a1 + x, 50 + temp, b1 + x, 70 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + x, 70 + temp, b1 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 + x, 90 + temp, b1 + x, 110 + temp, 255, 255, 79, 0, 0, 0);
									drawRectangle(a1 - 20 + x, 70 + temp, b1 - 20 + x, 90 + temp, 255, 255, 79, 0, 0, 0);
									last_value = temp;
									count = 0;
									break;
								}
								else {
									temp -= 20;
								}
							}
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
							drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
							y += 20;
						}
						else {
							drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
							drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);

							board[temp1][temp2] = true;
							board[temp1 + 1][temp2] = true;
							board[temp1 + 2][temp2] = true;
							board[temp1 + 1][temp2 - 1] = true;

							colour[temp1][temp2] = 7;
							colour[temp1 + 1][temp2] = 7;
							colour[temp1 + 2][temp2] = 7;
							colour[temp1 + 1][temp2 - 1] = 7;
							flag = true;
							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_RIGHT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != 120) {
						if (board[temp1][temp2 + 1] == false && board[temp1 + 1][temp2 + 1] == false && board[temp1 + 2][temp2 + 1] == false) {
							x += 20;
							count = 2;
						}
					}
				}
				else if (GetAsyncKeyState(VK_LEFT) != 0) {
					int temp1 = ((y / 20) - 1), temp2 = ((x / 20) + 4);
					if (x != -60) {
						if (board[temp1][temp2 - 1] == false && board[temp1 + 1][temp2 - 2] == false && board[temp1 + 2][temp2 - 1] == false) {
							x -= 20;
							count = 1;
						}
					}
				}
				else if (GetAsyncKeyState(VK_UP) != 0) {
					rotation = 0;
					drawRectangle(a1 + x, 50 + last_value, b1 + x, 70 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 70 + last_value, b1 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 + x, 90 + last_value, b1 + x, 110 + last_value, 0, 0, 0, 0, 0, 0);
					drawRectangle(a1 - 20 + x, 70 + last_value, b1 - 20 + x, 90 + last_value, 0, 0, 0, 0, 0, 0);
					fill_empty();
					break;
				}
			}
		}
		if (flag) {
			break;
		}
	}
	set_board(board);
	return check;
}
void Piece_T::next_piece_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
}
void Piece_T::next_piece_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 20;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
void Piece_T::rotations_call() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
	// Rotation == 1
	a1 += 80; b1 += 80;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
	// Rotation == 2
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	// Rotation == 3
	a1 += 100; b1 += 100;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 255, 255, 79, 232, 232, 0);
	drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 255, 255, 79, 232, 232, 0);
}
void Piece_T::rotations_call_remove() {
	int a1 = 390, b1 = 410;
	int x = 0, y = 140;

	// Rotation == 0
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 50 + y, b1 + 40 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	// Rotation == 1
	a1 += 80; b1 += 80;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	// Rotation == 2
	a1 += 60; b1 += 60;
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 70 + y, b1 + 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 40 + x, 70 + y, b1 + 40 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + 20 + x, 50 + y, b1 + 20 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	// Rotation == 3
	a1 += 100; b1 += 100;
	drawRectangle(a1 + x, 50 + y, b1 + x, 70 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 70 + y, b1 + x, 90 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 + x, 90 + y, b1 + x, 110 + y, 0, 0, 0, 0, 0, 0);
	drawRectangle(a1 - 20 + x, 70 + y, b1 - 20 + x, 90 + y, 0, 0, 0, 0, 0, 0);
}
//SAME LOGICS HAVE BEEN IMPLEMENTED IN EVERY PIECE

// Tetris
void Tetris::Download() {		//downloads the welcome screen and the game
	system("Color B5");		//sets the background color to blue and text color to purple
	for (int i = 1; i <= 50; i++) {
		showConsoleCursor(false);
		system("CLS");
		setxy(55, 12);
		cout << "Loading ";

		for (int j = 1; j <= i; j++) {
			setxy(33 + j, 14);
			cout << char(219);
		}
		cout << 2 * i << "%";
		if (i >= 1 && i <= 20) {
			setxy(45, 16);
			cout << "Creating Temporary files";
		}
		else if (i >= 20 && i <= 40) {
			setxy(45, 16);
			cout << "Accessing Main Memory";
		}
		else if (i >= 40 && i <= 48) {
			setxy(45, 16);
			cout << "Accessing Cache";
		}
		else {
			setxy(55, 16);
			cout << "Complete. ";
		}
		delaay(1);
	}
	delaay(10);
	Instructions();
}
void Tetris::Instructions() {		//displays the instructions of the game
	system("cls");
	system("Color B5");
	delaay(10);
	cout << "\n\n\t\t\t\t\t" << "INSTRUCTIONS!!!" << endl;
	delaay(10);
	cout << "\n\n\n\t\t\t";
	cout << "1)\tPress " << char(30) << " arrow key to rotate the piece" << endl << endl;
	delaay(10);
	cout << "\t\t\t";
	cout << "2)\tPress " << char(31) << " arrow key to move the piece downwards" << endl << endl;
	delaay(10);
	cout << "\t\t\t";
	cout << "3)\tPress " << char(16) << " arrow key to move the piece rightwards" << endl << endl;
	delaay(10);
	cout << "\t\t\t";
	cout << "4)\tPress " << char(17) << " arrow key to move the piece leftwards" << endl << endl;
	delaay(10);
	cout << "\t\t\tPress Enter to Continue \n";
	_getch();
	PlayGame();
}
void Tetris::PlayGame() {				//allows user to either play the game or exit the system
	char a;
	system("cls");
	system("Color 05");
	cout << "\n\n\t\t\t\t\t" << "WELCOME TO TETRIS GAMEPLAY!!!" << endl << endl;
	cout << "\t\t\t" << "Press any key if you want to continue to the game!" << endl << endl;
	cout << "\t\t\t" << "Press 'N' if you want to exit the game!" << endl << endl;
	cin >> a;
	if (a == 'n' || a == 'N')
	{
		delaay(10);
		cout << "\t\t\t EXITING THE SYSTEM IN \n";
		cout << "\t\t\t\t3" << endl;
		delaay(10);
		cout << "\t\t\t\t2" << endl;
		delaay(10);
		cout << "\t\t\t\t1" << endl;
		delaay(10);
	}
	else
	{
		cls();
		gamePlay();
	}
}
void Tetris::ExitScreen() {			//allows user to either play the game again or exit the system
	char b;
	system("cls");
	system("Color 05");
	cout << "\n\n";
	cout << "\t\t\t" << "Press Enter if you want to play the game AGAIN!!" << endl << endl;
	cout << "\t\t\t" << "Press 'N' if you want to exit the game!" << endl << endl;
	cin >> b;
	if (b == 'n' || b == 'N')
	{
		delaay(10);
		cout << "\t\t\t EXITING THE SYSTEM IN \n";
		cout << "\t\t\t\t3" << endl;
		delaay(10);
		cout << "\t\t\t\t2" << endl;
		delaay(10);
		cout << "\t\t\t\t1" << endl;
		delaay(10);
		system("pause");
		gameOver();
	}
	else
	{
		cls();
		gamePlay();
	}
}
void Tetris::gameOver() {			//Game over printed with graphics
	cls();
	showConsoleCursor(false);

	//G
	drawLine(100, 70, 100, 250, 210, 250, 15);
	drawLine(100, 70, 150, 70, 245, 87, 98);
	drawLine(100, 250, 150, 250, 287, 156, 98);
	drawLine(150, 175, 150, 250, 185, 89, 65);
	drawLine(140, 175, 160, 175, 65, 98, 78);

	//A
	drawLine(170, 250, 185, 150, 210, 178, 98);
	drawLine(185, 150, 200, 250, 178, 210, 98);
	drawLine(175, 195, 195, 195, 154, 87, 98);

	//M
	drawLine(215, 150, 215, 250, 210, 250, 15);
	drawLine(215, 150, 230, 250, 185, 89, 65);
	drawLine(230, 250, 245, 150, 245, 87, 98);
	drawLine(245, 150, 245, 250, 287, 156, 98);

	//E
	drawLine(260, 150, 260, 250, 65, 187, 250);
	drawLine(260, 150, 285, 150, 210, 54, 98);
	drawLine(260, 200, 275, 200, 245, 87, 98);
	drawLine(260, 250, 285, 250, 24, 87, 255);

	//O
	drawEllipse(480, 70, 590, 250, 210, 65, 87);

	//V
	drawLine(610, 150, 625, 250, 254, 98, 78);
	drawLine(625, 250, 640, 150, 187, 45, 98);

	//E
	drawLine(655, 150, 655, 250, 210, 54, 87);
	drawLine(655, 150, 680, 150, 287, 189, 65);
	drawLine(655, 200, 670, 200, 245, 78, 89);
	drawLine(655, 250, 680, 250, 178, 89, 45);

	//R
	drawLine(695, 150, 695, 250, 287, 89, 32);
	drawLine(695, 150, 720, 150, 287, 98, 78);
	drawLine(695, 200, 720, 200, 98, 78, 45);
	drawLine(720, 150, 720, 200, 210, 254, 87);
	drawLine(695, 200, 720, 250, 287, 54, 65);

	drawLine(60, 260, 290, 260, 289, 52, 87);
	drawLine(70, 270, 285, 270, 287, 87, 98);
	drawLine(465, 260, 735, 260, 289, 52, 87);
	drawLine(465, 270, 720, 270, 287, 87, 98);
	drawRectangle(290, 260, 465, 270, 210, 65, 98, 210, 98, 65);
	_getch();
}
void Tetris::printScore(int &score)		//prints score after the game is over before asking for playing again
{
	cls();
	gotoxy(40, 0);
	//S
	drawLine(50, 10, 70, 10, 225, 0, 225);
	drawLine(50, 10, 50, 20, 225, 0, 225);
	drawLine(50, 20, 70, 20, 225, 0, 225);
	drawLine(70, 20, 70, 30, 225, 0, 225);
	drawLine(50, 30, 70, 30, 225, 0, 225);

	//C
	drawLine(80, 10, 100, 10, 225, 0, 225);
	drawLine(80, 10, 80, 30, 225, 0, 225);
	drawLine(80, 30, 100, 30, 225, 0, 225);

	//O
	drawLine(110, 10, 130, 10, 225, 0, 225);
	drawLine(130, 10, 130, 30, 225, 0, 225);
	drawLine(110, 30, 130, 30, 225, 0, 225);
	drawLine(110, 30, 110, 10, 225, 0, 225);

	//R
	drawLine(140, 10, 140, 30, 225, 0, 225);
	drawLine(140, 10, 160, 10, 225, 0, 225);
	drawLine(160, 10, 160, 20, 225, 0, 225);
	drawLine(140, 20, 160, 20, 225, 0, 225);
	drawLine(140, 20, 160, 30, 225, 0, 225);

	//E
	drawLine(170, 10, 190, 10, 225, 0, 225);
	drawLine(170, 10, 170, 30, 225, 0, 225);
	drawLine(170, 20, 190, 20, 225, 0, 225);
	drawLine(170, 30, 190, 30, 225, 0, 225);

	//:
	drawRectangle(210, 15, 215, 18, 225, 0, 225);
	drawRectangle(210, 22, 215, 25, 225, 0, 225);

	showConsoleCursor(false);
	cout << "\n\t\t\t\t";
	
	cout << "Score: " << score;

	delaay(30);
	ExitScreen();
}
void Tetris::gamePlay() {				//Entire game play of Tetris
	srand((unsigned)time(0));
	Piece** piece = new Piece * [7];
	piece[0] = new Piece_L;
	piece[1] = new Piece_S;
	piece[2] = new Piece_Z;
	piece[3] = new Piece_O;
	piece[4] = new Piece_I;
	piece[5] = new Piece_J;
	piece[6] = new Piece_T;
	int count = 0;
	Board b(12, 20);
	bool** board = nullptr;
	int** colour = nullptr;
	int score = 0;
	bool endgame = false;
	int again_random = 0;
	b.print_board();		//prints the board of tetris
	int random = (rand() % 7);
	while (!endgame) {
		again_random = (rand() % 7);
		b.print_board();

		piece[again_random]->next_piece_call();

		piece[random]->rotations_call();
		endgame = piece[random]->print();

		piece[random]->rotations_call_remove();

		piece[random]->set_x(0);
		piece[random]->set_y(20);
		piece[random]->set_rotation(0);

		if (board != nullptr) {
			for (int i = 0; i < 19; i++) {
				delete[] board[i];
			}
			delete[] board;
		}
		colour = piece[random]->get_colour();
		board = piece[random]->get_board();

		b.set_board(board);
		b.set_colour(colour);
		b.fill_board();
		b.check_board(score);

		score = b.get_score();

		if (board != nullptr) {
			for (int i = 0; i < 19; i++) {
				delete[] board[i];
			}
			delete[] board;
		}
		board = nullptr;

		board = b.get_board();
		colour = b.get_colour();

		for (int i = 0; i < 7; i++) {
			piece[i]->set_board(board);
			piece[i]->set_colour(colour);
			piece[i]->set_score(score);
			piece[i]->next_piece_remove();
		}
		b.print_score();

		random = again_random;
	}
	score = b.get_score();
	printScore(score);
	ExitScreen();
}
