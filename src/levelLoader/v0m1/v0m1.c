#include <stdio.h>

#ifdef _MSC_VER
#include <windirent.h>
#else
#include <dirent.h>
#endif

#include <utils.h>
#include <string.h>
#include <stdlib.h>
#include <inisg.h>

#include "v0m1.h"

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

level_t *loadlvl_v0m1(FILE* lvlfile) {
	/* read file contents*/
	
	umax pos = ftell(lvlfile);
	char* buffer = NULL;
	
	if (f)
	{
		fseek (lvlfile, 0, SEEK_END);
		length = ftell(lvlfile) - pos;
		fseek (lvlfile, pos, SEEK_SET);
		buffer = malloc(length * sizeof(char));
		if (buffer) {
			fread(buffer, 1, length, lvlfile);
		}
	}

	ini_t* ini = inisg_parse(buffer);
	free(buffer);

	level_t* lvl = malloc(sizeof(level_t));

	iniSection_t* sec = inisg_GetSection(ini, "empty");
	if(!sec) return NULL;
	lvl->title = strdup(inisg_GetEntry(sec, "title")->value);
	lvl->info = (inisg_GetEntry(sec, "info")->value);
	lvl->nScenes = 0;
	lvl->scenes = NULL;
	if(!lvl->title || !lvl->info) return NULL;


	sec = inisg_GetSection(ini, "scenes");
	if(!sec) return NULL;
	lvl->scenes = malloc(sizeof(scene_t));
	
	iniEntry_t* entry = NULL;
	inisg_ForEachEntry(entry, sec) {
		++lvl->nScenes;
		lvl->scenes = realloc(lvl->nScenes);
		FILE* f = fopen(entry->value, "r");
		loadScene(f, 0,lvl->scenes + lvl->nSections - 1);
		fclose(f);
	}
}
