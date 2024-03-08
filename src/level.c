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

#include <levelLoader/v0m1/v0m1.h>

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
	memcpy(header.magic, LVL_MAGIC, 4);
	header.ver.major = PROJECT_VERSION_MAJOR;
	header.ver.minor = PROJECT_VERSION_MINOR;

	fwrite(&header, sizeof(header), 1, file);
	

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
