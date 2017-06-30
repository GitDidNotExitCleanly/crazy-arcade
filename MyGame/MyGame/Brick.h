#pragma once
#include "SDL.h"
#include "../BaseEngine/Objects/TileObject.h"
#include "../BaseEngine/Scenes/TileMapScene.h"
#include "Gift.h"

class Brick : public TileObject
{
private:
	Gift * gift_;

public:
	Brick(TileMapScene *);
	virtual ~Brick();

	void addGift(Gift *);
	void exlode();

	virtual void SetPosition(int, int);
	virtual int GetImageAreaPosXFromPosX(int);
	virtual int GetImageAreaPosYFromPosY(int);
	virtual int GetPosXFromImageAreaPosX(int);
	virtual int GetPosYFromImageAreaPosY(int);
	virtual void UpdateObject();
	virtual void DrawObject();
};

