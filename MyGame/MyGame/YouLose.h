#pragma once
#include "../BaseEngine/Scenes/Scene.h"
#include "../BaseEngine/BaseEngine.h"

class YouLose : public Scene
{
private:
	Image lose_;

public:
	YouLose(BaseEngine *);
	virtual ~YouLose();

	virtual void Setup();
	virtual void Reset();
	virtual void Update();
	virtual void Draw();
};

