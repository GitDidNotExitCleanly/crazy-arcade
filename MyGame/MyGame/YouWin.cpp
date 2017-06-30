#include "YouWin.h"
#include "ResourceID.h"
#include "SceneID.h"

YouWin::YouWin(BaseEngine * engine)
	:Scene(engine)
{
}

YouWin::~YouWin()
{
}

void YouWin::Setup()
{
	ResourceManager * resource = getBaseEngine()->getResourceManager();
	win_ = resource->getImage(static_cast<int>(ImageID::WIN_PAGE));
}

void YouWin::Reset()
{
}

void YouWin::Update()
{
}

void YouWin::Draw()
{
	WindowManager * window = getBaseEngine()->getWindowManager();
	window->drawImage(win_, { 0,0,window->WINDOW_WIDTH,window->WINDOW_HEIGHT });
	window->updateWindow();
}
