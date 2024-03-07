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

/*		   'Q G L M ' 
		    | | | |  */
#define LVL_MAGIC 0x51474c4d

#define MAX_LVL_MAJOR 1
#define MAX_LVL_MINOR 1

#if PROJECT_VERSION_MAJOR != MAX_LVL_MAJOR
#	error Project does not contain a equivalent level loader for this version
#endif

typedef LVL_TNAME_VER(MAX_LVL_MAJOR, MAX_LVL_MINOR), level_t;


struct LEVEL_FILE_HEADER {
	uint32_t  magic;
	struct { uint8_t major, minor; } ver;
};

static struct LEVEL_FILE_HEADER LVL_HEADER = { LVL_MAGIC, { PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR } };

level_t *loadLevel(const char*);

void play_level();

#endif
