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

	struct engine_terminal_size ts = engine_terminal_getSize();

	for (unsigned char ih=0; ih < (*canvas).size.h; ih++) {
		if (ih >= ts.h) {
			continue;
		}
		for (unsigned char iw=0; iw < (*canvas).size.w; iw++) {
			if (iw >= ts.w) {
				continue;
			}
			unsigned short pos = ((*canvas).size.w * ih) + iw;

			if ((*canvas).chaxels[pos].bold) {
				engine_terminal_style(ENGINE_TERMINAL_STYLE_FOREGROUND + (*canvas).chaxels[pos].fgcolor);
			}
			if ((*canvas).chaxels[pos].underline) {
				engine_terminal_style(ENGINE_TERMINAL_STYLE_UNDERLINE);
			}
			if ((*canvas).chaxels[pos].blink) {
				engine_terminal_style(ENGINE_TERMINAL_STYLE_BLINK);
			}
			engine_terminal_style(ENGINE_TERMINAL_STYLE_FOREGROUND + (*canvas).chaxels[pos].fgcolor);
			engine_terminal_style(ENGINE_TERMINAL_STYLE_BACKGROUND + (*canvas).chaxels[pos].bgcolor);
			wprintf(L"%lc", (*canvas).chaxels[pos].character);
		}
		if ((*canvas).size.w < ts.w && ih < ts.h) {
			wprintf(L"\n");
		}
	}

	engine_terminal_cursorPosition((struct engine_terminal_position) {0, 0});
	engine_terminal_style(ENGINE_TERMINAL_STYLE_RESET);
}

void engine_termianl_applyCanvas(
	struct engine_terminal_canvas *source,
	struct engine_terminal_canvas *target,
	struct engine_terminal_position position,
	struct engine_terminal_size size,
	struct engine_terminal_position targetPosition
) {
	for (unsigned char ih=position.y; ih < size.h; ih++) {
		if (ih >= (*target).size.h + targetPosition.y) {
			continue;
		}
		for (unsigned char iw=position.x; iw < size.w; iw++) {
			if (iw >= (*target).size.w + targetPosition.x) {
				continue;
			}

			unsigned short sourcePos = ((*source).size.w * (ih - position.y)) + (iw - position.x);
			unsigned short targetPos =
				(*target).size.w * ((ih - position.y) + targetPosition.y)
				+ ((iw - position.x) + targetPosition.x);

			engine_terminal_color newfgcolor = (*target).chaxels[targetPos].fgcolor;
			if ((*source).chaxels[sourcePos].fgcolor != ENGINE_TERMINAL_COLOR_TRANSPARENT) {
				newfgcolor = (*source).chaxels[sourcePos].fgcolor;
			}

			engine_terminal_color newbgcolor = (*target).chaxels[targetPos].bgcolor;
			if ((*source).chaxels[sourcePos].bgcolor != ENGINE_TERMINAL_COLOR_TRANSPARENT) {
				newbgcolor = (*source).chaxels[sourcePos].bgcolor;
			}

			wchar_t newCharacter = (*target).chaxels[targetPos].character;
			if ((*source).chaxels[sourcePos].character != L'\0') {
				newCharacter = (*source).chaxels[sourcePos].character;
			}

			(*target).chaxels[targetPos] = (struct engine_terminal_chaxel) {
				newbgcolor,
				newfgcolor,
				newCharacter,
				(*source).chaxels[sourcePos].bold,
				(*source).chaxels[sourcePos].underline,
				(*source).chaxels[sourcePos].blink
			};
		}
	}
}



