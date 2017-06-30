#include "CoverScene.h"
#include "ResourceID.h"
#include "SceneID.h"
#include "MainScene.h"

CoverScene::CoverScene(BaseEngine * engine)
	:Scene(engine)
{
}

CoverScene::~CoverScene()
{
}

void CoverScene::Setup()
{
	ResourceManager * resource = getBaseEngine()->getResourceManager();
	start_page_ = resource->getImage(static_cast<int>(ImageID::START_PAGE));
}

void CoverScene::Reset()
{
}

void CoverScene::Update()
{
	KeyboardManager * keyboardManager = getBaseEngine()->getKeyboardManager();
	KeyCode key = keyboardManager->getLastPressedKey();
	if (key == KeyCode::KEY_SPACE) {
		SceneManager * sceneManager = getBaseEngine()->getSceneManager();
		sceneManager->setCurrentScene(static_cast<int>(SceneID::MAIN));
		dynamic_cast<MainScene *>(sceneManager->getCurrentScene())->startGame();
	}
}

void CoverScene::Draw()
{
	WindowManager * window = getBaseEngine()->getWindowManager();
	window->drawImage(start_page_, { 0,0,window->WINDOW_WIDTH,window->WINDOW_HEIGHT });
	window->updateWindow();
}
