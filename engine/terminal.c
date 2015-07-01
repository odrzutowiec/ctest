#include "terminal.h"

struct engine_terminal_size engine_terminal_getSize() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	struct engine_terminal_size result;
	result.col = w.ws_col;
	result.row = w.ws_row;
	return result;
}

//#include <signal.h>
//signal(SIGWINCH, SIG_IGN);

void engine_terminal_style(int attr) {
	printf("%c[%dm", ENGINE_TERMINAL_ESCAPE_BASE, attr);
}

void engine_terminal_clearScreen() {
	printf("%cc", ENGINE_TERMINAL_ESCAPE_BASE);
}

void engine_terminal_cursorPosition(int x, int y) {
	printf("%c[%d;%dH", ENGINE_TERMINAL_ESCAPE_BASE, x, y);
}

void engine_terminal_showCursor() {
	printf("%c[25l", ENGINE_TERMINAL_ESCAPE_BASE);
}

void engine_terminal_hideCursor() {
	printf("%c[25h", ENGINE_TERMINAL_ESCAPE_BASE);
}
