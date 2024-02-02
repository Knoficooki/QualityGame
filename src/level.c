#include "level.h"
#include <type.h>

void play_level(level_t* level) {
	printf("Level started!\n");
	u8 activeLevel = 0;
	while(activeLevel < level->nScenes) {
		play_scene(&(level->scenes[activeLevel]));
	}
}
