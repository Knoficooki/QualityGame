#include "level.h"
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

static char* LVL_MAGIC = "QGLM";

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

// QGLM
level_t *loadLevel(const char* filepath) {
	FILE* lvlfile = fopen(filepath, "rb");
	struct LEVEL_FILE_HEADER header;
	fread(&header, sizeof(header), 1, lvlfile);
	
	level_t *res = NULL;

	if(memcmp(header.magic, LVL_MAGIC, 4)) {
		printf("File does not contain a level");
	}

	if(header.ver.major == 0) {
		printf("Using level version 0.");
		if(header.ver.minor == 1) {
			printf("1");
			res = loadlvl_v0m1(lvlfile);
		}
		printf("\n");
	}
	else {
		printf("Version not supported!\n");
	}
	fclose(lvlfile);
	if(res == NULL) {
		printf("\nCould not load the level from: %s\n", filepath);
	}
	return res;
}

// return the path of the level file
void saveLevel(const level_t* lvl, const char* filepath) {
	FILE* file = fopen(filepath, "wb");
	struct LEVEL_FILE_HEADER header = 0;
	header.magic = LVL_MAGIC;
	header.ver.major = QG_VERSION_MAJOR;
	header.ver.minor = QG_VERSION_MINOR;

	fwrite(header, sizeof(struct LEVEL_FILE_HEADER), 1, file);
	
	ini_t* ini = NULL;
	inisg_createIni(&ini);
	iniSection_t* emptys = inisg_AddSection(ini, "empty");
	inisg_AddEntry(emptys, "title", lvl->title);
	inisg_AddEntry(emptys, "info", lvl->info);
	
	for(umax i = 0; i < lvl->nScenes; i++) {
		char key[4];
		sprintf(key, "%d", i);
		umax len = strlen(lvl->scenes[i].name) + strlen(sceneFilePathStructure) - 2;
		char* name = malloc(len + 1);
		sprintf(name, sceneFilePathStructure, lvl->scenes[i].name);

		inisg_AddEntry(scenes, key, name);
	}
	const char* inistr = inisg_print(ini);
	fprintf("\n%s\n", inistr);
	free(inistr);
	inisg_RemoveIni(ini);
	fclose(file);
}


void play_level(level_t* level) {
	printf("Level started!\n");
	u8 activeLevel = 0;
	while(activeLevel < level->nScenes) {
		play_scene(&(level->scenes[activeLevel]));
	}
}
