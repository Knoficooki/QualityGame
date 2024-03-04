#include "console.h"

#if defined(WIN32)
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#endif

#include <stdio.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printWithOffset(const char *str, umax offset) {
	switch (offset) {
	case MID: 
		offset = (ConCHAR_Width - stringWidth(str)) / 2;	
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

umax consoleWidth() {
#ifndef WIN32
	ConCHAR_Width = w.ws_col;
	return w.ws_col;
#else
	ConCHAR_Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return ConCHAR_Width;
#endif
}
umax consoleHeight() {
#ifndef WIN32
	ConCHAR_Height = w.ws_row;
	return w.ws_row;
#else
	ConCHAR_Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return ConCHAR_Height;
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
	ConCHAR_Width = width;
	ConCHAR_Height = height;
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
