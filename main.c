#include <stdio.h>
#include "engine/terminal.h"

int main() {
	struct engine_terminal_size ts = engine_terminal_getSize();
	printf("Hello World, size %dx%d\n", ts.col, ts.row);
	return 0;
}
