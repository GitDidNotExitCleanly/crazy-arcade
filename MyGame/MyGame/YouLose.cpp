#include "YouLose.h"
#include "ResourceID.h"
#include "SceneID.h"

YouLose::YouLose(BaseEngine * engine)
	:Scene(engine)
{
}

YouLose::~YouLose()
{
}

void YouLose::Setup()
{
	ResourceManager * resource = getBaseEngine()->getResourceManager();
	lose_ = resource->getImage(static_cast<int>(ImageID::LOSE_PAGE));
}

void YouLose::Reset()
{
}

void YouLose::Update()
{
}

void YouLose::Draw()
{
	WindowManager * window = getBaseEngine()->getWindowManager();
	window->drawImage(lose_, { 0,0,window->WINDOW_WIDTH,window->WINDOW_HEIGHT });
	window->updateWindow();
}
