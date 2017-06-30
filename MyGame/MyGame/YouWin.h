#pragma once
#include "../BaseEngine/Scenes/Scene.h"
#include "../BaseEngine/BaseEngine.h"

class YouWin : public Scene
{
private:
	Image win_;

public:
	YouWin(BaseEngine *);
	virtual ~YouWin();

	virtual void Setup();
	virtual void Reset();
	virtual void Update();
	virtual void Draw();
};

