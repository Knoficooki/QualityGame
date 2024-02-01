#ifndef CONSOLE_H
#define CONSOLE_H

enum OFFSETS {
	MID = -1
};

void checkResizeEvent();
void handle_resize(int);
umax_t consoleWidth();
void printML(const char*, int);
void printMultilineWithOffset(char*, int);
void printWithOffset(const char*, umax_t);

#endif //CONSOLE_H