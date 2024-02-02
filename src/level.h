#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include <type.h>

typedef struct QG_LEVEL {
	scene_t* scenes;
	u8 nScenes;
} level_t;

void play_level();

#endif
