#pragma once
#include "SDL.h"
#include "../BaseEngine/Objects/TileObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "../BaseEngine/Scenes/TileMapScene.h"
#include "../BaseEngine/Utility.h"

enum class BombState
{
	APPEAR = 0,
	EXPLODE = 1,
	DISAPPEAR = 2
};

class Bomb : public TileObject
{
private:
	int power_;
	Timer timer_;

	void destroy();
	bool destroyTileObject(TileObject *);
	void destroyActiveObject(DisplayableObject *);

public:
	Bomb(TileMapScene *);
	virtual ~Bomb();

	void setPower(int);
	void appear(int, int);
	void explode();

	virtual void SetPosition(int, int);
	virtual void UpdateObject();
	virtual void DrawObject();
};

