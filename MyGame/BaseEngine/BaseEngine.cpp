#include "BaseEngine.h"
#include "SDL_image.h"
#include "Utility.h"
#include <iostream>

BaseEngine::BaseEngine()
	:isBaseEngineInitialized_(true),
	GAME_ACTION_FREQUENCY(33),
	keyboardManager_(NULL),
	windowManager_(NULL),
	resourceManager_(NULL),
	sceneManager_(NULL)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		isBaseEngineInitialized_ = false;
		std::cout << "SDL fails to start" << std::endl;
	}
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if ((IMG_Init(flags)&flags) != flags) {
		isBaseEngineInitialized_ = false;
		std::cout << "IMG fails to start" << std::endl;
	}
	if (TTF_Init() != 0) {
		isBaseEngineInitialized_ = false;
		std::cout << "TTF fails to start" << std::endl;
	}

	keyboardManager_ = new KeyboardManager;
	if (keyboardManager_->isKeyboardManagerInitialized_ == false) {
		isBaseEngineInitialized_ = false;
		std::cout << "KeyboardManager fails to start" << std::endl;
	}

	windowManager_ = new WindowManager;
	if (windowManager_->isWindowManagerInitialized_ == false) {
		isBaseEngineInitialized_ = false;
		std::cout << "WindowManager fails to start" << std::endl;
	}
}

BaseEngine::~BaseEngine()
{
	delete windowManager_;
	delete keyboardManager_;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void BaseEngine::Initialize() 
{
	resourceManager_ = new ResourceManager(windowManager_->sdl_renderer_);
	LoadResource();
	if (resourceManager_->isResourceManagerInitialized_ == false) {
		isBaseEngineInitialized_ = false;
		std::cout << "ResourceManager fails to start" << std::endl;
	}

	sceneManager_ = new SceneManager;
	SetupScenes();
	if (sceneManager_->isSceneManagerInitialized_ == false) {
		isBaseEngineInitialized_ = false;
		std::cout << "SceneManager fails to start" << std::endl;
	}
}

void BaseEngine::Finalize() 
{
	delete sceneManager_;
	delete resourceManager_;
}

void BaseEngine::MainLoop() 
{
	if (isBaseEngineInitialized_) {
		SDL_Event event;
		Timer update_timer;
		Uint32 frames = 0;
		Uint32 elapsedTime;
		Uint32 currentTime;
		update_timer.start();
		while (true) {

			// read input
			while (SDL_PollEvent(&event) != 0) {
				switch (event.type)
				{
				case SDL_QUIT:
					return;
					break;
				case SDL_KEYUP:
					keyboardManager_->setKeyStatus(keyboardManager_->findInternalKeyCode(event.key.keysym.sym), KeyState::KEY_RELEASED);
					break;
				case SDL_KEYDOWN:
					keyboardManager_->setKeyStatus(keyboardManager_->findInternalKeyCode(event.key.keysym.sym), KeyState::KEY_PRESSED);
					break;
				default:
					break;
				}
			}

			// update all components
			elapsedTime = update_timer.getDeltaTicks();
			if (elapsedTime >= GAME_ACTION_FREQUENCY) {
				// update
				update_timer.pause();
				currentTime = update_timer.getTotalTicks();
				GameAction();
				update_timer.unpause();

				// reset keyboard record
				keyboardManager_->resetKeyStatus();

				// showing frame rate
				//std::cout << frames / (elapsedTime / 1000.0f) << std::endl;
				frames = 0;
			}

			// render all components
			GameRender();

			frames++;
		}
	}
}

KeyboardManager * BaseEngine::getKeyboardManager()
{
	return keyboardManager_;
}

WindowManager * BaseEngine::getWindowManager()
{
	return windowManager_;
}

ResourceManager * BaseEngine::getResourceManager()
{
	return resourceManager_;
}

SceneManager * BaseEngine::getSceneManager()
{
	return sceneManager_;
}