#pragma once

#ifndef CONUP_HPP
#define CONUP_HPP

#include <stdio.h>
#include <stdint.h>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define INVERTED "\033[7m"
#define HIDDEN "\033[8m"

#define FOREGROUND "38"
#define BACKGROUND "48"

typedef struct {
	uint8_t r, g, b;
} concolor_t;

typedef struct CONUP_CONSOLE_MODIFIER {
	const char* effect;
	concolor_t fg;
	concolor_t bg;
} conmod_t;

#ifdef __cplusplus
#include <string>
#include <iostream>

class conmod {
	const char* effect;
	struct {
		u8 r;
		u8 g;
		u8 b;
	} foreground, fg;
	struct {
		u8 r;
		u8 g;
		u8 b;
	} background, bg;
public:
	conmod(u8 fgr = 245, u8 fgg = 245, u8 fgb = 245, u8 bgr = 3, u8 bgg = 3, u8 bgb = 3, std::string effect = RESET) {
		this->set(fgr, fgg, fgb, bgr, bgg, bgb, effect);
	}

	conmod(conmod_t mod) {
		*this = conmod(mod.fg.r, mod.fg.g, mod.fg.b, mod.bg.r, mod.bg.g, mod.bg.b);
		this->effect = mod.effect;
	}

	void set_bg(float r, float g, float b) {
		bg.r = (u8)(r * 256);
		bg.g = (u8)(g * 256);
		bg.b = (u8)(b * 256);
	}
	void set_bg(u8 r, u8 g, u8 b) {
		bg.r = r;
		bg.g = g;
		bg.b = b;
	}
	void set_fg(float r, float g, float b) {
		fg.r = (u8)(r * 256);
		fg.g = (u8)(g * 256);
		fg.b = (u8)(b * 256);
	}
	void set_fg(u8 r, u8 g, u8 b) {
		fg.r = r;
		fg.g = g;
		fg.b = b;
	}
	void set(u8 fgr, u8 fgg, u8 fgb, u8 bgr, u8 bgg, u8 bgb, std::string& effect) {
		fg.r = fgr;
		fg.g = fgg;
		fg.b = fgb;

		bg.r = bgr;
		bg.g = bgg;
		bg.b = bgb;

		this->effect = effect.c_str();
	}

	void set_effect(std::string& effect) {
		this->effect = effect.c_str();
	}

	friend std::ostream& operator<<(std::ostream& os, const conmod& mod);
	friend void apply(std::ostream of, conmod mod);
};
#endif // __cplusplus


const void apply_color(FILE* out,const char* type, const char r, const char g, const char b)
{
	if (out == NULL) {
		out = stdout;
	}
	fprintf(out,"\033[%s;2;%d;%d;%dm", type, r, g, b);
}

const void apply(FILE* out, conmod_t* modi)
{
	if (out == NULL) {
		out = stdout;
	}
	fprintf(out, modi->effect);
	fprintf(out, "\033[%s;2;%d;%d;%d;%s;2;%d;%d;%dm", FOREGROUND, modi->fg.r, modi->fg.g, modi->fg.b, BACKGROUND, modi->bg.r, modi->bg.g, modi->bg.b);
}

const void apply_effect(FILE* out, const char* effect) {
	if (out == NULL) {
		out = stdout;
	}
	fprintf(out, effect);
}

const void reset_color(FILE* out) {
	apply_effect(out, RESET);
}

#ifdef __cplusplus
#include <iostream>

std::ostream& operator<<(std::ostream& os, const conmod& mod) {
	std::string out = "\033["; 
	out += FOREGROUND;
	out += ";2;" + std::to_string(mod.fg.r) + ";" + std::to_string(mod.fg.g) + ";" + std::to_string(mod.fg.b) + ";" + 
		BACKGROUND + ";2;" + std::to_string(mod.bg.r) + ";" + std::to_string(mod.bg.g) + ";" + std::to_string(mod.bg.b) + "m";
	os << out;
	return os;
}

std::ostream& operator<<(std::ostream& os, const conmod_t& mod) {
	std::string out = "\033[";
	out += FOREGROUND;
	out += ";2;" + std::to_string(mod.fg.r) + ";" + std::to_string(mod.fg.g) + ";" + std::to_string(mod.fg.b) + ";" +
		BACKGROUND + ";2;" + std::to_string(mod.bg.r) + ";" + std::to_string(mod.bg.g) + ";" + std::to_string(mod.bg.b) + "m";
	os << out;
	return os;
}

void apply(std::ostream of, conmod mod) {
	std::string out = "\033[";
	out += FOREGROUND;
	out += ";2;" + std::to_string(mod.fg.r) + ";" + std::to_string(mod.fg.g) + ";" + std::to_string(mod.fg.b) + ";" +
		BACKGROUND + ";2;" + std::to_string(mod.bg.r) + ";" + std::to_string(mod.bg.g) + ";" + std::to_string(mod.bg.b) + "m";
	of << out;
}
#endif

#endif // CONUP_HPP