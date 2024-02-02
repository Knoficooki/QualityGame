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
#define MIN_COL_SIZE 80
unsigned long long ConCharHeight = 25;
#define MIN_ROW_SIZE 15


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

void getConsoleValues() {
#ifndef WIN32
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
#else
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
#endif
}

umax_t consoleWidth() {
#ifndef WIN32
	return w.ws_col;
#else
	int col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return col;
#endif
}
umax_t consoleHeight() {
#ifndef WIN32
	return w.ws_row;
#else
	int row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return row;
#endif
}


#ifdef _WIN32
void setConsoleSize(int width, int height) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD newSize;
	SMALL_RECT windowSize;

	newSize.X = width;
	newSize.Y = height;

	if (!SetConsoleScreenBufferSize(hOut, newSize)) {
		printf("SetConsoleScreenBufferSize failed\n");
		return;
	}

	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = newSize.X - 1;
	windowSize.Bottom = newSize.Y - 1;

	if (!SetConsoleWindowInfo(hOut, TRUE, &windowSize)) {
		printf("SetConsoleWindowInfo failed\n");
		return;
	}
}
#else
void setConsoleSize(int width, int height) {
	struct winsize ws;
	int fd;

	fd = open("/dev/tty", O_RDWR);
	if (fd < 0) {
		perror("open /dev/tty");
		return;
	}

	ws.ws_row = height;
	ws.ws_col = width;
	ws.ws_xpixel = 0;
	ws.ws_ypixel = 0;

	if (ioctl(fd, TIOCSWINSZ, &ws) < 0) {
		perror("ioctl TIOCSWINSZ");
		return;
	}

	close(fd);
}
#endif


void display();

void handle_resize(int sig) {
	getConsoleValues();
	ConCharWidth = consoleWidth();
	ConCharHeight = consoleHeight();
	if (ConCharWidth < MIN_COL_SIZE) {
		setConsoleSize(MIN_COL_SIZE, ConCharHeight);
	}
	if (ConCharHeight < MIN_ROW_SIZE) {
		setConsoleSize(ConCharWidth, MIN_ROW_SIZE);
	}
	display();
}

#ifdef WIN32 
void checkResizeEvent() {
	getConsoleValues();
	int newWidth = consoleWidth();
	int newHeight = consoleHeight();
	if (newWidth != oldWidth || newHeight != oldHeight) {
		handle_resize(0);
		oldWidth = newWidth;
		oldHeight = newHeight;
	}
}
#endif

int8_t gamestate = 0;

void handle_sigint() {
	gamestate = -1;
}

#ifdef WIN32
BOOL WINAPI ConsoleHandler(DWORD dwType)
{
	switch (dwType) {
	case CTRL_C_EVENT:
		handle_sigint();
		break;
	case CTRL_BREAK_EVENT:
		handle_sigint();
		break;
	default:
		printf("Event: %d\n", dwType);
	}
	return TRUE;
}
#endif

#undef ERROR

enum EXITS {
	SUCCESSFULL = 0,
	ERROR,
	SEGFAULT,
	ALLOCERR,
	NONE
};

enum GAMESTATE {
	OFF = -1,
	MENU,
	RUNNING,
	QUESTION
};

/*
* 
* Level and own stuff
* 
*/
#include "level.h"

level_t* activeLevel;

int main() {
	getConsoleValues();
	ConCharWidth = consoleWidth();
	ConCharHeight = consoleHeight();
#ifndef WIN32
	signal(SIGWINCH, handle_resize);
#else
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE)) {
		fprintf(stderr, "Unable to install handler!\n");
		return EXIT_FAILURE;
	}
#endif

	display();
	
	char *line = malloc(sizeof(char) * 256);
	memset(line, '\0', sizeof(char) * 256);

	while (gamestate > OFF) {
#ifdef WIN32
		checkResizeEvent();
#endif // WIN32
		if (gamestate > MENU) {
			play_level(activeLevel);
		}
		else
		{
			//
			// Checking for input
			//
			printf("> ");
			if (fgets(line, sizeof(line), stdin) == NULL) {
				gamestate = 0;
				continue;
			}
			char* tmp = trim(line);
			char* text = malloc(strlen(tmp) * sizeof(char));
			if (text == NULL) {
				return ALLOCERR;
			}
			strcpy(text, tmp);

			if (strcmp(text, "quit") == 0) {
				gamestate = OFF;
				continue;
			}

			if (strcmp(text, "start") == 0) {
				gamestate = RUNNING;
				continue;
			}
			//end
		}
	}

	apply(NULL, &mainTitleColor);
	printML("\nSaving...\n", MID);

	printML("Bye Bye", MID);
	apply(NULL, &contxt);
	
	return 0;
}

void display() {
	system("clear");
	apply(NULL, &mainTitleColor);
	printML(title, MID);
	apply(NULL, &subTitleColor);
	printML(c_version_title, MID);
	apply(NULL, &contxt);
	printf("\n");
}
