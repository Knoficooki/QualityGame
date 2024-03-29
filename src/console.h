#ifndef CONSOLE_H
#define CONSOLE_H

#include <utils.h>

#if defined(WIN32)
#include <windows.h>
static CONSOLE_SCREEN_BUFFER_INFO csbi;
static int oldWidth = -1;
static int oldHeight = -1;
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
static struct winsize w;
#endif

static umax ConCHAR_Width = 80, ConCHAR_Height = 25;

enum OFFSETS {
	MID = -1
};

void checkResizeEvent();
void handle_resize(int);
umax consoleWidth();
umax consoleHeight();
void printML(const char*, int);
void printMultilineWithOffset(char*, int);
void printWithOffset(const char*, umax);
void setConsoleSize(int width, int height);
void getConsoleValues();

#endif //CONSOLE_H
