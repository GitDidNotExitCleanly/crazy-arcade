#pragma once
#include "Scenes/Scene.h"

class SceneManager
{
private:
	int numOfScenes_;
	int currentSceneIndex;
	Scene ** scenes_;
	
	bool isSceneManagerInitialized_;

	// only allow BaseEngine to create instance
	SceneManager();
	friend class BaseEngine;

public:
	~SceneManager();
	SceneManager(const SceneManager &) = delete;
	SceneManager & operator=(const SceneManager &) = delete;

	void setNumOfScenes(int);
	int getNumOfScenes();
	void setCurrentScene(int);
	Scene * getCurrentScene();
	void addScene(int, Scene *);
	void removeScene(int);
	Scene * getScene(int);
	void resetScene(int);
	void resetAllScenes();
};

