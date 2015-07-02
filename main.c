#include <stdio.h>
#include <locale.h>
#include "engine/terminal.h"

int main() {
	setlocale(LC_CTYPE, "");
	// struct engine_terminal_size ts = engine_terminal_getSize();

	// engine_terminal_clearScreen();
	// printf("1\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");
	// engine_terminal_clearScreen();
	// printf("2\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");
	// engine_terminal_clearScreen();
	// printf("3\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");
	// engine_terminal_clearScreen();
	// printf("4\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");

	// engine_terminal_style(ENGINE_TERMINAL_STYLE_RESET);

	struct engine_terminal_canvas *canvas = engine_terminal_getNewCanvas(
		(struct engine_terminal_size) {10, 10},
		(struct engine_terminal_position) {0, 0},
		false, false,
		ENGINE_TERMINAL_COLOR_WHITE, ENGINE_TERMINAL_COLOR_BLACK,
		L'ą', false, false, false
	);

	wprintf(L"%lc", (*canvas).chaxels[0].character);

	engine_terminal_freeCanvas(canvas);

	return 0;
}
