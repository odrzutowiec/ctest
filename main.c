#include <stdio.h>
#include <locale.h>
#include "engine/terminal.h"

int main() {
	setlocale(LC_CTYPE, "");

	engine_terminal_style(ENGINE_TERMINAL_STYLE_RESET);
	engine_terminal_cursorPosition((struct engine_terminal_position) {0, 0});
	engine_terminal_clearScreen();

	wprintf(L"CZEŚĆ");

	engine_terminal_cursorPosition((struct engine_terminal_position) {2, 0});


	// struct engine_terminal_size ts = engine_terminal_getSize();

	struct engine_terminal_canvas *canvas = engine_terminal_getNewCanvas(
		(struct engine_terminal_size) {120, 10},
		(struct engine_terminal_position) {0, 0},
		false, false,
		ENGINE_TERMINAL_COLOR_WHITE, ENGINE_TERMINAL_COLOR_GREEN,
		L'.', false, false, false
	);

	engine_termianl_printCanvas(canvas);

	engine_terminal_freeCanvas(canvas);

	// engine_terminal_cursorPosition((struct engine_terminal_position) {0, 0});


	getchar();
	engine_terminal_clearScreen();
	return 0;
}
