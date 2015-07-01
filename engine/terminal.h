#ifndef ENGINE_TERMINAL_H
#define ENGINE_TERMINAL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

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

struct engine_terminal_size {
	unsigned short col;
	unsigned short row;
};

struct engine_terminal_size engine_terminal_getSize();
void engine_terminal_style(int attr);
void engine_terminal_clearScreen();
void engine_terminal_cursorPosition(int x, int y);
void engine_terminal_showCursor();
void engine_terminal_hideCursor();

#endif
