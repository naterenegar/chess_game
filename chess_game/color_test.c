#include <ncurses.h>

int main(void) {
	int i, j;
	initscr();
	start_color();

	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_YELLOW);
	for(i = 0; i < 8; i++) { 
			for(j = 0; j < 8; j++) {
			attron(COLOR_PAIR(i % 2 + 1));
			move((i*3), j*3);
			printw("---");	
			move((i*3)+1, j*3);
			printw("---");
			move((i*3)+2, j*3);
			printw("---");
		}
	}

	getch();

	endwin();
	
	return 0;
}
