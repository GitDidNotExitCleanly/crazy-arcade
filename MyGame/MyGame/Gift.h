#pragma once
#include "SDL.h"
#include "../BaseEngine/Objects/TileObject.h"
#include "../BaseEngine/Scenes/TileMapScene.h"

class Gift : public TileObject
{
public:
	Gift(TileMapScene *);
	virtual ~Gift();
};

