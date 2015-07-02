#ifndef ENGINE_TERMINAL_H
#define ENGINE_TERMINAL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <wchar.h>
#include <locale.h>

#define ENGINE_TERMINAL_ESCAPE_BASE 0x1B

#define ENGINE_TERMINAL_FUNCT_CLEAR 'J'
#define ENGINE_TERMINAL_FUNCT_POSITION 'H'

#define ENGINE_TERMINAL_STYLE_RESET 0
#define ENGINE_TERMINAL_STYLE_BOLD 1
#define ENGINE_TERMINAL_STYLE_UNDERLINE 4
#define ENGINE_TERMINAL_STYLE_BLINK 5
#define ENGINE_TERMINAL_STYLE_REVERSE 7
#define ENGINE_TERMINAL_STYLE_FOREGROUND 30
#define ENGINE_TERMINAL_STYLE_BACKGROUND 40
#define ENGINE_TERMINAL_STYLE_REVERSE2 50

#define ENGINE_TERMINAL_COLOR_BLACK 0
#define ENGINE_TERMINAL_COLOR_RED 1
#define ENGINE_TERMINAL_COLOR_GREEN 2
#define ENGINE_TERMINAL_COLOR_YELLOW 3
#define ENGINE_TERMINAL_COLOR_BLUE 4
#define ENGINE_TERMINAL_COLOR_MAGENTA 5
#define ENGINE_TERMINAL_COLOR_CYAN 6
#define	ENGINE_TERMINAL_COLOR_WHITE 7
#define	ENGINE_TERMINAL_COLOR_DEFAULT 9
#define	ENGINE_TERMINAL_COLOR_TRANSPARENT 99

typedef unsigned short engine_terminal_coord;
typedef unsigned short engine_terminal_color;

struct engine_terminal_size {
	engine_terminal_coord w;
	engine_terminal_coord h;
};

struct engine_terminal_position {
	engine_terminal_coord x;
	engine_terminal_coord y;
};

struct engine_terminal_chaxel {
	engine_terminal_color bgcolor, fgcolor;
	wchar_t character;
	bool bold, underline, blink;
};

struct engine_terminal_canvas {
	struct engine_terminal_size size;
	struct engine_terminal_position position;
	struct engine_terminal_chaxel *chaxels;
};

struct engine_terminal_size engine_terminal_getSize();
void engine_terminal_style(unsigned char attr);
void engine_terminal_clearScreen();
void engine_terminal_cursorPosition(struct engine_terminal_position position);
void engine_terminal_showCursor();
void engine_terminal_hideCursor();

struct engine_terminal_canvas *engine_terminal_getNewCanvas(
	struct engine_terminal_size size,
	struct engine_terminal_position position,
	engine_terminal_color bgcolor,
	engine_terminal_color fgcolor,
	wchar_t character,
	bool bold, bool underline, bool blink
);

void engine_terminal_freeCanvas(struct engine_terminal_canvas *canvas);
void engine_termianl_printCanvas(struct engine_terminal_canvas *canvas);
void engine_termianl_applyCanvas(
	struct engine_terminal_canvas *source,
	struct engine_terminal_canvas *target,
	struct engine_terminal_position position,
	struct engine_terminal_size size,
	struct engine_terminal_position targetPosition
);

#endif
