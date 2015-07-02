#include <stdio.h>
#include <locale.h>
#include "engine/terminal.h"

int main() {
	setlocale(LC_CTYPE, "");

	struct engine_terminal_size ts = engine_terminal_getSize();

	struct engine_terminal_canvas *trees = engine_terminal_getNewCanvas(
		(struct engine_terminal_size) {10, 10},
		(struct engine_terminal_position) {0, 0},
		false, false,
		ENGINE_TERMINAL_COLOR_BLACK, ENGINE_TERMINAL_COLOR_RED,
		L'T', false, false, false
	);

	struct engine_terminal_canvas *canvas = engine_terminal_getNewCanvas(
		(struct engine_terminal_size) {ts.w, ts.h},
		(struct engine_terminal_position) {0, 0},
		false, false,
		ENGINE_TERMINAL_COLOR_BLACK, ENGINE_TERMINAL_COLOR_GREEN,
		L'.', false, false, false
	);

	engine_termianl_applyCanvas(
		trees, canvas,
		(struct engine_terminal_position) {0, 0},
		(struct engine_terminal_size) {10, 10},
		(struct engine_terminal_position) {0, 0}
	);

	engine_termianl_printCanvas(canvas);

	engine_terminal_freeCanvas(canvas);

	getchar();

	engine_terminal_clearScreen();
	return 0;
}
