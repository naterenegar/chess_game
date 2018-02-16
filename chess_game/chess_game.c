#include <ncurses.h>

#define W_FIRST 1
#define Y_FIRST 2

char p1_r1[8] = {'r', 'h', 'b', 'k', 'q', 'b', 'h', 'r'};
char p1_ps[8] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};	 
char p2_r1[8] = {'r', 'h', 'b', 'k', 'q', 'b', 'h', 'r'};
char p2_ps[8] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};	 

int pos_p1[2][16];
int pos_p2[2][16];

int row, col;
int m_row, m_col;

void makeMove(int player){
	init_pair(3, COLOR_BLUE, COLOR_WHITE);
	attron(COLOR_PAIR(3));
	printw("dick");
}

void changeState(int *s){
	if(*s == W_FIRST) {
		*s = Y_FIRST;	
	} else {
		*s = W_FIRST;
	}
}

int main(void) {
	int i, j, state = W_FIRST, *s = &state, row, col;

	initscr();
	raw();
	start_color();
	
	getmaxyx(stdscr, row, col);
	m_row = row/2;
	m_col = col/2;

	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_YELLOW);

	
	attron(COLOR_PAIR(0)); 
	for(i = 8; i > 0; i--) {
		move((i*3) + m_row - 14, m_col - 27);
		printw("%d", i);	
	}

	for(i = 65; i < 73; i++){
		move(m_row + 13, (i-65)*6 + (m_col - 21));
		printw("%c", i);	
	}
	
	for(i = 0; i < 8; i++) { 	
		for(j = 0; j < 8; j++) {
			attron(COLOR_PAIR(state));
			changeState(s);
			move((i*3) + (row/2 -12), j*6 + (col/2 - 24));
			printw("      ");
			move(((i*3)+1) + (row/2 -12), j*6 + (col/2 - 24));
			if(i == 0) {
				printw("  %c%d  ", p1_r1[j], 1);
				getyx(stdscr, pos_p1[0][j], pos_p2[1][j]);
			} else if(i == 1) {
				printw("  %c%d  ", p1_ps[j], 1);
				getyx(stdscr, pos_p1[0][8+j], pos_p1[1][8+j]);
			} else if(i == 6) {
				printw("  %c%d  ", p2_ps[j], 2);
				getyx(stdscr, pos_p2[0][8+j], pos_p2[1][8+j]);
			} else if(i == 7) {
				printw("  %c%d  ", p2_r1[j], 2);
				getyx(stdscr, pos_p2[0][j], pos_p2[1][j]);
			} else {
				printw("      ");
			}
			move((i*3)+2 + (row/2 -12), j*6 + (col/2 - 24));
			printw("      ");
		}
		changeState(s);
	}
	getch();

	endwin();
	
	return 0;
}
