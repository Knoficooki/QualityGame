#include "scene.h"
#include <type.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

u8 play_scene(scene_t* scene) {
	printf("Scene Output");
	return 0;
}

u8 loadScene(FILE* file, umax_t pos, scene_t* scene) 
{
	if(scene == NULL) {
		scene = malloc(sizeof(scene_t));
	}
	char* buffer = 0;
	long length;

	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file) - pos;
		fseek(file, pos, SEEK_SET);
		buffer = malloc(length);
		memset(buffer, 0, length);
		if (buffer)
		{
			fread(buffer, 1, length, file);
		}
	}

	if (!buffer)
	{
		return 1;
	}
	cJSON *s_text,*s_answers, *s_influences, *s_iofcans, *s_requiredlevel;


	cJSON* json = cJSON_ParseWithLength(buffer, length);
	
	if (json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
		goto end;
	}
	
	// name
	cJSON *s_name;
	s_name = cJSON_GetObjectItemCaseSensitive(json, "name");
	if(cJSON_IsString(s_name) && (s_name->valuestring != NULL)) {
		scene->name = strdup(s_name->valuestring);
	}

	// text
	s_text = cJSON_GetObjectItemCaseSensitive(json, "text");
	if (cJSON_IsString(s_text) && (s_text->valuestring != NULL)) {
		scene->text = strdup(s_text->valuestring);
	}
	
	// answers
	s_answers = cJSON_GetObjectItemCaseSensitive(json, "answers");
	char** answers = malloc(sizeof(char*)*1);
	umax numAnswers = 0;
	cJSON *answer = NULL;
	cJSON_ArrayForEach(answer, s_answers)
	{
		answers = realloc(answers , sizeof(char*) * (++numAnswers));
		cJSON *text = cJSON_GetObjectItemCaseSensitive(answer, "text");
		if (!cJSON_IsString(text) && (text->valuestring != NULL))
		{
			answers[numAnswers-1] = strdup(text->valuestring);
		}
	}
	scene->answers = (const char**)answers;
	scene->nAnswers = numAnswers;
	

	// influences
	s_influences = cJSON_GetObjectItemCaseSensitive(json, "influences");
	cJSON *influence = NULL;
	
	float* influences = malloc(sizeof(float));
	umax numinf = 0;
	cJSON_ArrayForEach(influence, s_influences) {
		influences = realloc(influences, sizeof(float) * (++numinf));

		cJSON *strength = cJSON_GetObjectItemCaseSensitive(influence, "strength");
		if (!cJSON_IsNumber(strength)) {
			influences[numinf] = strength->valuedouble;
		}
	}

	// right answer
	s_iofcans = cJSON_GetObjectItemCaseSensitive(json, "right_answer");
	if(!cJSON_IsNumber(s_iofcans)) {
		scene->iofcans = (umax)s_iofcans->valuedouble;
	}
	
	// required level
	s_requiredlevel = cJSON_GetObjectItemCaseSensitive(json, "required_level");
	if(!cJSON_IsNumber(s_requiredlevel)) {
		scene->requiredlevel = s_requiredlevel->valuedouble;
	}
	
	cJSON_Delete(json);
	free(buffer);
	return 0;

end:
	// delete
	cJSON_Delete(json);
	free(buffer);
	return 1;
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

	// name
	if (cJSON_AddStringToObject(scenejson, "name", scene->name) == NULL) {
		goto end;
	}

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

	// right answer
	if (cJSON_AddNumberToObject(scenejson, "right_answer", scene->iofcans) == NULL)
	{
		goto end;
	}

	// required level
	if (cJSON_AddNumberToObject(scenejson, "required_level", scene->requiredlevel) == NULL) 
	{
		goto end;
	}
	// file print
	char *string = cJSON_Print(scenejson);
	if (string == NULL)
	{
		fprintf(stderr, "Failed to save scene to file.\n");
	}

	fseek(file, pos, SEEK_SET);
	fprintf(file, "%s", string);

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
