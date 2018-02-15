#include <stdio.h>
#include <ncurses.h>

#define BOARD_WIDTH 8
#define BOARD_LENGTH 8


void clearScreen(void) {
	printf("\033[2J");
}

void setBoard(char board[][8]){
	int i, j;
	for(i = 0; i < BOARD_LENGTH; i++) {
		for(j = 0; j < BOARD_WIDTH; j++) {
			if(i == 0 || i == 7) {
				switch(j) { 
					case 0: board[i][j] = 'R';
						break;
					case 1: board[i][j] = 'k'; 
						break;
					case 2: board[i][j] = 'B';
						break;
					case 3: board[i][j] = 'K';
						break;
					case 4: board[i][j] = 'Q';
						break;
					case 5: board[i][j] = 'B';
						break;
					case 6: board[i][j] = 'k';
						break;
					case 7: board[i][j] = 'R';
						break;
				 }
			} else if(i == 1 || i == 6) {
				board[i][j] = 'P';
			} else {
				board[i][j] = '-';
			}
		}
	}
}

void printBoard(char board[][8]) {
	int i, j;	
	for(i = 0; i <= BOARD_LENGTH*2; i++) {
		for(j = 0; j < BOARD_WIDTH; j++) {
			if(i % 2 == 0 && j != 7) {
				printw("-----");
			} else if(i % 2 == 0) {
				printw("--");
			} else {
				printw("| %c ", board[i/2][j]); 
			if(j == 7) {
					printw("| %c |", board[i/2][j]);
				}
			}
		}
		printw("\n");	
	}	
}

int main(void) {
	char board[BOARD_LENGTH][BOARD_WIDTH];
	
	initscr(); 
	cbreak();

	mvprintw(15,30,"I like dick");
	
	setBoard(board);	
	printBoard(board);	

	getch();	
	endwin();
	return 0;
}
