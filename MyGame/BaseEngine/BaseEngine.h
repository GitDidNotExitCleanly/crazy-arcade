#pragma once
#include "SDL.h"
#include "KeyboardManager.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

class Scene;
class DisplayableObject;

class BaseEngine
{
private:
	const Uint32 GAME_ACTION_FREQUENCY;
	bool isBaseEngineInitialized_;

	KeyboardManager * keyboardManager_;
	WindowManager * windowManager_;
	ResourceManager * resourceManager_;
	SceneManager * sceneManager_;

protected:
	virtual void LoadResource() = 0;
	virtual void SetupScenes() = 0;
	virtual void GameAction() = 0;
	virtual void GameRender() = 0;

public:
	BaseEngine();
	virtual ~BaseEngine();
	void Initialize();
	void MainLoop();
	void Finalize();
	KeyboardManager * getKeyboardManager();
	WindowManager * getWindowManager();
	ResourceManager * getResourceManager();
	SceneManager * getSceneManager();
};

