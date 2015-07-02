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
	wprintf(L"%c[%dm", ENGINE_TERMINAL_ESCAPE_BASE, attr);
}

void engine_terminal_clearScreen() {
	// wprintf(L"%c[2J", ENGINE_TERMINAL_ESCAPE_BASE);//c
	wprintf(L"%cc", ENGINE_TERMINAL_ESCAPE_BASE);//c
}

void engine_terminal_cursorPosition(struct engine_terminal_position position) {
	wprintf(L"%c[%d;%df", ENGINE_TERMINAL_ESCAPE_BASE, position.x, position.y);
}

void engine_terminal_showCursor() {
	wprintf(L"%c[25l", ENGINE_TERMINAL_ESCAPE_BASE);
}

void engine_terminal_hideCursor() {
	wprintf(L"%c[25h", ENGINE_TERMINAL_ESCAPE_BASE);
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

void engine_termianl_printCanvas(struct engine_terminal_canvas *canvas) {
	engine_terminal_style(ENGINE_TERMINAL_STYLE_RESET);
	engine_terminal_cursorPosition((struct engine_terminal_position) {0, 0});
	engine_terminal_clearScreen();

	for (unsigned char ih=0; ih < (*canvas).size.h; ih++) {
		for (unsigned char iw=0; iw < (*canvas).size.w; iw++) {
			unsigned short pos = ((*canvas).size.w * ih) + iw;
			wprintf(L"%lc", (*canvas).chaxels[pos].character);
		}
		// if (ih < (*canvas).size.h + 1) {
		// 	wprintf(L"\n");
		// }
	}

	engine_terminal_cursorPosition((struct engine_terminal_position) {0, 0});
}
