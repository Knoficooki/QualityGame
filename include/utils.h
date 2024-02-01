#ifndef UTILS_H
#define UTILS_H

typedef unsigned long long umax_t;

umax_t stringWidth(const char* str) {
	umax_t i = 0;
	while (str[i] != '\0' || str[i] == '\n') 
	{
		++i;
	}
	return i;
}

#endif // UTILS_H
