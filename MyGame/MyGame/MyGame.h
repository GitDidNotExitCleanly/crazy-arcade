#pragma once
#include "SDL.h"
#include "../BaseEngine/BaseEngine.h"

class MyGame : public BaseEngine
{
private:
	virtual void LoadResource();
	virtual void SetupScenes();
	virtual void GameAction();
	virtual void GameRender();

public:
	MyGame();
	virtual ~MyGame();
};

