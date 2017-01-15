#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// FIRST PROJECT IN C
// SIMPLE CONNECT FOUR GAME PLAYED THROUGH THE SHELL




// myinsert; where piece is 0 or 1 (computer or user)
// c stands for column
// requires: 0 <= c <= 7
bool myinsert(int num_col, int num_row, int piece, int c, int b[num_col][num_row]) {
	for(int i = 0; i <= 7; ++i) {
		if(b[c][i] == -2) {
			b[c][i] = piece;
			if(i-1 >= 0) {
				b[c][i-1] = -2;
			}
			return true;
		}
	}
	return false;
}

void displayboard(int num_col, int num_row, int board[num_col][num_row]) {
	int swidth = 8; //width of each square
	int sheight = 4; //hight of each square
	int number_label = 1; 
	char userP = 'u';
	char compP = 'c';
	int t;
	for(int i = 0; i < (num_row * swidth) - 1; ++i) {
		if(i % 8 == 4) {
			printf("%d", number_label);
			++number_label;
			}
		else {
			printf(" ");
		}
	}
	printf("\n");
	for(int i = 0; i <= num_row * swidth; ++i) {
		printf("-");
	}
	printf("\n");
	for(int i = 1; i < sheight * num_col; ++i) {
		if(i % 4 == 0) {
			for(int j = 0; j <= swidth * num_row; ++j) {
				if(j % 8 == 0) {
					printf("|");
				}
				else {
					printf("_");
				}
			}
		}	
		else {
			for(int j = 0; j <= swidth * num_row; ++j) {
				if(j % 8 == 0) {
					printf("|");
				}
				else if(board[j/8][i/4] == 1) {
					printf("%c", userP);
				}
				else if(board[j/8][i/4] == 0) {
					printf("%c", compP);
				}
				else {
					printf(" ");
				}

			}
		}
		printf("\n");
	}
	for(int i = 0; i <= num_row * swidth; ++i) {
		printf("-");
	}
	printf("\n");
}

bool isFull(int input, int num_col, int num_row, int board[num_col][num_row]) {
	if(board[input-1][0] >= 0) {
		return true;
	}
	return false;
}

void getUserInput(int num_col, int num_row, int board[num_col][num_row]) {
	int input;
	while(1) {
		printf("Which column would you like to place your peice? ");
		scanf("%d", &input);
		if (input > num_col || input <= 0) {
		while((input = getchar()) != '\n' && input != EOF );
		if(input > num_row || input <= 0) {
			printf("Invalid input, please choose again\n");
		}
	}
		else if(isFull(input, num_col, num_row, board)) {
			printf("That column is full, please pick a different one\n");
		}
		else if(input <= num_col && input > 0) {
			break;
		}
		
		else {
			break;
		}
	}
	//find where piece should be placed
	--input;
	myinsert(num_col, num_row, 1, input, board);
	/*
	for(int r = 0; r < num_row; ++r) {
		if(board[input][r] == -2) {
			board[input][r] = 1;
			if(r > 0) {
				board[input][r-1] = -2;
				break;
			}
		break;	
		}
	}*/
}
// checkIfGameOver returns true for game over and false otherise
bool checkIfGameOver(int num_row, int num_col, int b[num_row][num_col]) {
	//check vertical
	for(int j = 0; j < num_col; ++j) {
		for(int i = 0; i < num_row - 3; ++i) {
			if((b[i][j] == 0 || b[i][j] == 1) && (b[i][j] == b[i+1][j] && 
				b[i+1][j] == b[i+2][j] && b[i+2][j] == b[i+3][j])) {
				return true;
			}
		}

	}
	//check horizontal
	for(int i = 0; i < num_row; ++i) {
		for(int j = 0; j < num_col - 3; ++j) {
			if((b[i][j] == 0 || b[i][j] == 1) && (b[i][j] == b[i][j+1] &&
			b[i][j+1] == b[i][j+2] && b[i][j+2] == b[i][j+3])) {
				return true;
			}
		}
	}
	//check diagonal - top left to bottom right
	int c = 0;
	for(int j = 0; j < num_col - 3; j = c) {
		for(int i = 0; i < num_col - 3; ++i) {
			if((b[i][j] == 1 || b[i][j] == 0) && (b[i][j] == b[i+1][j+1] &&
			b[i+1][j+1] == b[i+2][j+2] && b[i+2][j+2] == b[i+3][j+3])) {
				return true;
			}
			++j;
		}
		++c;
	}
	c = 0;
	for(int i = 0; i < num_col - 3; i = c) {
		for(int j = 0; j < num_col - 3; ++j) {
			if((b[i][j] == 1 || b[i][j] == 0) && (b[i][j] == b[i+1][j+1] &&
			b[i+1][j+1] == b[i+2][j+2] && b[i+2][j+2] == b[i+3][j+3])) {
				return true;
			}
			++i;
		}
		++c;
	}
	c=7;
	// check diagonal - bottom left to top right
	for(int i = 7; i > 2; i = c) {
		for(int j = 0; j < num_col - 3; ++j) {
			if((b[i][j] == 1 || b[i][j] == 0) && (b[i][j] == b[i-1][j+1] &&
			b[i-1][j+1] == b[i-2][j+2] && b[i-2][j+2] == b[i-3][j+3])) {
				return true;
			}
			--i;
		}
		--c;
	}
	c=7;
	for(int j = 7; j > 2; j = c) {
		for(int i = 0; i < num_col - 3; ++i) {
			if((b[i][j] == 1 || b[i][j] == 0) && (b[i][j] == b[i-1][j+1] &&
			b[i-1][j+1] == b[i-2][j+2] && b[i-2][j+2] == b[i-3][j+3])) {
				return true;
			}
			--j;
		}
		--c;
	}

	return false;
}


