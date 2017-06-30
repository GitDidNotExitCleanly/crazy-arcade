#pragma once
#include "../BaseEngine/Scenes/Scene.h"
#include "../BaseEngine/BaseEngine.h"

class CoverScene : public Scene
{
private:
	Image start_page_;

public:
	CoverScene(BaseEngine *);
	virtual ~CoverScene();

	virtual void Setup();
	virtual void Reset();
	virtual void Update();
	virtual void Draw();
};

