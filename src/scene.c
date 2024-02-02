#include "scene.h"
#include <type.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>

u8 play_scene(scene_t* scene) {
	printf("Scene Output");
	return 0;
}

u8 loadScene(FILE* file, umax_t pos, scene_t* scene) 
{
	char* buffer = 0;
	long length;

	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);
		buffer = malloc(length);
		memset(buffer, 0, length);
		if (buffer)
		{
			fread(buffer, 1, length, file);
		}
		fclose(file);
	}

	if (!buffer)
	{
		return 1;
	}
	cJSON* json = cJSON_ParseWithLength(buffer, length);



	// delete
	cJSON_Delete(json);
	free(buffer);
	return 0;
}
u8 saveScene(FILE* file, umax_t pos, scene_t* scene) 
{
	if (!file) {
		return 1;
	}
	// cJSON's
	cJSON* answers = NULL;
	cJSON* influences = NULL;
	cJSON* scenejson = cJSON_CreateObject();

	// text
	if (cJSON_AddStringToObject(scenejson, "text", scene->text) == NULL) {
		goto end;
	}

	// answers
	answers = cJSON_AddArrayToObject(scenejson, "answers");
	if (answers == NULL) {
		goto end;
	}
	for (size_t i = 0; i < scene->nAnswers; i++)
	{
		cJSON* answer = cJSON_CreateObject();
		if (cJSON_AddStringToObject(answer, "text", scene->answers[i]) == NULL) {
			goto end;
		}
		cJSON_AddItemToArray(answers, answer);
	}

	// influence
	influences = cJSON_AddArrayToObject(scenejson, "influences");
	if (influences == NULL) {
		goto end;
	}
	for (size_t i = 0; i < scene->nAnswers; i++)
	{
		cJSON* influence = cJSON_CreateObject();
		if (cJSON_AddNumberToObject(influence, "strength", scene->influence[i]) == NULL) {
			goto end;
		}
		cJSON_AddItemToArray(influences, influence);
	}

	// TODO: index of right answer and required level

	// end
end:
	cJSON_Delete(scenejson);
	return 0;
}

scene_t* createScene(
	const char* 	text, 
	const char** 	answers, 
	umax_t 		numAnswers, 
	float* 		influenceOfAnswers, 
	umax_t 		indexOfRightAnswers, 
	umax_t 		requiredLevel ) 
{
	scene_t* newScene 	= malloc(sizeof(scene_t));
	assert(newScene != NULL);
	newScene->text 		= text;
	newScene->answers 	= answers;
	newScene->nAnswers 	= numAnswers;
	newScene->influence 	= influenceOfAnswers;
	newScene->iofcans 	= indexOfRightAnswers;
	newScene->requiredlevel = requiredLevel;
	return newScene;
}
