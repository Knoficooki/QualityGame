#include "scene.h"
#include <type.h>
#include <malloc.h>
#include <stdio.h>

u8 playScene(scene_t* scene) {
	printf("Scene Output");
}

u8 loadScene(FILE* file, umax_t pos, scene_t* scene) 
{

}
u8 saveScene(FILE* file, umax_t pos, scene_t* scene) 
{

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
	newScene->text 		= text;
	newScene->answers 	= answers;
	newScene->nAnswers 	= numAnswers;
	newScene->influence 	= influenceOfAnswers;
	newScene->iofcans 	= indexOfRightAnswers;
	newScene->requiredlevel = requiredLevel;
	return newScene;
}