// findPossibleWin returns index in board array of winning spot
// returns -1 if no win can be made
// first digit = column 
// second digit = row
// 0 being 0th column and 0th row
int findPossibleWin(int num_col, int num_row, int piece, 
					int b[num_col][num_row]) {
//horizontal
	for(int i = 0; i < num_row; ++i) {
		for(int j = 0; j < num_col - 3; ++j) {
				int m = 0;
				int saveSpot;
				if(b[j][i] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[j+s][i] == 0){
						break;
					}
					else if(-2 == b[j+s][i] && m == 0 && s == 3) {
						return ((j+s)*10) + i;
					}
					else if(-2 == b[j+s][i]) {
						saveSpot = ((j+s)*10) + i;
						++m;
					}
					else if(piece == b[j+s][i] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[j][i] == -2) {
				m = 1;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[j+s][i] == 0){
						break;
					}
					else if(-2 == b[j+s][i]) {
						saveSpot = ((j+s)*10) + i;
						++m;
					}
					else if(piece == b[j+s][i] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[j+s][i] && m == 0 && s == 3) {
						return ((j+s)*10) + i;
					}
				}

			}
		}
	}
	//vertical
	for(int i = 0; i < num_col; ++i) {
		for(int j = 7; j > 3; --j) {
			int m = 0;
				int saveSpot;
				if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(b[i][j+s] != piece) break;
					if(s == 3) return (i*10) + (j+s);
				}

			}
		}
	}
	//diagonal - top left to bottom right
	// bottom left triangular half
	int c = 0;
	for(int j = 0; j < num_row - 3; j = c) {
		for(int i = 0; i < num_col - 3; ++i) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10)+j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
				}
			}
			++j;
		}
		++c;
	}
	// top right triangular half
	c = 0;
	for(int i = 0; i < num_col - 3; i = c) {
		for(int j = 0; j < num_row - 3; ++j) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10)+j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
				}
			}
			++i;
		}
		++c;
	}
	// check diagonal - bottom left to top right
	c=7;
	for(int j = 7; j > 2; j = c) {
		for(int i = 0; i < num_col - 3; ++i) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10) + j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
				}
			}
			--j;
		}
		--c;
	}
	c=0;
	for(int i = 0; i < num_col - 3; i = c) {
		for(int j = 7; j > 2; --j) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10) + j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
				}
			}
			--i;
		}
		++c;
	}
	return -1;
}



