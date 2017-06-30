#include "SceneManager.h"
#include "Scenes/Scene.h"
#include <iostream>

SceneManager::SceneManager()
	:isSceneManagerInitialized_(true),
	numOfScenes_(0),
	currentSceneIndex(0),
	scenes_(NULL)
{
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < numOfScenes_; i++) {
		delete scenes_[i];
	}
	delete[] scenes_;
}

void SceneManager::setNumOfScenes(int num)
{
	numOfScenes_ = num;
	scenes_ = new Scene *[num];
	for (int i = 0; i < num; i++) {
		scenes_[i] = NULL;
	}
}

int SceneManager::getNumOfScenes()
{
	return numOfScenes_;
}

void SceneManager::setCurrentScene(int index)
{
	currentSceneIndex = index;
}

Scene * SceneManager::getCurrentScene()
{
	return scenes_[currentSceneIndex];
}

void SceneManager::addScene(int index, Scene * scene)
{
	scenes_[index] = scene;
}

void SceneManager::removeScene(int index)
{
	delete scenes_[index];
	scenes_[index] = NULL;
}

Scene * SceneManager::getScene(int index)
{
	return scenes_[index];
}

void SceneManager::resetScene(int index)
{
	scenes_[index]->Reset();
}

void SceneManager::resetAllScenes()
{
	for (int i = 0; i < numOfScenes_; i++) {
		scenes_[i]->Reset();
	}
}
