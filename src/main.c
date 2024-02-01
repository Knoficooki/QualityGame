//   ______                                ______
//  /|     \              ||     ||       /|     \
//  ||     |        ____  || || ||||      ||        ____   ___  __   ___
//  ||  _  | ||  | /|  |\ ||     ||       ||   __  /|  |\ ||  \/  | /|__\
//  ||  \\ | ||  | ||  || || ||  || \\  / ||     | ||  || ||  ||  | ||  
//  \|___\\/ \|__/ \|__|| \| \|  \|  \\/  \|_____/ \|__|| ||  ||  | \|__/
//  ______\\_________________________//__________________________________
//  ___Lloyd Bush und Robin Ulke____//_______(c) 2024 MIT-License________                                       
//		    ___                        _         
//		  /  __ \  ___ _ _ ___ ___ ___|_|___ ___ 
//		 / /      |___| | | -_|  _|_ -| | . |   |
//		 \ \ ___       \_/|___|_| |___| |___|_|_|
//		  \ ___ / ___Jann Hoffmann____|_|_(c) 2024 GNU v2.0
//
// This C-Version was written by Jann Hoffmann.
// This version is published on github.com: https://github/Knoficooki/QualityGame.
// This product is licenced under the GNU v2.0 Licence.

unsigned long long ConCharWidth = 80;


const char* title = 
"______                                ______                       \n\
/|     \\              ||     ||       /|     \\                       \n\
||     |        ____  || || ||||      ||        ____   ___  __   ___ \n\
||  _  | ||  | /|  |\\ ||     ||       ||   __  /|  |\\ ||  \\/  | /|__\\\n\
||  \\\\ | ||  | ||  || || ||  || \\\\  / ||     | ||  || ||  ||  | ||   \n\
\\|___\\\\/ \\|__/ \\|__|| \\| \\|  \\|  \\\\/  \\|_____/ \\|__|| ||  ||  | \\|__/\n\
______\\\\_________________________//__________________________________\n\
___Lloyd Bush und Robin Ulke____//_______(c) 2024 MIT-License________\n\0";

const char* c_version_title = 
"\
   ___                        _                   \n\
 /  __ \\  ___ _ _ ___ ___ ___|_|___ ___           \n\
/ /      |___| | | -_|  _|_ -| | . |   |          \n\
\\ \\ ___       \\_/|___|_| |___| |___|_|_|          \n\
 \\ ___ / ___Jann Hoffmann____|_|_(c) 2024 GNU v2.0\n\
";

#if defined(WIN32)
#include <windows.h>

CONSOLE_SCREEN_BUFFER_INFO csbi;
int oldWidth = -1;
int oldHeight = -1;

#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#endif

#include <stdio.h>
#include <utils.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <conup/conup.h>
#include "console.h"

const conmod_t mainTitleColor = { BOLD, {51,204,255}, {3,3,3} };
const conmod_t subTitleColor = { RESET, {255, 153, 0}, {3,3,3} };
const conmod_t contxt = { RESET, {245,245,245}, {3,3,3} };

void printWithOffset(const char *str, umax_t offset) {
	switch (offset) {
	case MID: 
		offset = (ConCharWidth - stringWidth(str)) / 2;	
		break;
	default:
		break;
	} 
	for (int i = 0; i < offset; i++) {
            printf(" ");  // Print spaces for offset
	}
	printf("%s", str);
}

void printMultilineWithOffset(char *text, int offset) {
	// Split the multiline string into lines
	char *multilineStr = strdup(text);
	char *token = strtok(multilineStr, "\n\0");
	while (token != NULL) {
	// Print each line with the specified offset
		printWithOffset(token, offset);
		printf("\n");  // Move to the next line
		token = strtok(NULL, "\n\0");
	}
	free(multilineStr);
}

void printML(const char *str, int offset) {
	printMultilineWithOffset((char*)str, offset);
}

umax_t consoleWidth() {
#ifndef WIN32
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
#else
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return col;
#endif
}


void handle_resize(int sig) {
	system("clear");
	ConCharWidth = consoleWidth();
}

void checkResizeEvent() {
	int newWidth = consoleWidth();
	if (newWidth != oldWidth) {
		handle_resize(0);
		oldWidth = newWidth;
	}
}

int main() {
	ConCharWidth = consoleWidth();

#ifndef WIN32
	signal(SIGWINCH, handle_resize);
#endif

	system("clear");
	apply(NULL, &mainTitleColor);
	printML(title, MID);
	apply(NULL, &subTitleColor);
	printML(c_version_title, MID);
	apply(NULL, &contxt);
	printf("\n");
	
	
	
	return 0;
}