// bestWinningStreak returns integer 
// first digit = column 
// second digit = row
int bestWinningStreak(int num_col, int num_row, int piece, 
	int b[num_col][num_row]) {
	for(int s = 2; s >= 1; --s) {
	//horizontal
	for(int i = 0; i < num_row; ++i) {
		for(int j = 0; j < num_col - 3; ++j) {
				int m = s;
				int saveSpot;
				if(b[j][i] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 4-s) {
						break;
					}
					else if(b[j+s][i] == 0){
						break;
					}
					else if(-2 == b[j+s][i] && m == 0 && s == 3) {
						return ((j+s)*10) + i;
					}
					else if(-2 == b[j+s][i]) {
						saveSpot = ((j+s)*10) + i;
						++m;
					}
					else if(piece == b[j+s][i] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[j][i] == -2) {
				m = 1;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[j+s][i] == 0){
						break;
					}
					else if(-2 == b[j+s][i]) {
						saveSpot = ((j+s)*10) + i;
						++m;
					}
					else if(piece == b[j+s][i] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[j+s][i] && m == 0 && s == 3) {
						return ((j+s)*10) + i;
					}
				}

			}
		}
	}

	//vertical
	for(int i = 0; i < num_col; ++i) {
		for(int j = 7; j > 3; --j) {
			int m = 0;
				int saveSpot;
				if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(b[i][j+s] != piece) break;
					if(s == 3) return (i*10) + (j+s);
				}

			}
		}
	}
	//diagonal - top left to bottom right
	// bottom left triangular half
	int c = 0;
	for(int j = 0; j < num_row - 3; j = c) {
		for(int i = 0; i < num_col - 3; ++i) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10)+j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
				}
			}
			++j;
		}
		++c;
	}
	// top right triangular half
	c = 0;
	for(int i = 0; i < num_col - 3; i = c) {
		for(int j = 0; j < num_row - 3; ++j) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10)+j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j+s] == 0 || b[i+s][j+s] == -1){
						break;
					}
					else if(-2 == b[i+s][j+s]) {
						saveSpot = ((i+s)*10) + j+s;
						++m;
					}
					else if(piece == b[i+s][j+s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j+s] && m == 0 && s == 3) {
						return ((i+s)*10) + j+s;
					}
				}
			}
			++i;
		}
		++c;
	}
	// check diagonal - bottom left to top right
	c=7;
	for(int j = 7; j > 2; j = c) {
		for(int i = 0; i < num_col - 3; ++i) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10) + j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
				}
			}
			--j;
		}
		--c;
	}
	c=0;
	for(int i = 0; i < num_col - 3; i = c) {
		for(int j = 7; j > 2; --j) {
			int m = 0;
			int saveSpot;
			if(b[i][j] == piece) {
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					
				}
			}
			if(b[i][j] == -2) {
				m = 1;
				saveSpot = (i*10) + j;
				for(int s = 1; s <= 3; ++s) {
					if(m > 1) {
						break;
					}
					else if(b[i+s][j-s] == 0 || b[i+s][j-s] == -1){
						break;
					}
					else if(-2 == b[i+s][j-s]) {
						saveSpot = ((i+s)*10) + j-s;
						++m;
					}
					else if(piece == b[i+s][j-s] && m == 1 && s == 3) {
						return saveSpot;
					}
					else if(-2 == b[i+s][j-s] && m == 0 && s == 3) {
						return ((i+s)*10) + j-s;
					}
				}
			}
			--i;
		}
		++c;
	}
}
	return -1;
}



void getCompTurn(int num_col, int num_row, int b[num_row][num_col]) {
	//check if a win can be made by computer
	int cWin = findPossibleWin(num_col,num_row,0,b);
	if(cWin != -1) {
		myinsert(num_col,num_row,0,cWin/10,b); //cWin/10 - since findPossibleWin function
		// returns two digit integer where first digit is colunm and second is row
		return;
	}
	//check if a win can be made by user, block
	int uWin = findPossibleWin(num_col,num_row,1,b);
	if(uWin != -1) {
		myinsert(num_col,num_row,0,uWin/10,b);
		return;
	}
	//find longest streak and add to that
	int cr = bestWinningStreak(num_col, num_row, 0, b);
	if(cr != -1) {
		myinsert(num_col,num_row,0,cr/10,b);
		return;
	}
	int randomNumber = rand() % 8;
	myinsert(num_col,num_row,0,randomNumber,b);
}


// 1 being user piece
// 0 being computer piece

int main(void) {
	int num_col = 8;
	int num_row = 8;
	int input;
	int board[num_col][num_row];
	printf("Connect Four! Lets play :)\n");
	bool game = true;
	//set board to empty
	// index 7 being bottom of board
	for(int i = 0; i < num_row; ++i) {
		for(int j = 0; j < num_col; ++j) {
			if(j == 7) { //set bottom row to -2 meaning it can accept piece
				board[i][j] = -2;
			}
			else {
				board[i][j] = -1; // -1 means there are places underneath
			}
		}
	}

	displayboard(num_col, num_row, board);
	while(game) {
		getUserInput(num_col, num_row, board);
		displayboard(num_col, num_row, board);
		if(checkIfGameOver(num_row, num_col, board)) {
			printf("YOU WIN!\n");
			return 0;
		}
		getCompTurn(num_col,num_row,board);
		displayboard(num_col, num_row, board);
		if(checkIfGameOver(num_row, num_col, board)) {
			printf("YOU LOSE\n");
			return 0;
		}
	}

	printf("\n");
	return 0;
}
