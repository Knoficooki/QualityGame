#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include <utils.h>

#define CONCATENATE(arg1, agr2) CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2

#define LVL_NAMESTRC_VER(major, minor) CONCATENATE(QG_LEVEL_##major, _##minor)
#define LVL_TNAME_VER(major, minor) CONCATENATE(CONCATENATE(level_v##major,m##minor), _t)

static const char* sceneFilePathStructure = "./scenes/%s.qgscn";

typedef struct LVL_NAMESTRC_VER(0, 1) {
	const char* title;
	const char* info;
	scene_t* scenes;
	u8 nScenes;
} LVL_TNAME_VER(0, 1), level_t;

typedef struct LEVEL_VERSION {
	u16 major;
	u16 minor;
} verdesc;

struct LEVEL_FILE_HEADER {
	char magic[4];
	verdesc ver;
};

level_t *loadLevel(const char*);

void play_level();

#endif
