#include "terminal.h"

struct engine_terminal_size engine_terminal_getSize() {
	static struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	static struct engine_terminal_size result;
	result.w = w.ws_col;
	result.h = w.ws_row;
	return result;
}

//#include <signal.h>
//signal(SIGWINCH, SIG_IGN);

void engine_terminal_style(unsigned char attr) {
	printf("%c[%dm", ENGINE_TERMINAL_ESCAPE_BASE, attr);
}

void engine_terminal_clearScreen() {
	printf("%cc", ENGINE_TERMINAL_ESCAPE_BASE);
}

void engine_terminal_cursorPosition(struct engine_terminal_position position) {
	printf("%c[%d;%dH", ENGINE_TERMINAL_ESCAPE_BASE, position.x, position.y);
}

void engine_terminal_showCursor() {
	printf("%c[25l", ENGINE_TERMINAL_ESCAPE_BASE);
}

void engine_terminal_hideCursor() {
	printf("%c[25h", ENGINE_TERMINAL_ESCAPE_BASE);
}

struct engine_terminal_canvas *engine_terminal_getNewCanvas(
	struct engine_terminal_size size,
	struct engine_terminal_position position,
	bool bgtrans, bool fgtrans,
	engine_terminal_color bgcolor,
	engine_terminal_color fgcolor,
	wchar_t character,
	bool bold, bool underline, bool blink
) {
	unsigned short numOfChax = size.w * size.h;

	struct engine_terminal_chaxel *chaxels =
		malloc(sizeof(struct engine_terminal_chaxel) * numOfChax);

	for (unsigned short i = 0; i < numOfChax; i++) {
		chaxels[i] = (struct engine_terminal_chaxel) {
			bgtrans, fgtrans,
			bgcolor, fgcolor,
			character,
			bold, underline, blink
		};
	}

	struct engine_terminal_canvas *canvas =
		malloc(sizeof(struct engine_terminal_canvas));

	*canvas = (struct engine_terminal_canvas) {
		size, position, chaxels
	};
	return canvas;
}

void engine_terminal_freeCanvas(struct engine_terminal_canvas *canvas) {
	free((*canvas).chaxels);
	free(canvas);
}
