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

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

#endif // UTILS_H
