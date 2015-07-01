#ifndef ENGINE_TERMINAL_H
#define ENGINE_TERMINAL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "terminal.h"

struct engine_terminal_size engine_terminal_getSize() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	struct engine_terminal_size result;
	result.col = w.ws_col;
	result.row = w.ws_row;
	return result;
}

//#include <signal.h>
//signal(SIGWINCH, SIG_IGN);

#endif
