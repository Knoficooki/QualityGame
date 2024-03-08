#ifndef V0M1_LOADER_DEFINED
#define V0M1_LOADER_DEFINED

#include <utils.h>
#include "level.h"

typedef struct LVL_NAMESTRC_VER(0,1) {
	const char* title;
	const char* info;
	scene_t* scenes;
	u8 nScenes;
} LVL_TNAME_VER(0,1);

/*
 * lvl_v0m1 structure:
 * 
 * string title = title;
 * string info = info;
 *
 * [ scenes ]
 * string scene_num[] = filestring;
 *  
 * 
*/

level_t *loadlvl_v0m1(FILE* lvlfile);

#endif /* V0M1_LOADER_DEFINED */
