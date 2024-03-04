#ifndef UTILS_H
#define UTILS_H

#ifndef NO_STD_TYPES
#	if __has_include(<types.h>)
#		include <types.h>
#	else

#if __has_include(<stdint.h>)
#	include <stdint.h>
#else
/* Exact integral types.  */

/* Signed.  */

#ifndef __int8_t_defined
# define __int8_t_defined
typedef signed char		int8_t;
typedef signed short int	int16_t;
typedef signed int		int32_t;
# if __WORDSIZE == 64
typedef long int		int64_t;
# else
__extension__
typedef long long int		int64_t;
# endif
#endif

/* Unsigned.  */
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
#ifndef __uint32_t_defined
typedef unsigned int		uint32_t;
# define __uint32_t_defined
#endif
#if __WORDSIZE == 64
typedef unsigned long int	uint64_t;
#else
__extension__
typedef unsigned long long int	uint64_t;
#endif


/* Small types.  */

/* Signed.  */
typedef signed char		int_least8_t;
typedef short int		int_least16_t;
typedef int			int_least32_t;
#if __WORDSIZE == 64
typedef long int		int_least64_t;
#else
__extension__
typedef long long int		int_least64_t;
#endif

/* Unsigned.  */
typedef unsigned char		uint_least8_t;
typedef unsigned short int	uint_least16_t;
typedef unsigned int		uint_least32_t;
#if __WORDSIZE == 64
typedef unsigned long int	uint_least64_t;
#else
__extension__
typedef unsigned long long int	uint_least64_t;
#endif


/* Fast types.  */

/* Signed.  */
typedef signed char		int_fast8_t;
#if __WORDSIZE == 64
typedef long int		int_fast16_t;
typedef long int		int_fast32_t;
typedef long int		int_fast64_t;
#else
typedef int			int_fast16_t;
typedef int			int_fast32_t;
__extension__
typedef long long int		int_fast64_t;
#endif

/* Unsigned.  */
typedef unsigned char		uint_fast8_t;
#if __WORDSIZE == 64
typedef unsigned long int	uint_fast16_t;
typedef unsigned long int	uint_fast32_t;
typedef unsigned long int	uint_fast64_t;
#else
typedef unsigned int		uint_fast16_t;
typedef unsigned int		uint_fast32_t;
__extension__
typedef unsigned long long int	uint_fast64_t;
#endif


/* Types for `void *' pointers.  */
#if __WORDSIZE == 64
# ifndef __intptr_t_defined
typedef long int		intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned long int	uintptr_t;
#else
# ifndef __intptr_t_defined
typedef int			intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned int		uintptr_t;
#endif


/* Largest integral types.  */
#if __WORDSIZE == 64
typedef long int		intmax_t;
typedef unsigned long int	uintmax_t;
#else
__extension__
typedef long long int		intmax_t;
__extension__
typedef unsigned long long int	uintmax_t;
#endif

#endif

// signed
typedef int8_t		s8;
typedef int16_t		s16;
typedef int32_t		s32;
// unsigned
typedef uint8_t		u8;
typedef uint16_t 	u16;
typedef uint32_t	u32;

#define MAX_SBIT_TYPE s32
#define MAX_UBIT_TYPE u32

// 64 bit types
#if __WORDSIZE == 64
typedef int64_t		s64;
typedef uint64_t	u64;
#define MAX_SBIT_TYPE s64
#define MAX_UBIT_TYPE u64
#endif

#ifndef _MAX_TYPES_DEFINED
#define _MAX_TYPES_DEFINED
typedef MAX_SBIT_TYPE smax;
typedef MAX_UBIT_TYPE umax;
#endif // _MAX_TYPES_DEFINED

typedef umax count_t;

#	endif
#endif // NO_STD_TYPES

umax stringWidth(const char*);
char* strtrm(char*);
#ifndef NO_FILE_UTILS
#include <stdio.h>
char* fgetstr(FILE*);
#endif

#ifdef UTILS_H_IMPLEMENTATION

#ifndef NO_STRING_UTILS
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

umax stringWidth(const char* str) {
	umax i = 0;
	while (str[i] != '\0' || str[i] == '\n') 
	{
		++i;
	}
	return i;
}

char *_ltrim_str_inp(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *_rtrim_str_inp(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *strtrim_inplace(char *s)
{
    return _rtrim_str_inp(_ltrim_str_inp(s));
}

// return a new string of type char* that contains the trimed version of s, manuall free required
char *strtrm(char *s) {
	if(s == NULL) {
		return s;
	}
	char* str = malloc(strlen(s)+1);
	if(str == NULL) {
		return NULL;
	}
	strcpy(str, s);
	char* tmp = strtrim_inplace(str);
	if(tmp == NULL) {
		return s;
	}
	char* res = malloc(strlen(tmp) + 1);
	if(res == NULL) {
		return NULL;
	}
	strcpy(res, tmp);
	res[strlen(tmp)] = '\0';
	free(str);
	tmp = NULL; // tmp is a substring of str, which is a copy of s, thats why i free str but not tmp
	if(res == NULL) {
		return NULL;
	}
	return res;
}

void strcat_s(char** str, const char* str2) {
	*str = realloc(*str, strlen(*str) + strlen(str2) + 1);
	strcat(*str, str2);
}



#define BUFFER_TEXT_LEN 255
// retreves a string from a file. the string has to have the format "{string}" 
// The file position pointer should point to the first character of the string in the file
char* parseStringFromFormat(const char* s, const char* delim) {
	char* buffer = strdup(s);
	/* states:
	 * StringClosed = 0
	 * StringOpen = 1
	*/
	char state = 0;
	umax i = 0;
	char* token = strtok(buffer, delim);
	char* res = strdup("");
	while() {
		
		*tmp++ = (char)fgetc(file);
		if(*tmp == '\"') {
			*tmp = '\0';
			break;
		}
		++i;
	}
	// string of iterator's size
	// copy only the sting
	// set the char after the string end to the NULL-Terminator ('\0')
	// deallocate the buffer
	
	char* str = malloc(i + 1);
	strcpy(str, buffer);
	str[i] = 0;
	free(buffer);

	return str;
}


#endif // NO_STRING_UTILS
#endif // UTILS_H_IMPLEMENTATION

#endif // UTILS_H
