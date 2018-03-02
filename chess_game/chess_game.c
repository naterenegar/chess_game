#include <ncurses.h>

#define W_FIRST 1
#define Y_FIRST 2
#define MAX_COMMAND_SIZE 88

char p1_r1[8] = {'r', 'h', 'b', 'k', 'q', 'b', 'h', 'r'};
char p1_ps[8] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};	 
char p2_r1[8] = {'r', 'h', 'b', 'k', 'q', 'b', 'h', 'r'};
char p2_ps[8] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};	 

char *pieces[8][8]=  {
{"r2", "h2", "b2", "k2", "q2", "b2", "h2", "r2"},
{"p2", "p2", "p2", "p2", "p2", "p2", "p2", "p2"},
{"--", "--", "--", "--", "--", "--", "--", "--"},
{"--", "--", "--", "--", "--", "--", "--", "--"},
{"--", "--", "--", "--", "--", "--", "--", "--"},
{"--", "--", "--", "--", "--", "--", "--", "--"},
{"p1", "p1", "p1", "p1", "p1", "p1", "p1", "p1"},
{"r1", "h1", "b1", "k1", "q1", "b1", "h1", "r1"}};

int pos_p1[2][16];
int pos_p2[2][16];

int parent_col, parent_row, parent_midy, parent_midx;

WINDOW *update_board();
WINDOW *update_command_box(char ch, const char *command);

void changeState(int *s){
	if(*s == W_FIRST) {
		*s = Y_FIRST;	
	} else {
		*s = W_FIRST;
	}
}


int main(void) {
	WINDOW *chess_board;
	WINDOW *command_box;
	int ch, command_size = 0;
	char command[MAX_COMMAND_SIZE] = {'\0'};	
	initscr();
	cbreak();
	start_color();
	keypad(stdscr, TRUE);
	refresh();

	getmaxyx(stdscr, parent_col, parent_row);
	parent_midy = parent_col / 2;
	parent_midx = parent_row / 2;
	chess_board = update_board();	
	while((ch = getch()) != KEY_F(1)) {
		if(command_size < MAX_COMMAND_SIZE) {
			command[command_size] = ch;
			command_size++;
			command_box = update_command_box(ch, command);
		} else {
			mvwprintw(command_box, 13, 1, "Command Overflow, press enter...                                                        ");                                                                    
			wmove(command_box, 13, 1);
			wrefresh(command_box);
		}
	}
	refresh();
	endwin();
	return 0;
}

WINDOW *update_board() {
	WINDOW *local_win;
	int i, j, k, state = W_FIRST, *s = &state, row, col, m_row, m_col;	
	local_win = newwin(31, 90, parent_midy - 16, parent_midx - 45);
	box(local_win, 0, 0);

	getmaxyx(local_win, row, col);
	m_row = row/2;
	m_col = col/2;

	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_YELLOW);
	init_pair(3, COLOR_BLUE, COLOR_BLACK); 

	mvwprintw(local_win, 0, 2, "Active game:");	
	for(i = 8; i > 0; i--) {
		mvwprintw(local_win, (i*3) + m_row -14, m_col - 27, "%d", i);	
	}
	
	for(i = 65; i < 73; i++){
		mvwprintw(local_win, m_row + 13, (i-65)*6 + (m_col - 21), "%c", i);	
	}
	
	for(i = 0; i < 8; i++) { 	
		for(j = 0; j < 8; j++) {
			wattron(local_win, COLOR_PAIR(state));
			changeState(s);
	
			mvwprintw(local_win, (i*3) + (row/2 -12), j*6 + (col/2 - 24), "      ");
	
			mvwprintw(local_win, ((i*3)+1) + (row/2 - 12), j*6 + (col/2 - 24), "  ");
			wprintw(local_win, "%s", pieces[i][j]);  
			wprintw(local_win, "  ");
	
			mvwprintw(local_win, (i*3)+2 + (row/2 -12), j*6 + (col/2 - 24), "      ");
		}
		changeState(s);
	}


	wrefresh(local_win);

	return local_win;
}

WINDOW *update_command_box(char ch, const char *command) {
	WINDOW *local_win;
	int row, col, m_row, m_col, i;

	local_win = newwin(15, 90, parent_midy + 15, parent_midx - 45);
	box(local_win, 0, 0);
	mvwprintw(local_win, 0, 1, "Command Box");
	mvwprintw(local_win, 13, 1, "%s", command);
	wrefresh(local_win);

	return local_win;	


}
