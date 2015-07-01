#include <stdio.h>
#include "engine/terminal.h"

int main() {
	// struct engine_terminal_size ts = engine_terminal_getSize();

	engine_terminal_clearScreen();
	printf("1\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");
	engine_terminal_clearScreen();
	printf("2\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");
	engine_terminal_clearScreen();
	printf("3\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");
	engine_terminal_clearScreen();
	printf("4\nasdasd\nasdasd\nasdasd\nasdasd\nasdasd");

	engine_terminal_style(ENGINE_TERMINAL_STYLE_RESET);
	return 0;
}
