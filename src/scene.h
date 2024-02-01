#ifndef SCENE_H
#define SCENE_H

#include "character.h"
#include <type.h>
#include <stdio.h>
#include <cJSON/cJSON.h>

typedef struct QG_SCENE {
	const char* text;		// the question
	const char** answers;	// Answers to the text
	umax_t nAnswers;		// number of answers
	float* influence;		// the influence on your stats per answer
	umax_t iofcans;			// the index of the right anwser
	umax_t requiredlevel;	// minimum level to play this level
} scene_t;

u8 playScene(scene_t*);

u8 loadScene(FILE*, umax_t, scene_t*);
u8 saveScene(FILE*, umax_t, scene_t*);

scene_t* createScene(const char*, const char**, umax_t, float*, umax_t, umax_t);

#endif // SCENE_H
